#include "context.h"
#include "font.h"
#include "polygon.h"

loadImageFunction loadImage = NULL;
freeImageFunction freeImage = NULL;
drawImageFunction drawImage = NULL;

void setImageFunctions(loadImageFunction li, freeImageFunction fi,
                       drawImageFunction di) {
  loadImage = li;
  freeImage = fi;
  drawImage = di;
}

// Clips a line segment to an axis-aligned rectangle
// Returns true if clipping is successful
// Returns false if line segment lies outside the rectangle
// https://stackoverflow.com/questions/11194876/clip-line-to-screen-coordinates
bool clip(vector_t *v1, vector_t *v2, int xmin, int ymin, int xmax, int ymax) {
  int a[] = {v1->x, v1->y};
  int b[] = {v2->x, v2->y};

  int mins[2] = {xmin, ymin};
  int maxs[2] = {xmax, ymax};
  int normals[2] = {1, -1};
  for (int axis = 0; axis < 2; axis++) {
    for (int plane = 0; plane < 2; plane++) {
      // Check both points
      for (int pt = 1; pt <= 2; pt++) {
        int *pt1 = pt == 1 ? a : b;
        int *pt2 = pt == 1 ? b : a;

        // If both points are outside the same plane, the line is
        // outside the rectangle
        if ((a[0] < xmin && b[0] < xmin) || (a[0] > xmax && b[0] > xmax) ||
            (a[1] < ymin && b[1] < ymin) || (a[1] > ymax && b[1] > ymax)) {
          return 0;
        }

        const int n = normals[plane];
        if ((n == 1 && pt1[axis] < mins[axis]) ||  // check left/top plane
            (n == -1 && pt1[axis] > maxs[axis])) { // check right/bottom plane

          // Calculate interpolation factor t using ratio of signed distance
          // of each point from the plane
          const float p = (n == 1) ? mins[axis] : maxs[axis];
          const float q1 = pt1[axis];
          const float q2 = pt2[axis];
          const float d1 = n * (q1 - p);
          const float d2 = n * (q2 - p);
          const float t = d1 / (d1 - d2);

          // t should always be between 0 and 1
          if (t < 0 || t > 1) {
            return 1;
          }

          // Interpolate to find the new point
          pt1[0] = (int)(pt1[0] + (pt2[0] - pt1[0]) * t);
          pt1[1] = (int)(pt1[1] + (pt2[1] - pt1[1]) * t);
        }
      }
    }
  }

  v1->x = a[0];
  v1->y = a[1];
  v2->x = b[0];
  v2->y = b[1];
  return true;
}

bool cull(context_t *context, vector_t v1, vector_t v2) {
  int w = context->width;
  int h = context->height;
  if ((v1.x < 0 && v2.x < 0) || (v1.y < 0 && v2.y < 0))
    return 1;
  if ((v1.x > w && v2.x > w) || (v1.y > h && v2.y > h))
    return 1;
  return 0;
}

void ContextInit(context_t *context, int width, int height) {
  memset(context, 0, sizeof(context_t));
  context->state = &context->states[0];
  context->state->stroke = 1;
  context->state->r = 255;
  context->width = width;
  context->height = height;
  MatrixStackInit(&context->matrixStack);

  PolygonInitSquare();
  PolygonInitCircle();
}

bool ContextSave(context_t *context) {
  if (context->state == &context->states[CONTEXT_STATES_SIZE - 1])
    return false;

  memcpy(context->state + 1, context->state, sizeof(contextState_t));
  context->state++;
  MatrixStackPush(&context->matrixStack);
  return true;
}

bool ContextRestore(context_t *context) {
  if (context->state == &context->states[0])
    return false;

  context->state--;
  MatrixStackPop(&context->matrixStack);
  return true;
}

int ContextStackSize(context_t *context) {
  int count = 0;
  contextState_t *m = &context->states[0];
  while (m != &context->states[CONTEXT_STATES_SIZE - 1]) {
    if (m == context->state) {
      break;
    }
    m++;
    count++;
  }
  return count;
}

void ContextRotate(context_t *context, float angle) {
  MatrixStackRotate2D(&context->matrixStack, angle);
}

void ContextTranslate(context_t *context, float x, float y) {
  MatrixStackTranslate2D(&context->matrixStack, x, y);
}

void ContextScale(context_t *context, float sz) {
  MatrixStackScale2D(&context->matrixStack, sz);
}

void ContextSetColor(context_t *context, int r, int g, int b) {
  context->state->r = r;
  context->state->g = g;
  context->state->b = b;
}

void ContextDrawLine(context_t *context, vector_t from, vector_t to) {
  if (context->drawLine == 0 || context->renderer == 0) {
    return;
  }
  vector_t v1 = VectorTransformed(&from, context->matrixStack.matrix);
  vector_t v2 = VectorTransformed(&to, context->matrixStack.matrix);

  // if (cull(context, v1, v2)) {
  //   return;
  // }

  int pad = 2;
  if (!clip(&v1, &v2, pad, pad, context->width - (pad << 1),
            context->height - (pad << 1))) {
    return;
  }

  context->drawLine(context, v1, v2);
}

void ContextDrawPolygon(context_t *context, polygon_t *polygon, vector_t pos,
                        float angle, float radius, bool close) {
  if (context->drawLine == 0 || context->renderer == 0) {
    return;
  }

  int l = polygon->sides;
  if (l < 3) {
    if (l == 2) {
      // this takes care of computing world coordinates
      ContextDrawLine(context, polygon->points[0], polygon->points[1]);
    }
    return;
  }

  if (!close) {
    l--;
  }

  matrix_t local;
  MatrixInit2D(&local, angle, radius, pos.x, pos.y);
  polygon_t pt = PolygonTransformed(polygon, &local);
  pt = PolygonTransformed(&pt, context->matrixStack.matrix);

  for (int i = 0; i < l; i++) {
    vector_t p1 = pt.points[i];
    vector_t p2 = pt.points[(i + 1) % pt.sides];
    context->drawLine(context, p1, p2);
  }
}

float ContextDrawChar(context_t *context, char c, vector_t pos, float size,
                      bool extentsOnly) {
  int *pts = FontCharPoints(c);
  int next_moveto = 1;
  vector_t startPosition;
  VectorZero(&startPosition);

  float adv = 0;
  float x = 0;
  float y = 0;

  for (int i = 0; i < 8; i++) {
    int delta = pts[i];
    if (delta == FONT_LAST)
      break;
    if (delta == FONT_UP) {
      next_moveto = 1;
      continue;
    }

    float dx = ((delta >> 4) & 0xF) * size;
    float dy = ((delta >> 0) & 0xF) * -size;

    if (next_moveto != 0) {
      startPosition.x = pos.x + x + dx;
      startPosition.y = pos.y + y + dy;
      if (x + dx > adv)
        adv = x + dx + (size * 4);
    } else {
      vector_t nextPosition;
      VectorInit(&nextPosition, pos.x + x + dx, pos.y + y + dy, 0);

      if (x + dx > adv)
        adv = x + dx + (size * 4);

      if (!extentsOnly) {
        ContextDrawLine(context, startPosition, nextPosition);
      }

      startPosition = nextPosition;
    }

    next_moveto = 0;

    adv -= x;
    if (adv < 12 * size) {
      adv = 12 * size;
    }
  }

  return adv;
}

float ContextDrawText(context_t *context, char *text, vector_t pos, float size,
                      int align) {
  float extents = 0;
  int len = strlen(text);

  float x = pos.x;
  float y = pos.y;

  // get extents
  for (int i = 0; i < len; i++) {
    char c = text[i];
    vector_t p;
    p.x = x;
    p.y = y;
    float adv = ContextDrawChar(context, c, p, size, true);
    if (c == ' ') {
      adv = ContextDrawChar(context, '.', p, size, true) / 2;
    }
    extents += adv;
  }

  // center
  if (align == 0) {
    x -= extents / 2;
  }

  // right
  if (align == 2) {
    x -= extents;
  }

  for (int i = 0; i < len; i++) {
    char c = text[i];
    vector_t p;
    p.x = x;
    p.y = y + (-size * 0.5);
    float adv = ContextDrawChar(context, c, p, size, false);
    if (c == ' ') {
      adv = ContextDrawChar(context, '.', p, size, true) / 2;
    }
    x += adv;
  }

  return x;
}