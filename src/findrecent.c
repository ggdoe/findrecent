#include "defs.h"
// #define ACTIVATE_HEAP_ALLOCATED_BUFFER

struct linux_dirent64 {
    ino64_t        d_ino;    /* 64-bit inode number */
    off64_t        d_off;    /* 64-bit NOT an offset to next structure */
    unsigned short d_reclen; /* Size of this dirent */
    unsigned char  d_type;   /* File type */
    char           d_name[]; /* Filename (null-terminated) */
};

static struct list_entries init_list_entries();
static void findrecent_work(struct list_task *restrict lt, int fd, struct filename *restrict path, const struct work_options *restrict options, const size_t depth);
static inline bool match(const char *pattern, const char *str);
static inline bool is_path_excluded(char* exclude_list, const char* filename);

struct list_entries findrecent(char *restrict directory, const struct work_options *restrict options)
{
  int nb_threads = omp_get_max_threads();
  struct list_task lt;
  lt.l = (struct list_entries*) malloc(nb_threads * sizeof(struct list_entries));
  for(int i=0; i<nb_threads; i++)
    lt.l[i] = init_list_entries();

  int fd = open64(directory, OPEN_FLAGS);
  check(fd);
  
  struct stat64 s;
  int ret = fstat64(fd, &s);
  check(ret);

  // remove a '/' when necessary to get the same output as 'find'
  size_t len = strlen(directory)-1;
  if(len > 1 && directory[len] == '/') directory[len] = '\0'; 
  if(*directory == '/') *directory = '\0'; // remove supernumenary '/' at the start
  
  struct filename *path;
  switch(options->search_type)
  {
    case SEARCH_FILES: default:
      path = push_buffer_filename(&lt.l[0], NULL, directory);
    break; 
    case SEARCH_DIRECTORIES:
      push_entry(&lt.l[0], directory, NULL, &s, options->date_type);
      path = lt.l[0].entries[0].name;
    break;
  }

  #pragma omp parallel
  #pragma omp single
  {
    findrecent_work(&lt, fd, path, options, 0);
  }

  struct list_entries l = merge_sort_list_task(&lt, nb_threads);
  free(lt.l);
  return l;
}

void findrecent_work(struct list_task *restrict lt, int fd, struct filename *restrict path, const struct work_options *restrict options, const size_t depth)
{
  if(depth > options->max_depth) return;

  #ifndef ACTIVATE_HEAP_ALLOCATED_BUFFER
  char buf[GETDENTS_BUFSIZE];
  #else
  char* buf = (char*)malloc(GETDENTS_BUFSIZE * sizeof(char));
  #endif

  struct list_entries *l = &lt->l[omp_get_thread_num()];

  for(;;)
  {
    int count = getdents64(fd, buf, GETDENTS_BUFSIZE);
    if(count <= 0) break;

    struct linux_dirent64* d;
    for(int off=0; off<count; off += d->d_reclen)
    {
      d = (struct linux_dirent64*)(buf + off);
      const char* filename = d->d_name;
      
      if(is_path_excluded(options->exclude_list, filename)) continue;

      if(d->d_type == options->search_type || d->d_type == DT_DIR){
        struct stat64 s;
        int ret = fstatat64(fd, filename, &s, 0);
        // check(ret);
        if(ret < 0) { 
          // ignore permissions denied
          if(errno == EACCES || errno == ENOENT) continue; 
          perror(NULL); exit(1); 
        }

        if(d->d_type == options->search_type){
          push_entry(l, filename, path, &s, options->date_type);
        }
        if(d->d_type == DT_DIR)
        {
          struct filename *nextpath = push_buffer_filename(l, path, filename);
          int newfd = openat64(fd, filename, OPEN_FLAGS);
          if(newfd < 0) { 
            // ignore permissions denied
            if(errno == EACCES || errno == ENOENT) continue; 
            perror(NULL); exit(1); 
          }
          
          if(s.st_nlink >= TASK_LINKS_THRESHOLD){
            #pragma omp task
            findrecent_work(lt, newfd, nextpath, options, depth+1);
          }
          else{
            findrecent_work(lt, newfd, nextpath, options, depth+1);
          }
        }
      }
    }

    // all file in the directory have been listed
    if(d->d_off == 0x7fffffffffffffff) break;
  }
  close(fd);
  #ifdef ACTIVATE_HEAP_ALLOCATED_BUFFER
  free(buf);
  #endif
}

struct list_entries init_list_entries()
{
  struct list_entries l;
  l.entries = (struct entry*)malloc(INITIAL_ENTRIES_SIZE * sizeof(struct entry));
  checkptr(l.entries);
  l.n = 0;
  l.cap = INITIAL_ENTRIES_SIZE;

  struct buffer *buffer = &l.buffer;
  buffer->b = (struct inner_buffer**) malloc(sizeof(struct inner_buffer*));
  checkptr(buffer->b);
  buffer->n = 1;
  (*buffer->b) = (struct inner_buffer*) malloc(sizeof(struct inner_buffer));
  checkptr(*buffer->b);
  (*buffer->b)->n = 0;

  return l;
}

bool is_path_excluded(char* exclude_list, const char* filename)
{
  if(!strcmp(filename, ".") || !strcmp(filename, "..")) return true;

  char* exclude = exclude_list;
  while(*exclude != '\0'){
    if(match(exclude, filename)){
      return true;
    }

    exclude += strlen(exclude) + 1;
  }
  return false;
}

// match 'pattern' and 'str', 'pattern' can countain operators `*` and `?` to match multiple characters
bool match(const char *pattern, const char *str) {
  while(*str) {
    if(*pattern == '*') {
      pattern++;
      if(*pattern == '\0')
        return true;
      while(*str) {
        if(match(pattern, str))
          return true;
        str++;
      }
      return false;
    }
    if(*pattern != *str && *pattern != '?')
        return false;
    pattern++;
    str++;
  }

  if(*pattern == '*')
    pattern++;

  return *pattern == '\0';
}
