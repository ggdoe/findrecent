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

#define INTIAL_EXCLUDE_LIST_SIZE   4096
#define CONFIG_FILE  "~/.config/findrecent/findrecent.conf"
#define DEFAULT_THREADS_NUMBER     4
#define DEFAULT_TASK_THRESHOLD     2 // minimum number of links in a subdirectory to launch a new openmp task
#define PRGM_VERSION               "1.3"

#define GETDENTS_BUFSIZE     (32768)   // size of the buffer for the getdents syscall, allocated on the stack for each subdirectories explored, be aware of stack overflow (see in findrecent.c to change for heap allocated buffer)
#define INNER_BUFSIZE        (32768)   // minimum: 256 (=NAME_MAX)
#define INITIAL_ENTRIES_SIZE (32768)   // initial size of the number of entries allocation (for each thread)

#define check(v)    if(v < 0)     { perror(NULL); exit(1); }
#define checkptr(p) if(p == NULL) { perror(NULL); exit(1); }

#define OPEN_FLAGS        (O_RDONLY|O_NOCTTY|O_NONBLOCK|O_NOFOLLOW|O_CLOEXEC|O_DIRECTORY)

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
  union {
    struct statx_timestamp date;
    size_t size;
  };
  struct filename *name;
  const char* color;
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

enum sort_type {
  SORT_CHANGE = STATX_CTIME,
  SORT_ACCESS = STATX_ATIME,
  SORT_MODIF  = STATX_MTIME,
  SORT_BIRTH  = STATX_BTIME,
  SORT_SIZE   = STATX_SIZE
};

enum search_type {
  SEARCH_FILES=DT_REG, 
  SEARCH_DIRECTORIES=DT_DIR
};

enum fzf_pane {
  FZF_PANE_NONE=0,
  FZF_PANE_CAT,
  FZF_PANE_BAT
};

enum fzf_select {
  FZF_SELECT_NONE=0,
  FZF_SELECT_CAT,
  FZF_SELECT_BAT,
  FZF_SELECT_GIT,
  FZF_SELECT_OPEN,
  FZF_SELECT_EXEC
};

struct options {
  enum search_type search_type;
  enum sort_type sort_type;
  char* exclude_list;
  size_t max_depth;
  uint64_t task_threshold;
  
  char* main_directory;
  uint32_t threads;
  bool reverse_order;
  bool hide_date;
  bool color;
  bool no_exclude;
  bool inc_max_fd;

  bool fzf_activate;
  bool fzf_wrap_entry;
  bool fzf_search_date;
  uint32_t fzf_shorten_name;
  enum fzf_pane fzf_pane;
  enum fzf_select fzf_select;

  // private
  uint32_t exclude_list_count;
  uint32_t exclude_list_capa;
  bool print_config;
  bool parsing_failed;
  bool no_config;
};

struct list_entries findrecent(const struct options *options);
struct list_entries merge_sort_list_task(struct list_task *lt, int nb_threads);
void print_list_entry(struct list_entries *restrict l, struct options *restrict options);
void free_list_entries(struct list_entries *l);
struct filename *push_buffer_filename(struct list_entries *restrict l, struct filename *restrict pred, const char *restrict name);
void push_entry(struct list_entries *restrict l, const char *restrict filename, struct filename *restrict pred, struct statx *restrict s, enum sort_type type);

struct options parse_options(int argc, char** argv);
void launch_in_fzf(char** argv, struct options *options);

#endif // _DEFS_H_
