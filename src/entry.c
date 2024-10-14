#include "defs.h"
#include <time.h>
#include "colormap.h"

void push_entry(struct list_entries *restrict l, const char *restrict filename, struct filename *restrict pred, struct stat64 *restrict s, enum sort_type type)
{
  size_t n = l->n++;
  if(n >= l->cap) {
    l->entries = (struct entry*)realloc(l->entries, l->cap*2 * sizeof(struct entry));
    checkptr(l->entries);
    l->cap *= 2;
  }

  struct entry *e = &l->entries[n];
  switch (type)
  {
  case SORT_CREAT:
    e->date = s->st_ctim; // creation
    break;
  case SORT_ACCESS:
    e->date = s->st_atim; // last access
    break;
  case SORT_MODIF: default:
    e->date = s->st_mtim; // last modif
    break;
  case SORT_SIZE:
    e->size = s->st_size; // size
    break;
  }

  e->name = push_buffer_filename(l, pred, filename);

  // color
  if(s->st_mode & S_IEXEC) {
    e->color = COLOR_EXEC;
    return;
  }
  const char* ext = strrchr(filename, '.'); // search extension
  if(ext == NULL)
    ext = filename;
  else 
    ext = ext+1;
  const size_t len = strlen(ext);
  e->color = get_color(ext, len);
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

static
int print_dirname_color(struct filename *f, int depth)
{
  if(f->pred == NULL){
    printf("%s", f->name);
    return (uint8_t)(DIR_COLOR_FUNCTION(depth)); // color code is function of depth max
  }
  const uint8_t color_val = print_dirname_color(f->pred, depth+1);
  printf("\033[38;5;%dm/%s", color_val, f->name);

  return color_val;
}

static inline
void print_entry_info(struct entry *e, enum sort_type sort_type)
{
  switch (sort_type) {
    case SORT_SIZE: {
      size_t id=0;
      size_t size = e->size;
      char symbols[] = {'B', 'K', 'M', 'G', 'T', 'P'}; 
      for(; (size>>(10*id))>=1024 && id < sizeof(symbols)/sizeof(char); id++);
      printf("%10.2lf%c:  ", (double)size/(1<<(10*id)), symbols[id]); 
      break;
    }
    default: {
      char buffer[32];
      const size_t fixed_length = 27;
      ctime_r(&e->date.tv_sec, buffer); // ctime put a newline at end
      const size_t len = strlen(buffer);
      buffer[len-1] = ':';
      for(size_t i=len; i<fixed_length; i++)
        buffer[i] = ' ';
      buffer[fixed_length] = '\0';
      printf("%s", buffer);
      break;
    }
  }
}

void print_list_entry(struct list_entries *restrict l, struct parsed_options *restrict options)
{
  const bool reverse_order = options->reverse_order;
  const bool activate_color = options->color;
  const enum search_type search_type = options->options.search_type;
  size_t n = l->n;

  for(size_t i=0; i<n; i++){
    struct entry *e = (!reverse_order) ? &l->entries[i] : &l->entries[n - 1 - i];
    print_entry_info(e, options->options.sort_type);

    if(activate_color && search_type == SEARCH_DIRECTORIES) {
      print_dirname_color(e->name, 0);
      printf("\033[0m");
      putchar('\n');
    }
    else {
      if(activate_color) printf("\033[%sm", e->color);
      print_filename(e->name);
      if(activate_color) printf("\033[0m");
      putchar('\n');
    }
  }
}

void free_list_entries(struct list_entries *l)
{
  for(size_t i=0; i<l->buffer.n; i++)
    free(l->buffer.b[i]);
  free(l->buffer.b);
  free(l->entries);
}