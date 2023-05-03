
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "stdtypes.h"

#define MATRIX_STACK_SIZE 32

typedef struct {
  union {
    float M[4][4];
    struct {
      float c00, c01, c02, c03;
      float c10, c11, c12, c13;
      float c20, c21, c22, c23;
      float c30, c31, c32, c33;
    };
  };
} matrix_t;

typedef matrix_t *pmatrix_t;

typedef struct {
  matrix_t matrices[MATRIX_STACK_SIZE];
  matrix_t *matrix;
} matrixStack_t;

typedef matrixStack_t *pmatrixStack_t;

void MatrixZero(matrix_t *m);
void MatrixIdentity(matrix_t *m);
void MatrixCopy(matrix_t *m, matrix_t *src);
void MatrixInit(matrix_t *m, float c00, float c01, float c02, float c03,
                float c10, float c11, float c12, float c13, float c20,
                float c21, float c22, float c23, float c30, float c31,
                float c32, float c33);
void MatrixAdd(matrix_t *ma, matrix_t *mb, matrix_t *mr);
void MatrixMultiply(matrix_t *ma, matrix_t *mb, matrix_t *mr);
void MatrixRotation(matrix_t *mrot, float ax, float ay, float az);
void MatrixTranslation(matrix_t *mtrans, float tx, float ty, float tz);
void MatrixScale(matrix_t *mscale, float sx, float sy, float sz);

matrix_t MatrixAdded(matrix_t *ma, matrix_t *mb);
matrix_t MatrixMultiplied(matrix_t *ma, matrix_t *mb);

void MatrixStackInit(matrixStack_t *stack);
bool MatrixStackPush(matrixStack_t *stack);
bool MatrixStackPop(matrixStack_t *stack);

// 2D
void MatrixInit2D(matrix_t *m, float angle, float scale, float x, float y);
void MatrixInitRotation2D(matrix_t *m, float angle);
void MatrixStackRotate2D(matrixStack_t *stack, float angle);
void MatrixStackTranslate2D(matrixStack_t *stack, float x, float y);
void MatrixStackScale2D(matrixStack_t *stack, float sz);
int MatrixStackSize(matrixStack_t *stack);

void MatrixTrace(matrix_t *m);

#endif // _MATRIX_H_