#include "defs.h"
#include <time.h>
#include "colormap.h"

void push_entry(struct list_entries *restrict l, const char *restrict filename, struct filename *restrict pred, struct statx *restrict s, enum sort_type type)
{
  size_t n = l->n++;
  if(n >= l->cap) {
    l->entries = (struct entry*)realloc(l->entries, l->cap*2 * sizeof(struct entry));
    checkptr(l->entries);
    memset(l->entries + l->cap, 0, l->cap * sizeof(struct entry));
    l->cap *= 2;
  }

  struct entry *e = &l->entries[n];
  switch (type)
  {
  case SORT_CHANGE:
    e->date = s->stx_ctime; // change
    break;
  case SORT_ACCESS:
    e->date = s->stx_atime; // last access
    break;
  case SORT_MODIF: default:
    e->date = s->stx_mtime; // last modif
    break;
  case SORT_BIRTH:
    e->date = s->stx_btime; // creation
    break;
  case SORT_SIZE:
    e->size = s->stx_size; // size
    break;
  }

  e->name = push_buffer_filename(l, pred, filename);

  // color
  if(s->stx_mode & S_IEXEC) {
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
void print_filename(struct filename *f, uint32_t count)
{
  if(f->pred == NULL){
    printf("%s", f->name);
    return;
  }
  if (count == 1) {
    printf(".../%s", f->name);
    return;
  }
  print_filename(f->pred, count-1);
  printf("/%s", f->name);
}

static
void print_dirname_color(struct filename *f, uint32_t count)
{
  if(f->pred == NULL){
    const uint8_t color_val = DIR_COLOR_FUNCTION(count); // color code is function of depth max
    printf("\033[38;5;%hhum%s", color_val, f->name);
    return;
  }
  if(count == 1) {
    for(struct filename *g=f ; (g=g->pred); count++);    // increase count until f->pred is NULL
    const uint8_t color_val = DIR_COLOR_FUNCTION(count); // color code is function of depth max
    printf("\033[38;5;%hhum.../%s", color_val, f->name);
    return;
  }
  print_dirname_color(f->pred, count-1);
  printf("/%s", f->name);
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
      const size_t fixed_length = 26;
      ctime_r((time_t*)&e->date.tv_sec, buffer); // ctime put a newline at end
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

void print_list_entry(struct list_entries *restrict l, struct options *restrict options)
{
  const bool reverse_order = options->reverse_order;
  const bool activate_color = options->color;
  const bool hide_date = options->hide_date;
  const bool fzf_activate = options->fzf_activate;
  const enum sort_type sort_type = options->sort_type;
  const enum search_type search_type = options->search_type;
  const uint32_t fzf_shorten_name = (fzf_activate ? options->fzf_shorten_name : 0);

  size_t n = l->n;

  for(size_t i=0; i<n; i++){
    struct entry *e = (!reverse_order) ? &l->entries[i] : &l->entries[n - 1 - i];
    
    if(!hide_date) {
      print_entry_info(e, sort_type);
      if(fzf_activate) printf("\x1f ");
    }

    if(search_type == SEARCH_DIRECTORIES && activate_color)
      print_dirname_color(e->name, fzf_shorten_name);
    else {
      if(activate_color) printf("\033[%sm", e->color);
      print_filename(e->name, fzf_shorten_name);
    }
    if(activate_color) printf("\033[0m");

    if(fzf_activate && fzf_shorten_name != 0) {
      printf("\x1f ");
      print_filename(e->name, 0); // print full filename
      // TODO: print_dirname_color & print_filename should (maybe) fill a buffer, 
      // to prevent a second exploration of the linked list here,
      // and to do post process like replacing home dir by '~'
    }

    printf("\n");
  }
}

void free_list_entries(struct list_entries *l)
{
  for(size_t i=0; i<l->buffer.n; i++)
    free(l->buffer.b[i]);
  free(l->buffer.b);
  free(l->entries);
}