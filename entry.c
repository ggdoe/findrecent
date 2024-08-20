#include "defs.h"
#include <sys/stat.h>

void push_entry(struct list_entries *restrict l, const char *restrict filename, int fd, struct filename *restrict pred, enum date_type type)
{
  size_t n = l->n++;
  if(n >= l->cap) {
    l->entries = (struct entry*)realloc(l->entries, l->cap*2 * sizeof(struct entry));
    checkptr(l->entries);
    l->cap *= 2;
  }

  struct entry *e = &l->entries[n];

  struct stat64 s;
  int ret = fstatat64(fd, filename, &s, 0);
  check(ret);

  switch (type)
  {
  case DATE_CREAT:
    e->date = s.st_ctim; // creation
    break;
  case DATE_ACCESS:
  e->date = s.st_atim; // last access
    break;
  case DATE_MODIF: default:
  e->date = s.st_mtim; // last modif
    break;
  }

  e->name = push_buffer_filename(l, pred, filename);
}

static
void print_filename(struct filename *f)
{
  if(f->pred == NULL){
    printf("%s", f->name);
    return;
  }
  print_filename(f->pred);
  printf("/%s", f->name);
}

void print_list_entry(struct list_entries *l)
{
  struct entry *e = l->entries; 
  for(size_t i=0; i<l->n; i++){
    print_filename(e[i].name);
    printf("\t%lu.%lu", e[i].date.tv_sec, e[i].date.tv_nsec);
    putchar('\n');
  }
}

void free_list_entries(struct list_entries *l)
{
  for(size_t i=0; i<l->buffer.n; i++)
    free(l->buffer.b[i]);
  free(l->buffer.b);
  free(l->entries);
}