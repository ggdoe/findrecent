#include "defs.h"

// #define BENCH_fd stderr
// #define BENCH_PRECISION ms
// #define BENCH_LOG_SIZE 1
// #include "bench.h"

int main(int argc, char** argv)
{
  struct parsed_options options = parse_options(argc, argv);
  
  if(isatty(STDOUT_FILENO) && options.activate_fzf)
    launch_in_fzf(argv, &options);
    
  struct list_entries l = findrecent(options.main_directory, &options.options);

  print_list_entry(&l, &options);

  free_list_entries(&l);
  if(!options.options.exclude_list) 
    free(options.options.exclude_list);
  return 0;
}
