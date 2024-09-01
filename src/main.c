#include "defs.h"

int main(int argc, char** argv)
{
  struct parsed_options options = parse_options(argc, argv);
  
  if(isatty(STDOUT_FILENO) && options.activate_fzf)
    launch_in_fzf(argv, &options);
    
  struct list_entries l = findrecent(options.main_directory, &options.options);

  print_list_entry(&l, &options);

  free_list_entries(&l);
  free(options.options.exclude_list);
  return 0;
}
