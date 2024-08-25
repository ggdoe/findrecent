#include "defs.h"
#include <time.h>
#include "color_list.h"

void push_entry(struct list_entries *restrict l, const char *restrict filename, struct filename *restrict pred, struct stat64 *restrict s, enum date_type type)
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
  case DATE_CREAT:
    e->date = s->st_ctim; // creation
    break;
  case DATE_ACCESS:
  e->date = s->st_atim; // last access
    break;
  case DATE_MODIF: default:
  e->date = s->st_mtim; // last modif
    break;
  }

  e->name = push_buffer_filename(l, pred, filename);

  // color
  if(s->st_mode & S_IEXEC) {
    e->color = COLOR_EXEC;
    return;
  }
  char* ext = strrchr(filename, '.');
  if(ext) {
    ext += 1; // remove '.'
    for(size_t i=0; i<sizeof_color_list; i++) {
      if(!strcmp(ext, color_list[i].ext)){
        e->color = i;
        return;
      }
    }
  }
  e->color = COLOR_DEFAULT;
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
    return (uint8_t)(DIR_COLOR_FUNCTION(depth)); // color code in function of depth max
  }
  const uint8_t color_val = print_dirname_color(f->pred, depth+1);
  printf("\033[38;5;%dm/%s", color_val, f->name);

  return color_val;
}

static inline
void print_date(struct entry *e)
{
  char buffer[32];
  const size_t fixed_length = 27;
  struct tm *tm = localtime(&e->date.tv_sec);
  // strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
  strftime(buffer, sizeof(buffer), "%c", tm);
  for(size_t i=strlen(buffer); i<fixed_length; i++)
    buffer[i] = ' ';
  buffer[fixed_length] = '\0';
  printf("%s", buffer);
}

void print_list_entry(struct list_entries *restrict l, struct parsed_options *restrict options)
{
  const bool reverse_order = options->reverse_order;
  const bool activate_color = options->color;
  const enum search_type search_type = options->options.search_type;
  size_t n = l->n;

  for(size_t i=0; i<n; i++){
    struct entry *e = (!reverse_order) ? &l->entries[i] : &l->entries[n - 1 - i];
    print_date(e);
    if(activate_color && search_type == SEARCH_DIRECTORIES) {
      print_dirname_color(e->name, 0);
      printf("\033[0m\n");
    }
    else {
      if(activate_color) printf("\033[%sm", color_list[e->color].color);
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