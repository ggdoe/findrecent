#include "defs.h"
#include <getopt.h>
#include <sys/resource.h>
#include <sys/mman.h>

#define INTIAL_EXCLUDE_LIST_SIZE   4096
#define CONFIG_FILE  "~/.config/findrecent/findrecent.conf"

struct option long_options[] = {
  {"find-files",       no_argument,       0, 'F'},
  {"find-directories", no_argument,       0, 'D'},
  {"date-type",        required_argument, 0, 't'},
  {"reverse",          no_argument,       0, 'r'},
  {"depth",            required_argument, 0, 'd'},
  {"fzf",              no_argument,       0, 'f'},
  {"color",            no_argument,       0, 'c'},
  {"threads",          required_argument, 0, 'T'},
  {"inc-max-fd",       no_argument,       0, 'i'},
  {"exclude",          required_argument, 0, 'e'},
  {"no-exclude",       no_argument,       0, 'E'},
  {"help",             no_argument,       0, 'h'},
  {"print-config",     no_argument,       0, 'P'},
  {0, 0, 0, 0}
};

struct arguments {
  struct options options;
  char* main_directory;
  uint32_t threads;
  bool reverse_order;
  bool fzf;
  bool color;
  bool inc_max_fd;
  bool no_exclude;

  bool print_config;
  uint32_t exclude_list_count;
  uint32_t exclude_list_capa;
};

static
void print_help()
{
  printf(
    "find recently modified files\n\n"

    "options:\n"
    "  -F, --find-files        : find files (default)\n"
    "  -D, --find-directories  : find directories\n"
    "  -t, --date-type <str>   : change the sorting criterium, can be `creation`, \n"
    "                            `access`, or `modification` (default: modification)\n"
    "  -d, --depth <int>       : maximum depth of search\n"
    "  -r, --reverse           : reverse the order\n"
    "      --fzf               : show in fzf\n"
    "      --color             : colorize output name\n"
    "      --threads <int>     : specify the number of threads (default: 3),\n"
    "                            high value may not be faster\n"
    "      --inc-max-fd        : increase the maximum number of files descriptors opened \n"
    "                            at the same time (may be necessary with lot of threads)\n"
    // "  -e, --exclude <path>    : exclude directory. `*` can match multiple characters\n"
    "  -e, --exclude <path>    : exclude directory.\n"
    "      --no-exclude        : do not exclude any path\n"
    "  -h, --help              : show help\n\n"
    "  --print-config          : show configuration\n\n"

    "config file (default: `"CONFIG_FILE"`):\n"
    "  -each line corresponds to an options (and has to start with `-`)\n"
    // "  findrecent/"CONFIG_EXCLUDE"    : each line corresponds to a directory\n"
    "  commentary are marked with `#`\n\n"

    // "fzf commands:\n"
    // "  ctrl+r  : reload\n"
    // "  enter   : select the entry, show git changes if possible\n"
    // option pour activer .git ou bat
    );
}

static
void print_arguments_config(struct arguments *arguments)
{
  printf("search_type:    %s \n", (arguments->options.search_type == SEARCH_FILES) ? "file" : "directories");
  printf("date_type:      %s \n", (arguments->options.date_type == DATE_CREAT) ? "creation" : (arguments->options.date_type == DATE_ACCESS) ? "access" : "modification");
  printf("max_depth:      %lu\n", arguments->options.max_depth);
  printf("main_directory: `%s` \n", arguments->main_directory);
  printf("threads:        %u \n", arguments->threads);
  printf("reverse_order:  %s \n", (arguments->reverse_order == false) ? "false" : "true");
  printf("fzf:            %s \n", (arguments->fzf == false) ? "false" : "true");
  printf("color:          %s \n", (arguments->color == false) ? "false" : "true");
  printf("inc_max_fd:     %s \n", (arguments->inc_max_fd == false) ? "false" : "true");
  printf("no_exclude:     %s \n", (arguments->no_exclude == false) ? "false" : "true");
  char* cur = arguments->options.exclude_list;
  while(*cur != '\0') {
    printf("exclude:        `%s`\n", cur);
    cur += strlen(cur) + 1;
  } 
}

static inline
struct arguments default_arguments()
{
  static char local_directory[NAME_MAX] = ".";
  char* exclude_list = (char*)calloc(INTIAL_EXCLUDE_LIST_SIZE, sizeof(char));

  return (struct arguments){
    .options        = {
      .exclude_list = exclude_list,
      .search_type  = SEARCH_FILES,
      .date_type    = DATE_MODIF,
      .max_depth    = UINT32_MAX,
      },
    .main_directory = local_directory,
    .threads        = 3,
    .reverse_order  = false,
    .fzf            = false,
    .color          = false,
    .inc_max_fd     = false,
    .no_exclude     = false,

    .print_config   = false,
    .exclude_list_count = 0,
    .exclude_list_capa  = INTIAL_EXCLUDE_LIST_SIZE
  };
}

static inline
void push_exclude_path(struct arguments *arguments, const char* path)
{
  size_t len = strlen(path) + 1;
  
  // subdirectories are not supported
  char* slash = strchr(path, '/');
  char* cur=slash;
  if(cur != NULL) 
    while(1) {// trim end
      cur++; len--;
      if(*cur == '\0'){
        *slash = '\0';
        break;
      }
      else if(*cur != '/'){
        fprintf(stderr, "subdirectories are not supported in exclude path: `%s`\n", path);
        return;
      }
    }

  uint32_t *count = &arguments->exclude_list_count;
  uint32_t *capa  = &arguments->exclude_list_capa;
  char** exclude_list = &arguments->options.exclude_list;

  if(*count + len + 1>= *capa){
    *exclude_list = (char*)realloc(*exclude_list, *capa * 2);
    *capa *= 2;
  }
  memcpy(*exclude_list + *count, path, len*sizeof(char));
  *count += len;
  (*exclude_list)[*count] = '\0';
}

static inline
void parse_arg(struct arguments *arguments, int arg)
{
  switch (arg)
  {
    case 'F': // find-files
      arguments->options.search_type = SEARCH_FILES;
      break;
    case 'D': // find-directories
      arguments->options.search_type = SEARCH_DIRECTORIES;
      break;
    case 't': // date-type
      if(!strncmp(optarg, "access", strlen(optarg)))
        arguments->options.date_type = DATE_ACCESS;
      else if(!strncmp(optarg, "creation", strlen(optarg)))
        arguments->options.date_type = DATE_CREAT;
      else if(!strncmp(optarg, "modification", strlen(optarg)))
        arguments->options.date_type = DATE_MODIF;
      else
        fprintf(stderr, "bad argument for date-type: `%s`\n", optarg);
      break;
    case 'd': // depth
      arguments->options.max_depth = atoi(optarg); 
      break;
    case 'r': // reverse
      arguments->reverse_order = !arguments->reverse_order; 
      break;
    case 'f': // fzf
      arguments->fzf = true;
      break;
    case 'c': // color
      arguments->color = true;
      break;
    case 'T': // threads
      arguments->threads = atoi(optarg);
      break;
    case 'i': // inc-max-fd
      arguments->inc_max_fd = true;
      break;
    case 'e': // exclude
      push_exclude_path(arguments, optarg);
      break;
    case 'E': // no-exclude
      arguments->no_exclude = true;
      break;
    case 'h': // help
      print_help();
      exit(0);
    case 'P':
      arguments->print_config = true;
      break;
  }
}

static inline
char* parsing_quote(char* str)
{
  char quote = *str;
  if(quote == '"' || quote == '\''){
    for(char* c=str+1;; c++) {
      if(*c == '\n' || *c == '\0'){
        *c = '\0';
        return NULL;
      }
      else if(*c == quote){
        *c = '\0';
        return c;
      }
    }
  }
  return str;
}

static
void parse_config_files(struct arguments *arguments)
{
  char config_file[PATH_MAX] = {0};

  const char* home_directory = getenv("HOME");
  if(CONFIG_FILE[0] == '~' && home_directory){
    int len = strlen(home_directory);
    memcpy(config_file+len-1, CONFIG_FILE, sizeof(CONFIG_FILE)); // remove the ~ character
    memcpy(config_file, home_directory, len);
  }
  else
    strcpy(config_file, CONFIG_FILE);

  #if 1
  int fd = open(config_file, O_RDWR);
  if(fd>=0)
  {
    struct stat64 stat;
    fstat64(fd, &stat);
    char* config_raw = (char*) mmap64(NULL, (stat.st_size+1)*sizeof(char), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    config_raw[stat.st_size] = '\0';
    int config_capa = 32, config_argc = 1;
    char** config_argv = (char**)malloc(config_capa * sizeof(char*));
    config_argv[0] = config_raw; // dummy argv[0] 

    // remove comments
    for(char* cur=config_raw; *cur != '\0'; cur++){
      if(*cur == '#')
        while(*cur != '\n' && *cur != '\0'){
          *cur = ' ';
          cur++;
        }
    }

    // verify validity
    bool parsing_failed = false;
    {
      int line = 0;
      for(char* cur=config_raw; *cur != '\0';){
        while(*cur == ' ' || *cur == '\t') cur++;

        int len = 0;
        while(!(cur[len] == '\n' || cur[len] == '\0')) len++;
        line++;

        if(*cur != '-' && *cur != '\n'){
          fprintf(stderr, "command error line %d: ", line);
          fwrite(cur, sizeof(char), len, stderr);
          fprintf(stderr, "\n");
          parsing_failed = true;
        }
        cur += len+1;
      }
      if(parsing_failed){
        fprintf(stderr, "error parsing `"CONFIG_FILE"`, commands has to start with `-`.\n");
      }
    }

    // fill argv to use getopt
    for(char* cur=config_raw; *cur != '\0';){
      while(*cur == ' ' || *cur == '\t' || *cur == '\n') cur++;

      char* quote_end = parsing_quote(cur);
      if(!quote_end){
        fprintf(stderr, "error parsing `"CONFIG_FILE"`, unfinished quote: %s\n", cur);
        parsing_failed = true;
      }
      else if(cur != quote_end){
        config_argv[config_argc++] = cur+1; // ignore the quote symbol
        cur = quote_end+1;
      }
      else
        config_argv[config_argc++] = cur;

      while(!(*cur == ' ' || *cur == '\t' || *cur == '\n' || *cur == '\0')) cur++;
      *cur++ = '\0';  
      
      if(config_argc >= config_capa){
        config_capa *= 2;
        config_argv = (char**)realloc(config_argv, config_capa * sizeof(char*));
      }
    }
    config_argv[--config_argc] = NULL;

    // process arguments
    while(1) {
      int arg = getopt_long_only(config_argc, config_argv, "FDt:d:rfce:h", long_options, NULL);
      if(arg == -1)
        break;
      else if(arg == '?'){
        parsing_failed = true;
      }
      parse_arg(arguments, arg);
    }
    if(parsing_failed) {
      fprintf(stderr, "Error parsing the config file `%s`\n", config_file);
      exit(1);
    } 
    optind=0; // reset getopt for next use of getopt

    free(config_argv);
    munmap(config_raw, stat.st_size*sizeof(char));
    close(fd);
  }
  #else
  
  char* line_buffer = NULL;
  size_t alloc_size = 0;
  size_t line_number = 0;

  FILE* config_findrecent = fopen64(config_file, "r");
  if(config_findrecent)
  {
    while(1)
    {
      ssize_t n = getline(&line_buffer, &alloc_size, config_findrecent);
      line_number++;
      if(n<=0) break;
      char* cur = line_buffer;
      cur[n-1] = '\0'; // remove newline

      while(*cur == ' ' || *cur == '\t' || *cur == '-') cur++; // trim left
      if(*cur == '#' || *cur == '\0' || *cur == '\n') continue;
      int arg = 0;
      
      for(struct option *opt=long_options; opt->name != 0; opt++){
        if(!strncmp(opt->name, cur, strlen(opt->name))){
          arg = opt->val;
          if(opt->has_arg == required_argument){
            optarg = cur + strlen(opt->name);
          }
          break;
        }
      }
      if(!arg) {
        if(cur[1] != ' ' && cur[1] != '\t' && cur[1] != '\0'){
          fprintf(stderr, "error parsing `"CONFIG_FILE":%ld`, invalid argument: `%s`\n", line_number, cur);
          continue;
        }
        else
          for(struct option *opt=long_options; opt->name != 0; opt++){
            if(opt->val == *cur){
              arg = opt->val;
              if(opt->has_arg == required_argument){
                optarg = cur + 1;
              }
              break;
            }
          }
      }
// //////////
//       char* quote_end = parsing_quote(cur);
//       if(!quote_end){
//         fprintf(stderr, "error parsing `"CONFIG_FILE"`, unfinished quote: %s\n", cur);
//         parsing_failed = true;
//       }
//       else if(cur != quote_end){
//         config_argv[config_argc++] = cur+1; // ignore the quote symbol
//         cur = quote_end+1;
//       }
//       else
//         config_argv[config_argc++] = cur;
// /////////

      if(optarg){
        // while(*optarg == ' ' || *optarg == '\t') optarg++; // trim left
        char* quote_end = parsing_quote(optarg);
        if(!quote_end){ // parsing quote from `optarg`
          fprintf(stderr, "error parsing `"CONFIG_FILE":%ld`, unfinished quote: `%s`\n", line_number, optarg);
          optarg = NULL;
          continue;
        }
      }

      if(arg)
        parse_arg(arguments, arg);
      optarg = NULL;
    
    fclose(config_findrecent);
    }
  print_arguments_config(arguments);
  exit(0);

  }
  if(line_buffer) free(line_buffer);
  #endif
}

struct parsed_options parse_options(int argc, char** argv)
{
  struct arguments arguments = default_arguments();
  
  // process config file
  parse_config_files(&arguments);

  // process arguments
  bool parsing_failed = false;
  while(1) {
    int arg = getopt_long_only(argc, argv, "FDt:d:rfce:h", long_options, NULL);
    if(arg == -1)
      break;
    else if(arg == '?')
      parsing_failed = true;
    parse_arg(&arguments, arg);
  }

  // post process
  if (optind < argc-1) {
    fprintf(stderr, "too many arguments given: ");
    while (optind < argc)
      fprintf (stderr, "`%s` ", argv[optind++]);
    fprintf (stderr, "\n");
    parsing_failed = true;
  }
  else if (optind == argc-1)
    arguments.main_directory = argv[optind];

  if(arguments.no_exclude)
    *arguments.options.exclude_list = '\0';

  if(arguments.print_config){
    print_arguments_config(&arguments);
    exit(0);
  }
  if(parsing_failed) exit(1);

  omp_set_num_threads(arguments.threads); // 3 best ?
  
  if(arguments.inc_max_fd) {
    // increase maximum number of file descriptor opened at the same time. prevent crash when there are to many threads 
    struct rlimit rl;
    check(getrlimit(RLIMIT_NOFILE, &rl));
    rl.rlim_cur = rl.rlim_max;
    check(setrlimit(RLIMIT_NOFILE, &rl));
  }

  return (struct parsed_options){
    .options=arguments.options, 
    .main_directory=arguments.main_directory,
    .activate_color=arguments.color,
    .reverse_order=arguments.reverse_order,
    .activate_fzf=arguments.fzf
    };
}
