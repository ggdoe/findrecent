#include "defs.h"

// #define BENCH_PRECISION µs
// #define BENCH_LOG_SIZE 1
// #include "bench.h"

//BUGS:
  // gérer les "permission denied" par exemple lorsqu'on par de la racine /

int main(int argc, char** argv)
{
  // char cwd[256];
  // getcwd(cwd, 256);
  struct parsed_options parsed = parse_options(argc, argv);

  // BENCH_BENCH(BENCH_LOG_SIZE,
  // BENCH_START;
  struct list_entries l = findrecent(parsed.main_directory, &parsed.options);
  // BENCH_LOG;
  // BENCH_PRINT;
  // findrecent("/home/elrond");
  // );
  // BENCH_PRINT

// TODO: color, fzf, depth

  print_list_entry(&l, parsed.reverse_order, parsed.activate_color);  
  free_list_entries(&l);
  if(!parsed.options.exclude_list) 
    free(parsed.options.exclude_list);
  return 0;
}
