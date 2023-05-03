#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "matrix.h"
#include "polygon.h"
#include "vector.h"

#define CONTEXT_STATES_SIZE MATRIX_STACK_SIZE

typedef void (*drawLineFunction)(void *context, vector_t v1, vector_t v2);
typedef void *(*loadImageFunction)(void *context, char *path);
typedef void (*freeImageFunction)(void *context, void *image);
typedef void (*drawImageFunction)(void *context, void *image, vector_t pos,
                                  bool flipped);

extern loadImageFunction loadImage;
extern freeImageFunction freeImage;
extern drawImageFunction drawImage;

void setImageFunctions(loadImageFunction li, freeImageFunction fi,
                       drawImageFunction di);

typedef struct {
  int r, g, b;
  int stroke;
  bool dark;
} contextState_t;

typedef struct {
  int width;
  int height;
  contextState_t states[CONTEXT_STATES_SIZE];
  contextState_t *state;
  matrixStack_t matrixStack;
  void *renderer;
  drawLineFunction drawLine;
} context_t;

void ContextInit(context_t *context, int width, int height);
bool ContextSave(context_t *context);
bool ContextRestore(context_t *context);
void ContextRotate(context_t *context, float angle);
void ContextTranslate(context_t *context, float x, float y);
void ContextScale(context_t *context, float sz);
void ContextSetColor(context_t *context, int r, int g, int b);
void ContextDrawLine(context_t *context, vector_t from, vector_t to);
void ContextDrawPolygon(context_t *context, polygon_t *polygon, vector_t pos,
                        float angle, float radius, bool close);
float ContextDrawChar(context_t *context, char c, vector_t pos, float size,
                      bool extentsOnly);
float ContextDrawText(context_t *context, char *text, vector_t pos, float size,
                      int align);
int ContextStackSize(context_t *context);

#endif // _CONTEXT_H_