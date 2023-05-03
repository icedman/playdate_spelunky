
#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdtypes.h"

#define ABS(a) (a * SGN(a))
#define SGN(a) ((a < 0) ? -1 : 1)
#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define CLAMP(n, min, max) (MIN(MAX(n, min), max))

extern void *(*tx_malloc)(size_t);
extern void (*tx_free)(void *);

void tx_set_allocator(void *(*custom_malloc)(size_t),
                      void (*custom_free)(void *));
void tx_stats();

float Rnd();
int Rand(int s, int e);
int RndOr(int s, int e);

typedef struct {
  void *data;
  struct node_t *prev;
  struct node_t *next;
  bool managed;
} node_t;

void NodeInit(node_t *n, void *data, bool managed);
node_t *NodeCreate(void *data, bool managed);
void NodeDestroy(node_t *n);

typedef struct {
  node_t *first;
  node_t *last;
  int length;
  node_t *(*createNode)(void *data, bool managed);
  void (*destroyNode)(struct node_t *);
} list_t, *plist_t;

void ListInit(list_t *l);
node_t *ListAppend(list_t *l, node_t *n);
node_t *ListInsertAfter(list_t *l, node_t *n, node_t *ntarget);
node_t *ListInsertBefore(list_t *l, node_t *n, node_t *ntarget);
node_t *ListNodeAt(list_t *l, int index);
void ListRemove(list_t *l, node_t *n);
void ListDestroy(list_t *l);

#endif // _UTIL_H_