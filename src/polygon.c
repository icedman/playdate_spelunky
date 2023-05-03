#include "polygon.h"
#include <math.h>

polygon_t polygon_square;
polygon_t polygon_circle;

void PolygonInitSquare() { PolygonInit(&polygon_square, 4, 1); }

void PolygonInitCircle() { PolygonInit(&polygon_circle, 8, 1); }

void PolygonInit(polygon_t *polygon, int sides, int radius) {
  polygon->sides = sides <= POLYGON_MAX_SIDES ? sides : POLYGON_MAX_SIDES;
  for (int i = 0; i < polygon->sides; i++) {
    float angle = ((360 / polygon->sides) * i) * 3.14 / 180;
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    polygon->points[i].x = x;
    polygon->points[i].y = y;
    polygon->points[i].z = 0;
  }
}

polygon_t PolygonTransformed(polygon_t *polygon, matrix_t *m) {
  polygon_t p;
  p.sides = polygon->sides;
  for (int i = 0; i < polygon->sides; i++) {
    p.points[i] = VectorTransformed(&polygon->points[i], m);
  }
  return p;
}