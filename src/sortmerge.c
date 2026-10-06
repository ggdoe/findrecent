#include "defs.h"

// `sort then merge` seems to be slightly faster.
// #define MERGE_THEN_SORT // `merge then sort` or `sort then merge`

static int cmp_date(const void *p1, const void *p2);
#ifndef MERGE_THEN_SORT
static void merge_sorted_list(struct list_entries *l, struct list_entries *ll, int nb_threads);
#endif

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


#ifdef MERGE_THEN_SORT
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

  // technically this is not valid when comparing the filesize as date, but it will work since entry is initialize to zero.
  if (e1->date.tv_sec != e2->date.tv_sec)
    return (e1->date.tv_sec > e2->date.tv_sec) - (e1->date.tv_sec < e2->date.tv_sec);
  else
    return (e1->date.tv_nsec > e2->date.tv_nsec) - (e1->date.tv_nsec < e2->date.tv_nsec);
}

#ifndef MERGE_THEN_SORT
void merge_sorted_list(struct list_entries *l, struct list_entries *ll, int nb_threads)
{
  const struct entry *cur[nb_threads];
  const struct entry *end[nb_threads];
  int active_threads = 0;

  for (int i = 0; i < nb_threads; i++) {
    if (ll[i].n > 0) {
      cur[active_threads] = ll[i].entries;
      end[active_threads] = ll[i].entries + ll[i].n;
      active_threads++;
    }
    ll[i].cap = ll[i].n;
    ll[i].n = 0;
  }

  for (size_t i = 0; i < l->n; i++) {
    int argmin = 0;
    const struct entry *minval = cur[0];

    for (int i = 1; i < active_threads; i++) {
      if (cmp_date(cur[i], minval) < 0) {
        minval = cur[i];
        argmin = i;
      }
    }

    l->entries[i] = *minval;
    cur[argmin]++;

    if (cur[argmin] == end[argmin]) {
      active_threads--;
      cur[argmin] = cur[active_threads];
      end[argmin] = end[active_threads];
    }
  }
}
#endif
