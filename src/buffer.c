#include "defs.h"

static inline 
void* push_buffer(struct buffer *buffer, size_t len)
{
  struct inner_buffer *cur = buffer->b[buffer->n-1];

  if(cur->n+len >= INNER_BUFSIZE) {
    size_t n = buffer->n++;
    buffer->b = (struct inner_buffer**) realloc(buffer->b, (n+1)*sizeof(struct inner_buffer*));
    checkptr(buffer->b);
    buffer->b[n] = (struct inner_buffer*) malloc(sizeof(struct inner_buffer));
    checkptr(buffer->b[n]);

    cur = buffer->b[n];
    cur->n = 0;
  }

  void *mem = cur->mem + cur->n;
  cur->n += len;

  return mem;
}

static inline 
char* push_buffer_str(struct buffer *restrict buffer, const char *restrict str)
{
  const size_t len = strlen(str)+1;
  char *mem = push_buffer(buffer, (len+7) & ~7);

  return memcpy(mem, str, len*sizeof(char));
}

struct filename *push_buffer_filename(struct list_entries *restrict l, struct filename *restrict pred, const char *restrict name)
{
  size_t len = sizeof(struct filename);
  struct filename *f = push_buffer(&l->buffer, len);
  
  f->name = push_buffer_str(&l->buffer, name);
  f->pred = pred;
  return f;
}
