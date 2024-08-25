#include "defs.h"

static int cmp_date(const void *p1, const void *p2);
static void merge_sorted_list(struct list_entries *l, struct list_entries *ll, int nb_threads);


struct list_entries merge_sort_list_task(struct list_task *lt, int nb_threads)
{
  struct list_entries *ll = lt->l;
  struct list_entries l;
  size_t nb_entries = 0;
  size_t nb_buffer = 0;
  for(int i=0; i<nb_threads; i++) {
    nb_entries += ll[i].n;
    nb_buffer  += ll[i].buffer.n;
  }

  l.entries = (struct entry*) malloc(nb_entries * sizeof(struct entry));
  checkptr(l.entries);
  l.n = nb_entries;
  l.cap = nb_entries;

  l.buffer.b = (struct inner_buffer**) malloc(nb_buffer * sizeof(struct inner_buffer*));
  checkptr(l.buffer.b);
  l.buffer.n = nb_buffer;

#if 0 // merge then qsort (slower?)
  int cur_b=0, cur_e=0;
  for(int i=0; i<nb_threads; i++) {
    const size_t nb = ll[i].buffer.n;
    const size_t ne = ll[i].n;
    memcpy(l.buffer.b + cur_b, ll[i].buffer.b, nb * sizeof(struct inner_buffer*));
    memcpy(l.entries  + cur_e, ll[i].entries,  ne * sizeof(struct entry));
    cur_b += nb;
    cur_e += ne;

    free(ll[i].buffer.b);
    free(ll[i].entries);
  }
  qsort(l.entries, l.n, sizeof(struct entry), cmp_date);

#else // qsort then merge
  int cur_b=0;
  for(int i=0; i<nb_threads; i++) {
    const size_t nb = ll[i].buffer.n;
    memcpy(l.buffer.b + cur_b, ll[i].buffer.b, nb * sizeof(struct inner_buffer*));
    cur_b += nb;

    free(ll[i].buffer.b);
  }

  #pragma omp parallel for
  for(int i=0; i<nb_threads; i++)
    qsort(ll[i].entries, ll[i].n, sizeof(struct entry), cmp_date);
  
  merge_sorted_list(&l, ll, nb_threads);

  for(int i=0; i<nb_threads; i++)
    free(ll[i].entries);
#endif

  return l;
}

int cmp_date(const void *p1, const void *p2)
{
  const struct entry *e1 = p1;
  const struct entry *e2 = p2;

  const long
   s = e1->date.tv_sec - e2->date.tv_sec;
  if (s != 0) return s;
  return e1->date.tv_nsec - e2->date.tv_nsec;
}

void merge_sorted_list(struct list_entries *l, struct list_entries *ll, int nb_threads)
{
  for(int i=0; i<nb_threads; i++){
    ll[i].cap = ll[i].n;
    ll[i].n = 0;
  }

  #define get_entry(i) &ll[i].entries[ll[i].n]
  struct entry minimum_value = {.date={0, 0}, .name=NULL};
  
  for(size_t cur=0; cur<l->n; cur++) {
    struct entry *maxval = &minimum_value;
    size_t argmin = 0;
    for(int i=0; i<nb_threads; i++) {
      if(ll[i].n >= ll[i].cap) continue;
      struct entry *curval = get_entry(i);
      if(cmp_date(curval, maxval)>0) {
        maxval = curval;
        argmin = i;
      }
    }
    l->entries[cur] = *maxval;
    ll[argmin].n++;
  }
  #undef get_entry
}
