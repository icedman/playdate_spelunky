
#include "vector.h"
#include <math.h>

float angleTo(float x1, float y1, float x2, float y2) {
  float angleRadians = atan2(y2 - y1, x2 - x1);
  float angle = angleRadians * 57.295779513;
  return (int)(angle + (360 * 2)) % 360;
}

void VectorInit(vector_t *v, float x, float y, float z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

static vector_t vector_rotations[360];
static vector_rotations_inited = false;
void VectorFromAngle(vector_t *v, float angle) {
  // float r = angle * 0.0174533;
  // float sn = sin(r);
  // float cs = cos(r);
  // v->x = cs;
  // v->y = sn;
  int a = ((int)angle + 360 * 4) % 360;
  if (!vector_rotations_inited) {
    for (int i = 0; i < 360; i++) {
      float r = (float)i * 0.0174533;
      float sn = sin(r);
      float cs = cos(r);
      vector_rotations[i].x = cs;
      vector_rotations[i].y = sn;
    }
    vector_rotations_inited = true;
  }
  memcpy(v, &vector_rotations[a], sizeof(vector_t));
}

void VectorZero(vector_t *v) {
  v->x = 0;
  v->y = 0;
  v->z = 0;
}

void VectorCopy(vector_t *v, vector_t *src) {
  memcpy((void *)(v), (void *)(src), sizeof(vector_t));
}

void VectorAdd(vector_t *va, vector_t *vb, vector_t *vr) {
  vr->x = va->x + vb->x;
  vr->y = va->y + vb->y;
  vr->z = va->z + vb->z;
}

vector_t VectorAdded(vector_t *va, vector_t *vb) {
  vector_t vr;
  vr.x = va->x + vb->x;
  vr.y = va->y + vb->y;
  vr.z = va->z + vb->z;
  return (vr);
}

void VectorSubtract(vector_t *va, vector_t *vb, vector_t *vr) {
  vr->x = va->x - vb->x;
  vr->y = va->y - vb->y;
  vr->z = va->z - vb->z;
}

vector_t VectorSubtracted(vector_t *va, vector_t *vb) {
  vector_t vr;
  vr.x = va->x - vb->x;
  vr.y = va->y - vb->y;
  vr.z = va->z - vb->z;
  return (vr);
}

void VectorScale(vector_t *v, vector_t *vr, float s) {
  vr->x = (v->x * s);
  vr->y = (v->y * s);
  vr->z = (v->z * s);
}

vector_t VectorScaled(vector_t *v, float s) {
  vector_t vr;
  vr.x = (v->x * s);
  vr.y = (v->y * s);
  vr.z = (v->z * s);
  return (vr);
}

float VectorDot(vector_t *va, vector_t *vb) {
  return (vb->x * va->x) + (vb->y * va->y) + (vb->z * va->z);
}

void VectorCross(vector_t *va, vector_t *vb, vector_t *vr) {
  vr->x = (va->y * vb->z) - (va->z * vb->y);
  vr->y = (va->z * vb->x) - (va->x * vb->z);
  vr->z = (va->x * vb->y) - (va->y * vb->x);
}

vector_t VectorCrossed(vector_t *va, vector_t *vb) {
  vector_t vr;
  vr.x = (va->y * vb->z) - (va->z * vb->y);
  vr.y = (va->z * vb->x) - (va->x * vb->z);
  vr.z = (va->x * vb->y) - (va->y * vb->x);
  return (vr);
}

void VectorNormalize(vector_t *v) {
  float l = VectorLength(v);
  if (l == 0) {
    v->x = 0;
    v->y = 0;
    v->z = 0;
    return;
  }
  v->x = (v->x / l);
  v->y = (v->y / l);
  v->z = (v->z / l);
}

float VectorLength(vector_t *v) {
  float fx = v->x, fy = v->y, fz = v->z;
  return sqrt(fx * fx + fy * fy + fz * fz);
}

void VectorTransform(vector_t *v, matrix_t *m, vector_t *vr) {
  VectorZero(vr);
  for (int col = 0; col < 3; col++) {
    float sum = 0;
    for (int row = 0; row < 3; row++) {
      sum += (v->M[row] * m->M[row][col]);
    }
    // add in last element in column or w*m[3][col]; (w=1)
    sum += m->M[3][col];
    vr->M[col] = sum;
  }
}

vector_t VectorTransformed(vector_t *v, matrix_t *m) {
  vector_t vr;
  VectorZero(&vr);
  for (int col = 0; col < 3; col++) {
    float sum = 0;
    for (int row = 0; row < 3; row++) {
      sum += (v->M[row] * m->M[row][col]);
    }
    // add in last element in column or w*m[3][col]; (w=1)
    sum += m->M[3][col];
    vr.M[col] = sum;
  }
  return (vr);
}

vector_t VectorLerp(vector_t v1, vector_t v2, float p) {
  vector_t res = VectorSubtracted(&v2, &v1);
  res = VectorScaled(&res, p);
  res = VectorAdded(&res, &v1);
  return res;
}

float VectorAngleTo(vector_t *va, vector_t *vb) {
  return angleTo(va->x, va->y, vb->x, vb->y);
}

float VectorAngle(vector_t *v) {
  vector_t vf;
  VectorZero(&vf);
  return VectorAngleTo(&vf, v);
}

float VectorDistanceTo(vector_t *va, vector_t *vb) {
  float dx = va->x - vb->x;
  float dy = va->y - vb->y;
  return sqrt((dx * dx) + (dy * dy));
}

vector_t VectorIntersection(vector_t p1, vector_t p2, vector_t p3,
                            vector_t p4) {
  vector_t p;
  p.x = -1;
  p.y = -1;

  float c2x = p3.x - p4.x; // (x3 - x4)
  float c3x = p1.x - p2.x; // (x1 - x2)
  float c2y = p3.y - p4.y; // (y3 - y4)
  float c3y = p1.y - p2.y; // (y1 - y2)

  // down part of intersection point formula
  float d = c3x * c2y - c3y * c2x;
  if (d == 0) {
    // throw new Error('Number of intersection points is zero or infinity.');
    return p;
  }

  // upper part of intersection point formula
  float u1 = p1.x * p2.y - p1.y * p2.x; // (x1 * y2 - y1 * x2)
  float u4 = p3.x * p4.y - p3.y * p4.x; // (x3 * y4 - y3 * x4)

  // intersection point formula
  float px = (u1 * c2x - c3x * u4) / d;
  float py = (u1 * c2y - c3y * u4) / d;

  p.x = px;
  p.y = py;
  return p;
}

void RectInitXYWH(rect_t *r, float x, float y, float w, float h) {
  r->lt.x = x;
  r->lt.y = y;
  r->lt.z = 0;
  r->rb.x = x + w;
  r->rb.y = y + h;
  r->rb.z = 0;

  r->rt.x = r->rb.x;
  r->rt.y = r->lt.y;
  r->rt.z = 0;
  r->lb.x = r->lt.x;
  r->lb.y = r->rb.y;
  r->lb.z = 0;
}

float RectWidth(rect_t r) { return r.rb.x - r.lt.x; }

float RectHeight(rect_t r) { return r.rb.y - r.lt.y; }

rect_t RectOffset(rect_t r, vector_t offset) {
  rect_t res;
  memcpy(&res, &r, sizeof(rect_t));
  for (int i = 0; i < 4; i++) {
    res.M[i].x += offset.x;
    res.M[i].y += offset.y;
  }
  return res;
}

bool RectCollide(rect_t r1, rect_t r2) {
  float r1x = r1.lt.x;
  float r1y = r1.lt.y;
  float r1w = RectWidth(r1);
  float r1h = RectHeight(r1);
  float r2x = r2.lt.x;
  float r2y = r2.lt.y;
  float r2w = RectWidth(r2);
  float r2h = RectHeight(r2);

  // are the sides of one rectangle touching the other?
  if (r1x + r1w >= r2x && // r1 right edge past r2 left
      r1x <= r2x + r2w && // r1 left edge past r2 right
      r1y + r1h >= r2y && // r1 top edge past r2 bottom
      r1y <= r2y + r2h) { // r1 bottom edge past r2 top
    return true;
  }
  return false;
}

bool RectContains(rect_t r, vector_t v) {
  if (v.x <= r.lt.x)
    return false;
  if (v.y <= r.lt.y)
    return false;
  if (v.x >= r.rb.x)
    return false;
  if (v.y >= r.rb.y)
    return false;
  return true;
}

int RectEdgeContains(rect_t r, vector_t v) {
  if (r.lt.y == v.y && r.lt.x <= v.x && r.rt.x >= v.x)
    return 0;
  if (r.rt.x == v.x && r.rt.y <= v.y && r.rb.y >= v.y)
    return 1;
  if (r.lb.y == v.y && r.lt.x <= v.x && r.rt.x >= v.x)
    return 2;
  if (r.lt.x == v.x && r.lt.y <= v.y && r.lb.y >= v.y)
    return 3;
  return -1;
}