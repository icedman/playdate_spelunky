
#include "matrix.h"
#include <math.h>

static const float identity_matrix[16] = {1, 0, 0, 0, 0, 1, 0, 0,
                                          0, 0, 1, 0, 0, 0, 0, 1};

void MatrixZero(matrix_t *m) { memset((void *)(m), 0, sizeof(matrix_t)); }

void MatrixIdentity(matrix_t *m) {
  memcpy((void *)(m), (void *)(identity_matrix), sizeof(matrix_t));
}

void MatrixCopy(matrix_t *m, matrix_t *src) {
  memcpy((void *)(m), (void *)(src), sizeof(matrix_t));
}

void MatrixInit(matrix_t *m, float c00, float c01, float c02, float c03,
                float c10, float c11, float c12, float c13, float c20,
                float c21, float c22, float c23, float c30, float c31,
                float c32, float c33) {
  m->c00 = c00;
  m->c01 = c01;
  m->c02 = c02;
  m->c03 = c03;
  m->c10 = c10;
  m->c11 = c11;
  m->c12 = c12;
  m->c13 = c13;
  m->c20 = c20;
  m->c21 = c21;
  m->c22 = c22;
  m->c23 = c23;
  m->c30 = c30;
  m->c31 = c31;
  m->c32 = c32;
  m->c33 = c33;
}

void MatrixAdd(matrix_t *ma, matrix_t *mb, matrix_t *mr) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      mr->M[row][col] = ma->M[row][col] + mb->M[row][col];
    }
  }
}

void MatrixMultiply(matrix_t *ma, matrix_t *mb, matrix_t *mr) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float sum = 0;
      for (int index = 0; index < 4; index++) {
        sum += ((ma->M[row][index] * mb->M[index][col]));
      }
      mr->M[row][col] = sum;
    }
  }
}

matrix_t MatrixAdded(matrix_t *ma, matrix_t *mb) {
  matrix_t mr;
  MatrixIdentity(&mr);
  MatrixAdd(ma, mb, &mr);
  return mr;
}

matrix_t MatrixMultiplied(matrix_t *ma, matrix_t *mb) {
  matrix_t mr;
  MatrixIdentity(&mr);
  MatrixMultiply(ma, mb, &mr);
  return mr;
}

#define ROTSEQX (1 << 1)
#define ROTSEQY (1 << 2)
#define ROTSEQZ (1 << 3)
void MatrixRotation(matrix_t *mrot, float ax, float ay, float az) {
  matrix_t mx, my, mz, mtmp;
  float sinTheta = 0;
  float cosTheta = 0;
  int rotSeq = 0;

  if (ax > 0)
    rotSeq = rotSeq | ROTSEQX;

  if (ay > 0)
    rotSeq = rotSeq | ROTSEQY;

  if (az > 0)
    rotSeq = rotSeq | ROTSEQZ;

  if (rotSeq == 0) {
    MatrixIdentity(mrot);
    return;
  }

  if (rotSeq & ROTSEQX) {
    cosTheta = cos(ax);
    sinTheta = sin(ax);
    MatrixInit(&mx, 1, 0, 0, 0, 0, cosTheta, sinTheta, 0, 0, -sinTheta,
               cosTheta, 0, 0, 0, 0, 1);

    if (rotSeq == ROTSEQX) {
      MatrixCopy(mrot, &mx);
      return;
    }
  }

  if (rotSeq & ROTSEQY) {
    cosTheta = cos(ay);
    sinTheta = sin(ay);
    MatrixInit(&my, cosTheta, 0, -sinTheta, 0, 0, 1, 0, 0, sinTheta, 0,
               cosTheta, 0, 0, 0, 0, 1);

    if (rotSeq == ROTSEQY) {
      MatrixCopy(mrot, &my);
      return;
    }
  }

  if (rotSeq & ROTSEQZ) {
    cosTheta = cos(az);
    sinTheta = sin(az);
    MatrixInit(&mz, cosTheta, sinTheta, 0, 0, -sinTheta, cosTheta, 0, 0, 0, 0,
               1, 0, 0, 0, 0, 1);

    if (rotSeq == ROTSEQZ) {
      MatrixCopy(mrot, &mz);
      return;
    }
  }

  if (rotSeq & ROTSEQX) {
    if (rotSeq & ROTSEQY) {
      if (rotSeq & ROTSEQZ) {
        MatrixMultiply(&mx, &my, &mtmp);
        MatrixMultiply(&mtmp, &mz, &mrot);
        return;
      }
      MatrixMultiply(&mx, &my, &mrot);
      return;
    }
  }

  if (rotSeq & ROTSEQZ) {
    if (rotSeq & ROTSEQX) {
      MatrixMultiply(&mx, &mz, &mrot);
      return;
    }
    MatrixMultiply(&my, &mz, &mrot);
    return;
  }
}

void MatrixTranslation(matrix_t *mtrans, float tx, float ty, float tz) {
  MatrixInit(mtrans, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
}

void MatrixScale(matrix_t *mscale, float sx, float sy, float sz) {
  MatrixInit(mscale, sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
}

void MatrixStackInit(matrixStack_t *stack) {
  stack->matrix = &stack->matrices[0];
  MatrixIdentity(stack->matrix);
}

bool MatrixStackPush(matrixStack_t *stack) {
  if (stack->matrix == &stack->matrices[MATRIX_STACK_SIZE - 1])
    return false;

  MatrixCopy(stack->matrix + 1, stack->matrix);
  stack->matrix++;

  return true;
}

bool MatrixStackPop(matrixStack_t *stack) {
  if (stack->matrix == &stack->matrices[0])
    return false;

  stack->matrix--;

  return true;
}

int MatrixStackSize(matrixStack_t *stack) {
  int count = 0;
  matrix_t *m = &stack->matrices[0];
  while (m != &stack->matrices[MATRIX_STACK_SIZE - 1]) {
    if (m == stack->matrix) {
      break;
    }
    m++;
    count++;
  }
  return count;
}

void MatrixStackRotate2D(matrixStack_t *stack, float angle) {
  matrix_t m, mr;
  MatrixRotation(&mr, 0, 0, angle * 0.0174533);
  m = MatrixMultiplied(stack->matrix, &mr);
  *stack->matrix = m;
}

void MatrixStackTranslate2D(matrixStack_t *stack, float x, float y) {
  matrix_t m, mt;
  MatrixTranslation(&mt, x, y, 0);
  m = MatrixMultiplied(stack->matrix, &mt);
  *stack->matrix = m;
}

void MatrixStackScale2D(matrixStack_t *stack, float sz) {
  matrix_t m, ms;
  MatrixScale(&ms, sz, sz, 1);
  m = MatrixMultiplied(stack->matrix, &ms);
  *stack->matrix = m;
}

static matrix_t matrix_rotations[360];
static matrix_rotations_inited = false;
void MatrixInitRotation2D(matrix_t *m, float angle) {
  // MatrixRotation(m, 0, 0, (float)angle * 0.0174533);
  int a = ((int)angle + 360 * 4) % 360;
  if (!matrix_rotations_inited) {
    for (int i = 0; i < 360; i++) {
      MatrixRotation(&matrix_rotations[i], 0, 0, (float)i * 0.0174533);
    }
    matrix_rotations_inited = true;
  }
  memcpy(m, &matrix_rotations[a], sizeof(matrix_t));
}

void MatrixInit2D(matrix_t *m, float angle, float scale, float x, float y) {
  MatrixIdentity(m);
  matrix_t mr;
  MatrixInitRotation2D(&mr, angle);
  MatrixRotation(&mr, 0, 0, angle * 0.0174533);
  *m = MatrixMultiplied(m, &mr);
  matrix_t ms;
  MatrixScale(&ms, scale, scale, 1);
  *m = MatrixMultiplied(m, &ms);
  matrix_t mt;
  MatrixTranslation(&mt, x, y, 0);
  *m = MatrixMultiplied(m, &mt);
}
