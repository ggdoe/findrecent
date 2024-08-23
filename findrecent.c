#include "defs.h"

struct linux_dirent64 {
    ino64_t        d_ino;    /* 64-bit inode number */
    off64_t        d_off;    /* 64-bit NOT an offset to next structure */
    unsigned short d_reclen; /* Size of this dirent */
    unsigned char  d_type;   /* File type */
    char           d_name[]; /* Filename (null-terminated) */
};

static struct list_entries init_list_entries();
static void findrecent_work(struct list_task *restrict lt, int fd, struct filename *restrict path, const struct options *options);


struct list_entries findrecent(char *directory, const struct options *options)
{
  int nb_threads = omp_get_max_threads();
  struct list_task lt;
  lt.l = (struct list_entries*) malloc(nb_threads * sizeof(struct list_entries));
  for(int i=0; i<nb_threads; i++)
    lt.l[i] = init_list_entries();

  int fd = open64(directory, OPEN_FLAGS);
  check(fd);
  
  // remove a '/' when necessary to get the same output as 'find'
  size_t len = strlen(directory)-1;
  if(len > 1 && directory[len] == '/') directory[len] = '\0'; 
  
  struct filename *path;
  switch(options->search_type)
  {
    case SEARCH_FILES: default:
      path = push_buffer_filename(&lt.l[0], NULL, directory);
    break; 
    case SEARCH_DIRECTORIES:
      push_entry(&lt.l[0], directory, fd, NULL, options->date_type);
      path = lt.l[0].entries[0].name;
    break;
  }

  #pragma omp parallel
  #pragma omp single
  {
    findrecent_work(&lt, fd, path, options);
  }

  struct list_entries l = merge_sort_list_task(&lt, nb_threads);
  free(lt.l);
  return l;
}

// static inline
// bool is_path_excluded(char* exclude_list, const char* filename)
// {
//   if(!strcmp(filename, ".") || !strcmp(filename, "..")) return true;
  
//   char* cur = exclude_list;
//   while(*cur != '\0'){
//     size_t len = strlen(cur);
//     if(!strncmp(filename, cur, len)) {
//       return true;
//     }
//     cur += len + 1;
//   }
//   return false;
// }

// check star
static inline
bool is_path_excluded(char* exclude_list, const char* filename)
{
  if(!strcmp(filename, ".") || !strcmp(filename, "..")) return true;

#if 0
  char* cur_exclude = exclude_list;
  while(*cur_exclude != '\0'){
    size_t len_cur = strlen(cur_exclude);
    size_t len = (len_cur > strlen(filename)) ? len_cur : strlen(filename);
    
    fwrite(cur_exclude, sizeof(char), len_cur, stdout);
    printf("\t%s %25s\n", filename, !strncmp(filename, cur_exclude, len) ? "--> \033[1;31mKILL\033[0;0m" : "");

    if(!strncmp(filename, cur_exclude, len)) {
      return true;
    }
    cur_exclude += len_cur + 1;
  }
  return false;
#else
  char* exclude = exclude_list;
  while(*exclude != '\0'){
    const char *cur_filename = filename;
    char *cur_exclude = exclude;

    while(*cur_filename == *cur_exclude){
      if(*cur_exclude == '*')
      {
        unfinished
      }
      cur_exclude++;
      cur_filename++;
      if(*cur_filename == '\0' && *cur_exclude == '\0'){
    printf("`");
    fwrite(exclude, sizeof(char), strlen(exclude), stdout);
    printf("`\t`%s` --> \033[1;31mMATCH\033[0;0m\n", filename);
        return true;
      }
    } // failed to match, try next excluded

    printf("`");
    fwrite(exclude, sizeof(char), strlen(exclude), stdout);
    printf("`\t`%s`\n", filename);

    exclude += strlen(exclude) + 1;
  }
  return false;

#endif
}

void findrecent_work(struct list_task *restrict lt, int fd, struct filename *restrict path, const struct options *options)
{
  char buf[GETDENTS_BUFSIZE];

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

      if(d->d_type == options->search_type){
        push_entry(l, filename, fd, path, options->date_type);
      }
      if(d->d_type == DT_DIR)
      {
        struct filename *nextpath = push_buffer_filename(l, path, filename);
        int newfd = openat64(fd, filename, OPEN_FLAGS);
        check(newfd);
        
        #pragma omp task
        findrecent_work(lt, newfd, nextpath, options);
      }
    }

    // all file in the directory have been listed
    if(d->d_off == 0x7fffffffffffffff) break;
  }
  close(fd);
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
