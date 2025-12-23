#include "defs.h"

int main(int argc, char** argv)
{
  struct options options = parse_options(argc, argv);
  
  if(isatty(STDOUT_FILENO) && options.fzf_activate)
    launch_in_fzf(argv, &options);
    
  struct list_entries l = findrecent(&options);

  print_list_entry(&l, &options);

  free_list_entries(&l);
  free(options.exclude_list);
  return 0;
}
