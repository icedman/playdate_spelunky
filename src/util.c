#include "util.h"
#include "fastRandom.h"
#include <stdio.h>
#include <stdlib.h>

#define FAST_RANDOM

static int _allocated = 0;
static int _freed = 0;
static void *tx_malloc_default(size_t size) {
  void *result = malloc(size);
  _allocated++;
  if (size > 0 && !result) {
    fprintf(stderr, "textmate failed to allocate %zu bytes", size);
    exit(1);
  }
  return result;
}

static void tx_free_default(void *data) {
  _freed++;
  free(data);
}

void tx_stats() { printf("allocated:%d freed:%d\n", _allocated, _freed); }

void *(*tx_malloc)(size_t) = tx_malloc_default;
void (*tx_free)(void *) = tx_free_default;

void tx_set_allocator(void *(*custom_malloc)(size_t),
                      void (*custom_free)(void *)) {
  tx_malloc = custom_malloc;
  tx_free = custom_free;
}

#ifdef FAST_RANDOM

void RandomSeed(int i) { FastRandomInit(i); }

float Rnd() { return NextFloat(); }

int Rand(int s, int n) {
  return (int)(s + (n > 0 ? (NextInt() % n) : 0));
  // return NextLowerUpper(s, e);
}

int RndOr(int s, int e) { return NextBool() ? s : e; }

#else

void RandomSeed(int i) { srand(i); }

float Rnd() { return (float)rand() / (float)(RAND_MAX / 1); }

int Rand(int s, int e) {
  int l = e - s;
  int i = floor(l * (float)rand() / RAND_MAX);
  return s + i;
}

int RndOr(int s, int e) {
  if (rand() % 2 == 0) {
    return s;
  }
  return e;
}

#endif

void NodeInit(node_t *n, void *data, bool managed) {
  n->data = data;
  n->next = NULL;
  n->prev = NULL;
  n->managed = managed;
}

node_t *NodeCreate(void *data, bool managed) {
  node_t *n = tx_malloc(sizeof(node_t));
  NodeInit(n, data, managed);
  return n;
}

void NodeDestroy(node_t *n) {
  if (n->managed && n->data != NULL) {
    tx_free(n->data);
  }
  tx_free(n);
}

void ListInit(list_t *l) {
  l->first = NULL;
  l->last = NULL;
  l->length = 0;
  l->createNode = NodeCreate;
  l->destroyNode = NodeDestroy;
}

node_t *ListAppend(list_t *l, node_t *n) {
  if (n == NULL && l->createNode) {
    n = l->createNode(NULL, false);
  }
  l->length++;
  if (l->first == NULL) {
    l->first = n;
    l->last = n;
    return n;
  }
  n->prev = l->last;
  l->last->next = n;
  l->last = n;
  return n;
}

node_t *ListInsertAfter(list_t *l, node_t *n, node_t *ntarget) {
  if (ntarget == l->last) {
    l->length++;
    ntarget->next = n;
    n->prev = ntarget;
    n->next = NULL;
    l->last = n;
    return n;
  }

  ((node_t *)(ntarget->next))->prev = n;
  n->next = ntarget->next;
  ntarget->next = n;
  n->prev = ntarget;
  return n;
}

node_t *ListInsertBefore(list_t *l, node_t *n, node_t *ntarget) {
  l->length++;
  if (ntarget == l->first) {
    l->first = n;
    n->next = ntarget;
    ntarget->prev = n;
    return n;
  }

  n->next = ntarget;
  n->prev = ntarget->prev;
  ((node_t *)(ntarget->prev))->next = n;
  ntarget->prev = n;
  return n;
}

void ListRemove(list_t *l, node_t *n) {
  if (n == l->last) {
    if (n == l->first) {
      l->first = NULL;
      l->last = NULL;
      l->length = 0;
      if (l->destroyNode) {
        l->destroyNode(n);
      }
      return;
    }
    l->last = n->prev;
    l->last->next = NULL;
    l->length--;
    if (l->destroyNode) {
      l->destroyNode(n);
    }
    return;
  }
  if (n == l->first) {
    l->first = n->next;
    l->first->prev = NULL;
    l->length--;
    if (l->destroyNode) {
      l->destroyNode(n);
    }
    return;
  }

  ((node_t *)n->prev)->next = n->next;
  ((node_t *)n->next)->prev = n->prev;
  if (l->destroyNode) {
    l->destroyNode(n);
  }
  l->length--;
}

void ListDestroy(list_t *l) {
  while (l->first) {
    ListRemove(l, l->first);
  }
}

node_t *ListNodeAt(list_t *l, int index) {
  int idx = 0;
  node_t *n = l->first;
  while (n) {
    if (idx++ == index) {
      break;
    }
    n = n->next;
  }
  return n;
}