#ifndef _DEFS_H_
#define _DEFS_H_
#define _GNU_SOURCE
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define GETDENTS_BUFSIZE     (32768)   // size of the buffer for the getdents syscall, allocated on the stack for each subdirectories explored, be aware of stack overflow, may change it for heap allocation
#define INNER_BUFSIZE        (32768)   // minimum: 256 (=NAME_MAX)
#define INITIAL_ENTRIES_SIZE (32768)   // initial size of the number of entries allocation (for each thread)
#define TASK_LINKS_THRESHOLD (12)      // minimum number of links in a subdirectory to launch a new openmp task

#define check(v)    if(v < 0)     { perror(NULL); exit(1); }
#define checkptr(p) if(p == NULL) { perror(NULL); exit(1); }

#define OPEN_FLAGS           O_DIRECTORY
// #define OPEN_FLAGS        O_RDONLY|O_NOCTTY|O_NONBLOCK|O_NOFOLLOW|O_CLOEXEC|O_DIRECTORY

struct inner_buffer{
  char mem[INNER_BUFSIZE];
  size_t n;
};

struct buffer{
  struct inner_buffer **b;
  size_t n;
};

struct filename{
  struct filename* pred;
  const char* name;
};

struct entry {
  struct timespec date;
  struct filename *name;
  size_t color;
};

struct list_entries {
  struct buffer buffer;
  struct entry *entries;
  size_t n;
  size_t cap;
};

struct list_task {
  struct list_entries *l;
};

enum date_type {
  DATE_CREAT,
  DATE_ACCESS,
  DATE_MODIF
};

enum search_type {
  SEARCH_FILES=DT_REG, 
  SEARCH_DIRECTORIES=DT_DIR
};

struct options {
  enum search_type search_type;
  enum date_type date_type;
  char* exclude_list;
  size_t max_depth;
};

struct parsed_options
{
  struct options options;
  char *main_directory;
  bool activate_color;
  bool reverse_order;
  bool activate_fzf;
};

struct list_entries findrecent(char *restrict directory, const struct options *restrict options);
struct list_entries merge_sort_list_task(struct list_task *lt, int nb_threads);
void print_list_entry(struct list_entries *l, bool reverse_order, bool activate_color);
void free_list_entries(struct list_entries *l);
struct filename *push_buffer_filename(struct list_entries *restrict l, struct filename *restrict pred, const char *restrict name);
void push_entry(struct list_entries *restrict l, const char *restrict filename, struct filename *restrict pred, struct stat64 *restrict s, enum date_type type);

struct parsed_options parse_options(int argc, char** argv);

#endif // _DEFS_H_
