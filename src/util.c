#include "util.h"
#include "fastRandom.h"
#include <stdio.h>
#include <stdlib.h>

// #define FAST_RANDOM

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

void RandomSeed(int i) {}

int Rand(int s, int e) { return NextLowerUpper(s, e); }

int RndOr(int s, int e) { return NextBool() ? s : e; }

float Rnd() { return (float)rand() / (float)(RAND_MAX / 1); }

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
  l->createNode = (void*)NodeCreate;
  l->destroyNode = (void*)NodeDestroy;
}

node_t *ListAppend(list_t *l, node_t *n) {
  if (n == NULL && l->createNode) {
    n = l->createNode(NULL, false);
  }
  l->length++;
  if (l->first == NULL) {
    l->first = (void*)n;
    l->last = (void*)n;
    return n;
  }
  n->prev = (void*)l->last;
  l->last->next = (void*)n;
  l->last = (void*)n;
  return n;
}

node_t *ListInsertAfter(list_t *l, node_t *n, node_t *ntarget) {
  if (ntarget == l->last) {
    l->length++;
    ntarget->next = (void*)n;
    n->prev = (void*)ntarget;
    n->next = NULL;
    l->last = (void*)n;
    return n;
  }

  ((node_t *)(ntarget->next))->prev = (void*)n;
  n->next = ntarget->next;
  ntarget->next = (void*)n;
  n->prev = (void*)ntarget;
  return n;
}

node_t *ListInsertBefore(list_t *l, node_t *n, node_t *ntarget) {
  l->length++;
  if (ntarget == l->first) {
    l->first = (void*)n;
    n->next = (void*)ntarget;
    ntarget->prev = (void*)n;
    return n;
  }

  n->next = (void*)ntarget;
  n->prev = ntarget->prev;
  ((node_t *)(ntarget->prev))->next = (void*)n;
  ntarget->prev = (void*)n;
  return n;
}

void ListRemove(list_t *l, node_t *n) {
  if (n == l->last) {
    if (n == l->first) {
      l->first = NULL;
      l->last = NULL;
      l->length = 0;
      if (l->destroyNode) {
        l->destroyNode((void*)n);
      }
      return;
    }
    l->last = (void*)n->prev;
    l->last->next = NULL;
    l->length--;
    if (l->destroyNode) {
      l->destroyNode((void*)n);
    }
    return;
  }
  if (n == l->first) {
    l->first = (void*)n->next;
    l->first->prev = NULL;
    l->length--;
    if (l->destroyNode) {
      l->destroyNode((void*)n);
    }
    return;
  }

  ((node_t *)n->prev)->next = (void*)n->next;
  ((node_t *)n->next)->prev = (void*)n->prev;
  if (l->destroyNode) {
    l->destroyNode((void*)n);
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
    n = (void*)n->next;
  }
  return n;
}