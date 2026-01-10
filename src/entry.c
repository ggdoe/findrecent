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
char* load_filepath(char *buffer, struct filename *f)
{
  const size_t len = strlen(f->name);
  
  if(f->pred){
    buffer = load_filepath(buffer, f->pred);
    *(buffer++) = '/'; // append a '/' and increase the buffer pointer
  }

  memcpy(buffer, f->name, len * sizeof(char));
  return buffer + len;
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
  const size_t n = l->n;
  char buffer[PATH_MAX];

  for(size_t i=0; i<n; i++){
    char* buf = buffer + 1; // +1 because if fzf_shorten_name=1 and you search at the root '/' and there is a single character directory at the root, the files inside this directory will underflow the buffer when adding the ellipsis character
    struct entry *e = (!reverse_order) ? &l->entries[i] : &l->entries[n - 1 - i];
    
    load_filepath(buf, e->name)[0] = '\0'; // load filename and null terminate the buffer

    // TODO: replace $HOME by ~

    size_t depth = 0; // count number of '/' in buffer
    for(char* c=buf; *c != '\0'; c++) if (*c == '/') depth++;

    if(!hide_date) {
      print_entry_info(e, sort_type);
      if(fzf_activate) printf("\x1f "); // print fzf separator
    }

    // print the 'hidden' full filename in fzf in case fzf_shorten_name is set
    if(fzf_activate && fzf_shorten_name != 0) {
      printf("%s\x1f ", buf);
      
      int64_t to_skip = depth - fzf_shorten_name;
      if (to_skip > 0) {
        // search position of the n-th '/' in buffer
        for(;to_skip >= 0; to_skip--) {
          char* slash = strchr(buf, '/');
          if(slash != NULL)
            buf = slash+1;
        }
        
        // print ellipsis if filename was shorten
        const char ellispis[] = "\xE2\x80\xA6/"; // ellipsis character
        buf -= sizeof(ellispis) - 1;
        memcpy(buf, ellispis, sizeof(ellispis) - 1);
      }
    }

    if(activate_color && search_type == SEARCH_DIRECTORIES) {
      const uint8_t color_val = DIR_COLOR_FUNCTION(depth);
      printf("\033[38;5;%hhum%s\033[0m\n", color_val, buf);
    }
    else if (activate_color /* && search_type == SEARCH_FILES */) {
      printf("\033[%sm%s\033[0m\n", e->color, buf);
    }
    else /* no color */ {
      printf("%s\n", buf);
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