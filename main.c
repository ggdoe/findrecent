#include "defs.h"

// #define BENCH_PRECISION µs
// #define BENCH_LOG_SIZE 1
// #include "bench.h"

struct options parse_options(int argc, char** argv, char **main_directory)
{
  char local_directory[NAME_MAX] = ".";
  char* path = local_directory;
  if(argc>1) path = argv[1];

  struct options opt;
  opt.date_type = DATE_MODIF;
  // opt.date_type = DATE_CREAT;
  // opt.date_type = DATE_ACCESS;
  opt.search_type = SEARCH_FILES;
  // opt.search_type = SEARCH_DIRECTORIES;

}

int main(int argc, char** argv)
{
  // char cwd[256];
  // getcwd(cwd, 256);
  char* main_directory;
  struct options options = parse_options(argc, argv, &main_directory);

  // BENCH_BENCH(BENCH_LOG_SIZE,
  // BENCH_START;
  struct list_entries l = findrecent(main_directory, &options);
  // BENCH_LOG;
  // BENCH_PRINT;
  // findrecent("/home/elrond");
  // );
  // BENCH_PRINT

  print_list_entry(&l);  
  free_list_entries(&l);
  return 0;
}
