#include "defs.h"
#include <getopt.h>
#include <sys/resource.h>

#define INTIAL_EXCLUDE_LIST_SIZE   4096
#define CONFIG_FINDRECENT          "findrecent.conf"
#define CONFIG_EXCLUDE             "exclude.conf"

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

  uint32_t exclude_list_count;
  uint32_t exclude_list_capa;
};

static inline
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

    "config folder (default: `"CONFIG_DIRECTORY"`):\n"
    "  findrecent/"CONFIG_FINDRECENT" : each line corresponds to an options\n"
    "  findrecent/"CONFIG_EXCLUDE"    : each line corresponds to a directory\n"
    "  lines starting with `#` are ignored\n\n"

    // "fzf commands:\n"
    // "  ctrl+r  : reload\n"
    // "  enter   : select the entry, show git changes if possible\n"
    // option pour activer .git ou bat
    );
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
      break;
  }
}

static inline
int parsing_quote(char** str)
{
  if(**str == '"' || **str == '\''){
    char quote = **str;
    char* c = *str;
    while(1){
      c++;
      if(*c == '\n' || *c == '\0')
        return 1;
      else if(*c == quote){
        *c = '\0';
        (*str)++;
        return 0;
      }
    }
  }
  return 0;
}

static
void parse_config_files(struct arguments *arguments)
{
  char config_file[PATH_MAX];
  char config_directory[PATH_MAX] = {0};

  const char* home_directory = getenv("HOME");
  if(CONFIG_DIRECTORY[0] == '~' && home_directory){
    strcpy(config_directory, home_directory);
    strcat(config_directory, CONFIG_DIRECTORY+1); // remove the ~ character
  }
  else
    strcpy(config_directory, CONFIG_DIRECTORY);

  char* line_buffer = NULL;
  size_t alloc_size = 0;
  size_t line_number = 0;

  // parse config file
  strcpy(config_file, config_directory);
  strcat(config_file, CONFIG_FINDRECENT);
  FILE* config_findrecent = fopen64(config_file, "r");
  if(config_findrecent){
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
          fprintf(stderr, "error parsing `"CONFIG_FINDRECENT":%ld`, invalid argument: `%s`\n", line_number, cur);
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

      if(optarg){
        while(*optarg == ' ' || *optarg == '\t') optarg++; // trim left
        if(parsing_quote(&optarg)){ // parsing quote from `optarg`
          fprintf(stderr, "error parsing `"CONFIG_FINDRECENT":%ld`, unfinished quote: `%s`\n", line_number, cur);
          optarg = NULL;
          continue;
        }
      }

      if(arg)
        parse_arg(arguments, arg);
      optarg = NULL;
    }
  }

  // parse exclude file
  strcpy(config_file, config_directory);
  strcat(config_file, CONFIG_EXCLUDE);
  FILE *config_exclude = fopen64(config_file, "r");
  if(config_exclude){
    while(1)
    {
      ssize_t n = getline(&line_buffer, &alloc_size, config_exclude);
      line_number++;
      if(n<=0) break;
      char* cur = line_buffer;
      cur[n-1] = '\0'; // remove newline

      while(*cur == ' ' || *cur == '\t') cur++; // trim left
      if(*cur == '#' || *cur == '\0' || *cur == '\n') continue;

      if(parsing_quote(&cur)){ // parsing quote from `optarg`
        fprintf(stderr, "error parsing `"CONFIG_FINDRECENT":%ld`, unfinished quote: `%s`\n", line_number, cur);
        continue;
      }
      push_exclude_path(arguments, cur);
    }
  }

  fclose(config_findrecent);
  fclose(config_exclude);
  free(line_buffer);
}

struct parsed_options parse_options(int argc, char** argv)
{
  struct arguments arguments = default_arguments();
  
  // process config file
  parse_config_files(&arguments);

  // process arguments
  while(1) {
    int arg = getopt_long(argc, argv, "FDt:d:rfce:h", long_options, NULL);
    if(arg == -1)
      break;
    parse_arg(&arguments, arg);
  }

  // post process
  if (optind < argc-1) {
    fprintf(stderr, "too many arguments given: ");
    while (optind < argc)
      fprintf (stderr, "`%s` ", argv[optind++]);
    fprintf (stderr, "\n");
    exit(1);
  }
  else if (optind == argc-1)
    arguments.main_directory = argv[optind];

  omp_set_num_threads(arguments.threads); // 3 best ?
  
  if(arguments.inc_max_fd) {
    // increase maximum number of file descriptor opened at the same time. prevent crash when there are to many threads 
    struct rlimit rl;
    check(getrlimit(RLIMIT_NOFILE, &rl));
    rl.rlim_cur = rl.rlim_max;
    check(setrlimit(RLIMIT_NOFILE, &rl));
  }
  
  if(arguments.no_exclude)
    *arguments.options.exclude_list = '\0';

  return (struct parsed_options){
    .options=arguments.options, 
    .main_directory=arguments.main_directory,
    .activate_color=arguments.color,
    .reverse_order=arguments.reverse_order,
    .activate_fzf=arguments.fzf
    };
}
