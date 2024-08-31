#include "defs.h"
#include <getopt.h>
#include <sys/resource.h>
#include <sys/mman.h>

#define INTIAL_EXCLUDE_LIST_SIZE   4096
#define CONFIG_FILE  "~/.config/findrecent/findrecent.conf"
#define DEFAULT_THREADS_NUMBER     5

#define SHORTOPT_STR "fdt:D:rT:Ie:h"
#define TOK_FIND_FILES          'f'
#define TOK_FIND_DIRECTORIES    'd'
#define TOK_DATE_TYPE           't'
#define TOK_REVERSE             'r'
#define TOK_DEPTH               'D'
#define TOK_COLOR               'c'
#define TOK_THREADS             'T'
#define TOK_INC_MAX             'I'
#define TOK_EXCLUDE             'e'
#define TOK_NO_EXCLUDE          'E'
#define TOK_FZF                 'F'
#define TOK_FZF_PANE            'P'
#define TOK_FZF_SELECT          'S'
#define TOK_PRINT_CONFIG        'p'
#define TOK_NO_CONFIG           'N'
#define TOK_HELP                'h'

const char* program_name; // just to show in help
static const
struct option long_options[] = {
  {"find-files",       no_argument,       0, TOK_FIND_FILES      },
  {"find-directories", no_argument,       0, TOK_FIND_DIRECTORIES},
  {"date-type",        required_argument, 0, TOK_DATE_TYPE       },
  {"reverse",          no_argument,       0, TOK_REVERSE         },
  {"depth",            required_argument, 0, TOK_DEPTH           },
  {"color",            no_argument,       0, TOK_COLOR           },
  {"threads",          required_argument, 0, TOK_THREADS         },
  {"inc-max-fd",       no_argument,       0, TOK_INC_MAX         },
  {"exclude",          required_argument, 0, TOK_EXCLUDE         },
  {"no-exclude",       no_argument,       0, TOK_NO_EXCLUDE      },
  {"print-config",     no_argument,       0, TOK_PRINT_CONFIG    },
  {"fzf",              no_argument,       0, TOK_FZF             },
  {"fzf-pane",         required_argument, 0, TOK_FZF_PANE        },
  {"fzf-select",       required_argument, 0, TOK_FZF_SELECT      },
  {"no-config",        no_argument,       0, TOK_NO_CONFIG       },
  {"help",             no_argument,       0, TOK_HELP            },
  {0, 0, 0, 0}
};

static
void print_help()
{
#define  STRINGIZING(s)  #s
#define SSTRINGIZING(s)  STRINGIZING(s)
#define DEFAULT_THREADS_NUMBER_STR  SSTRINGIZING(DEFAULT_THREADS_NUMBER)
  printf(
    "%s: find recently modified files or directories.\n"
    "options:\n"
    "  -f, --find-files        : find files (default).\n"
    "  -d, --find-directories  : find directories.\n"
    "  -t, --date-type <str>   : change the sorting criterium, can be `creation`, \n"
    "                            `access`, or `modification` (default: modification).\n"
    "  -D, --depth <int>       : maximum depth of search.\n"
    "  -r, --reverse           : reverse the order.\n"
    "      --color             : colorize output name (toggle on,off).\n"
    "  -T, --threads <int>     : specify the number of threads (default: " DEFAULT_THREADS_NUMBER_STR "),\n"
    "                            high value may not be faster.\n"
    "  -I, --inc-max-fd        : increase the maximum number of files descriptors opened\n"
    "                            at the same time (may be necessary with lot of threads).\n"
    "  -e, --exclude <path>    : exclude directory. `*` match multiple characters, and `?` match one.\n"
    "      --no-exclude        : do not exclude any path.\n"
    "      --fzf               : show in fzf.\n"
    "      --fzf-pane <str>    : activate fzf side pane.    options: `none`, `cat`, `bat`.\n"
    "      --fzf-select <str>  : behaviour after selection. options: `none`, `cat`, `bat`, `git`, `open`.\n"
    "      --print-config      : show configuration.\n"
    "      --no-config         : do not use config file.\n"
    "  -h, --help              : show help.\n\n"

    "config file (default: `"CONFIG_FILE"`):\n"
    "  each line corresponds to an options (and has to start with `-`).\n"
    "  commentary are marked with `#`.\n\n"

    "fzf commands:\n"
    "  ctrl+r  : reload\n"
    "  enter   : select the entry, execute option `fzf-select`.\n"
    , program_name);
}

static inline
struct parsed_options default_options()
{
  static char local_directory[NAME_MAX] = ".";
  char* exclude_list = (char*)calloc(INTIAL_EXCLUDE_LIST_SIZE, sizeof(char));

  return (struct parsed_options){
    .options        = {
      .exclude_list = exclude_list,
      .search_type  = SEARCH_FILES,
      .date_type    = DATE_MODIF,
      .max_depth    = UINT32_MAX,
      },
    .main_directory = local_directory,
    .threads        = DEFAULT_THREADS_NUMBER,
    .reverse_order  = false,
    .color          = false,
    .inc_max_fd     = false,
    .no_exclude     = false,

    .activate_fzf   = false,
    .fzf_pane       = FZF_PANE_NONE,
    .fzf_select     = FZF_SELECT_NONE,

    .parsing_failed = false,
    .print_config   = false,
    .no_config      = false,
    .exclude_list_count = 0,
    .exclude_list_capa  = INTIAL_EXCLUDE_LIST_SIZE
  };
}

static
void print_config(struct parsed_options *options)
{
  const char* true_false_str[] = { "false", "true"};
  const char* fzf_pane_str[]   = { "none", "cat", "bat" };
  const char* fzf_select_str[] = { "none", "cat", "bat", "git", "open" };
  const char* date_type_str[]  = { "creation", "access", "modification" };

  printf("search_type:    %s \n", (options->options.search_type == SEARCH_FILES) ? "file" : "directories");
  printf("date_type:      %s \n",  date_type_str[options->options.date_type]);
  printf("max_depth:      %lu\n",  options->options.max_depth);
  printf("main_directory: `%s`\n", options->main_directory);
  printf("threads:        %u \n",  options->threads);
  printf("reverse_order:  %s \n",  true_false_str[options->reverse_order]);
  printf("fzf:            %s \n",  true_false_str[options->activate_fzf]);
  printf("fzf-pane:       %s \n",  fzf_pane_str[options->fzf_pane]);
  printf("fzf-select:     %s \n",  fzf_select_str[options->fzf_select]);
  printf("color:          %s \n",  true_false_str[options->color]);
  printf("inc_max_fd:     %s \n",  true_false_str[options->inc_max_fd]);
  printf("no_exclude:     %s \n",  true_false_str[options->no_exclude]);
  char* cur = options->options.exclude_list;
  while(*cur != '\0') {
    printf("exclude:        `%s`\n", cur);
    cur += strlen(cur) + 1;
  } 
}

static inline
void push_exclude_path(struct parsed_options *options, const char* path)
{
  uint32_t *count = &options->exclude_list_count;
  uint32_t *capa  = &options->exclude_list_capa;
  char** exclude_list = &options->options.exclude_list;
  char buf[NAME_MAX];
  size_t len = 0;

  for(const char* cur=path;; cur++)
  {
    // trim '/' at the end
    if(*cur == '/'){
      while(*++cur == '/');
      if(*cur != '\0'){
        fprintf(stderr, "subdirectories are not supported in exclude path: `%s`\n", path);
        options->parsing_failed = true;
        return;
      }
    }
    if(*cur == '\0') break;
    buf[len++] = *cur;
    
    // remove supernumerary '*'
    if(*cur == '*')
      while(cur[1] == '*') cur++;
  }
  if(len==1 && *buf == '*'){
    fprintf(stderr, "cannot exclude a single star operator: `%s`\n", path);
    options->parsing_failed = true;
    return;
  }
  buf[len++] = '\0';

  if(*count + len + 1>= *capa){
    *exclude_list = (char*)realloc(*exclude_list, *capa * 2);
    *capa *= 2;
  }
  memcpy(*exclude_list + *count, buf, len*sizeof(char));
  *count += len;
}

static inline
void parse_arg(struct parsed_options *options, int arg)
{
  #define IF_ARG_MATCH(opt, match, val)                     \
      if(!strncmp(optarg, match, strlen(optarg))) opt = val;

  switch (arg)
  {
    case TOK_FIND_FILES: // find-files
      options->options.search_type = SEARCH_FILES;
      break;
    case TOK_FIND_DIRECTORIES: // find-directories
      options->options.search_type = SEARCH_DIRECTORIES;
      break;
    case TOK_DATE_TYPE: // date-type
           IF_ARG_MATCH(options->options.date_type, "access",       DATE_ACCESS)
      else IF_ARG_MATCH(options->options.date_type, "creation",     DATE_CREAT)
      else IF_ARG_MATCH(options->options.date_type, "modification", DATE_MODIF)
      else {
        fprintf(stderr, "bad argument for date-type: `%s`. options: `creation`, `access`, `modification`.\n", optarg);
        options->parsing_failed = true;
      }
      break;
    case TOK_REVERSE: // reverse
      options->reverse_order = !options->reverse_order; 
      break;
    case TOK_DEPTH: // depth
      options->options.max_depth = atoi(optarg); 
      break;
    case TOK_COLOR: // color
      options->color = !options->color;
      break;
    case TOK_THREADS: // threads
      options->threads = atoi(optarg);
      break;
    case TOK_INC_MAX: // inc-max-fd
      options->inc_max_fd = true;
      break;
    case TOK_EXCLUDE: // exclude
      push_exclude_path(options, optarg);
      break;
    case TOK_NO_EXCLUDE: // no-exclude
      options->no_exclude = true;
      break;
    case TOK_FZF: // fzf
      options->activate_fzf = true;
      break;
    case TOK_FZF_PANE: // fzf-pane
           IF_ARG_MATCH(options->fzf_pane, "none", FZF_PANE_NONE)
      else IF_ARG_MATCH(options->fzf_pane, "cat",  FZF_PANE_CAT)
      else IF_ARG_MATCH(options->fzf_pane, "bat",  FZF_PANE_BAT)
      else {
        fprintf(stderr, "bad argument for fzf-pane: `%s`. options: `none`, `cat`, `bat`.\n", optarg);
        options->parsing_failed = true;
      }
      break;
    case TOK_FZF_SELECT: // fzf-select
           IF_ARG_MATCH(options->fzf_select, "none", FZF_SELECT_NONE)
      else IF_ARG_MATCH(options->fzf_select, "cat",  FZF_SELECT_CAT)
      else IF_ARG_MATCH(options->fzf_select, "bat",  FZF_SELECT_BAT)
      else IF_ARG_MATCH(options->fzf_select, "git",  FZF_SELECT_GIT)
      else IF_ARG_MATCH(options->fzf_select, "open", FZF_SELECT_OPEN)
      else {
        fprintf(stderr, "bad argument for fzf-select: `%s`. options: `none`, `cat`, `bat`, `git`, `open`.\n", optarg);
        options->parsing_failed = true;
      }
      break;
    case TOK_PRINT_CONFIG: // help
      options->print_config = true;
      break;
    case TOK_NO_CONFIG: // remove config file
      if(!options->no_config){
        const bool parsing_failed = options->parsing_failed;
        free(options->options.exclude_list);
        *options = default_options();
        options->no_config = true;
        options->parsing_failed = parsing_failed;
        optind = 0; // reset getopt once
      }
      break;
    case TOK_HELP:
      print_help();
      exit(0);
  }
}

static
void parse_config_files(struct parsed_options *options)
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

  int fd = open(config_file, O_RDWR);
  if(fd<0) return;

  struct stat64 stat;
  fstat64(fd, &stat);
  if(stat.st_size == 0) return; // empty file
  char* config_raw = (char*) mmap64(NULL, (stat.st_size+1)*sizeof(char), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  config_raw[stat.st_size] = '\0';
  // config_raw[stat.st_size+1] = '\0'; // TODO remove
  int config_capa = 32, config_argc = 0;
  char** config_argv = (char**)malloc(config_capa * sizeof(char*));
  config_argv[config_argc] = config_raw; // dummy argv[0] 

  // remove comments by filling space
  for(char* cur=config_raw; *cur != '\0'; cur++){
    if(*cur == '#')
      while(*cur != '\n' && *cur != '\0')
        *cur++ = ' ';
  }

  // fill argv
  {
    char *saveptr_quote;
    char *str_quote = config_raw;
    bool is_inside_quote = false;
    for(char *token_quote;; str_quote=NULL) {
      // don't distinguish between different quote symbol, much easier to implement
      token_quote = strtok_r(str_quote, "'\"", &saveptr_quote);
      if(token_quote == NULL)
        break;
      if(is_inside_quote%2) { // is inside a quote
        config_argv[++config_argc] = token_quote;
      }
      else { // is not inside a quote
        char *token = strtok(token_quote, " \t\n"); // split args
        while(token != NULL) {
          config_argv[++config_argc] = token;
          token = strtok(NULL, " \t\n");

          // extend config_argv if necessary (keep space for the next quote block and NULL)
          if(config_argc + 2 > config_capa){
            config_capa *= 2;
            config_argv = (char**)realloc(config_argv, config_capa * sizeof(char*));
          }
        }
      }
      is_inside_quote=!is_inside_quote;
    }
    if(!is_inside_quote) {
      *strchrnul(config_argv[config_argc], '\n') = '\0'; 
      fprintf(stderr, "error in config file, unfinished quote: %s\n", config_argv[config_argc]);
      options->parsing_failed = true;
    }
    config_argv[++config_argc] = NULL;
  }


  // TODO rm
  // for(char** c=config_argv; *c!=NULL; c++)
  //   printf("%s\n", *c);
  // // for(int i=0; i<config_argc; i++)
  // //   printf("%s\n", config_argv[i]);
  // exit(0);
  
  // process options
  while(1) {
    int arg = getopt_long_only(config_argc, config_argv, SHORTOPT_STR, long_options, NULL);
    if(arg == -1)
      break;
    else if(arg == '?'){
      options->parsing_failed = true;
    }
    parse_arg(options, arg);
  }
  if(config_argc != optind){
    fprintf(stderr, "error in config file, commands has to start with `-`.\n");
    options->parsing_failed = true;
  }
  optind=0; // reset getopt for next use of getopt

  free(config_argv);
  munmap(config_raw, stat.st_size*sizeof(char));
  close(fd);

  options->no_config = false; // prevent to not be able to use no_config via options in case it was put in the config file.
}

struct parsed_options parse_options(int argc, char** argv)
{
  program_name = *argv;
  struct parsed_options options = default_options();
  
  // process config file
  parse_config_files(&options);
  if(options.parsing_failed) {
    fprintf(stderr, "error in the config file `"CONFIG_FILE"`\n");
    exit(1);
  } 

  // process options
  while(1) {
    int arg = getopt_long_only(argc, argv, SHORTOPT_STR, long_options, NULL);
    if(arg == -1)
      break;
    else if(arg == '?')
      options.parsing_failed = true;
    parse_arg(&options, arg);
  }

  // post process
  if (optind < argc-1) { // reset getopt
    fprintf(stderr, "too many options given: ");
    while (optind < argc)
      fprintf (stderr, "`%s` ", argv[optind++]);
    fprintf (stderr, "\n");
    options.parsing_failed = true;
  }
  else if (optind == argc-1)
    options.main_directory = argv[optind];

  if(options.no_exclude)
    *options.options.exclude_list = '\0';

  if(options.parsing_failed) {
    fprintf(stderr, "error in command line options.\n");
    exit(1);
  } 

  if(options.print_config){
    print_config(&options);
    exit(0);
  }

  omp_set_num_threads(options.threads);
  
  if(options.inc_max_fd) {
    // increase maximum number of file descriptor opened at the same time. prevent crash when there are to many threads 
    struct rlimit rl;
    check(getrlimit(RLIMIT_NOFILE, &rl));
    rl.rlim_cur = rl.rlim_max;
    check(setrlimit(RLIMIT_NOFILE, &rl));
  }

  return options;
}
