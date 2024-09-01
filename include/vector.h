#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "matrix.h"
#include "stdtypes.h"

typedef struct {
  union {
    float M[3];
    struct {
      float x, y, z;
    };
  };
} vector_t, *pvector_t;

void VectorZero(vector_t *v);
void VectorCopy(vector_t *v, vector_t *src);

void VectorInit(vector_t *v, float x, float y, float z);
void VectorFromAngle(vector_t *v, float angle);
void VectorAdd(vector_t *va, vector_t *vb, vector_t *vr);
void VectorSubtract(vector_t *va, vector_t *vb, vector_t *vr);
void VectorScale(vector_t *v, vector_t *vr, float s);
void VectorCross(vector_t *va, vector_t *vb, vector_t *vr);
vector_t VectorAdded(vector_t *va, vector_t *vb);
vector_t VectorSubtracted(vector_t *va, vector_t *vb);
vector_t VectorScaled(vector_t *v, float s);
vector_t VectorCrossed(vector_t *va, vector_t *vb);
float VectorDistanceTo(vector_t *va, vector_t *vb);
float VectorAngleTo(vector_t *va, vector_t *vb);
float VectorAngle(vector_t *v);

void VectorNormalize(vector_t *v);
float VectorLength(vector_t *v);
float VectorDot(vector_t *va, vector_t *vb);

void VectorTransform(vector_t *v, matrix_t *m, vector_t *vr);
vector_t VectorTransformed(vector_t *v, matrix_t *m);
vector_t VectorIntersection(vector_t p1, vector_t p2, vector_t p3, vector_t p4);

vector_t VectorLerp(vector_t v1, vector_t v2, float p);

typedef struct {
  union {
    vector_t M[4];
    struct {
      vector_t lt;
      vector_t rt;
      vector_t rb;
      vector_t lb;
    };
  };
} rect_t;

void RectInitXYWH(rect_t *r, float x, float y, float w, float h);
rect_t RectOffset(rect_t r, vector_t offset);
vector_t RectCenter(rect_t r);
float RectWidth(rect_t r);
float RectHeight(rect_t r);
bool RectContains(rect_t r, vector_t v);
int RectEdgeContains(rect_t r, vector_t v);
bool RectCollide(rect_t r1, rect_t r2);

#endif // _VECTOR_H_