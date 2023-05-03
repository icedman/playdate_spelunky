#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "matrix.h"
#include "vector.h"

#define POLYGON_MAX_SIDES 16

typedef struct {
  vector_t points[POLYGON_MAX_SIDES];
  int sides;
} polygon_t;

extern polygon_t polygon_square;
extern polygon_t polygon_circle;

void PolygonInit(polygon_t *polygon, int sides, int radius);
polygon_t PolygonTransformed(polygon_t *polygon, matrix_t *matrix);
void PolygonInitSquare();
void PolygonInitCircle();

#endif // _POLYGON_H_