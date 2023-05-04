#include "renderer.h"
#include "data.h"
#include "game.h"
#include "polygon.h"

#include <math.h>
#include <stdio.h>

void RenderShape(context_t *context, float *points, vector_t pos, float angle,
                 float radius, bool close) {
  points += 3;
  polygon_t p;
  p.sides = 0;
  for (int i = 0; i < POLYGON_MAX_SIDES; i++) {
    if (points[0] == -1 && points[1] == -1 && points[2] == -1) {
      break;
    }
    p.points[i].x = points[0];
    p.points[i].y = points[1];
    p.points[i].z = points[2];
    p.sides++;
    points += 3;
  }
  ContextDrawPolygon(context, &p, pos, angle, radius, close);
}

void RenderParticle(entity_t *e, context_t *context) {
  vector_t v = VectorScaled(&e->velocity, 0.1);
  vector_t v2 = VectorSubtracted(&e->position, &v);
  ContextDrawLine(context, e->position, v2);
}

void RenderExplosion(entity_t *entity, context_t *context) {
  ContextSave(context);
  ContextSetColor(context, 50, 100, 50);
  ContextDrawPolygon(context, &polygon_circle, entity->position,
                     VectorAngle(&entity->direction), entity->radius, true);
  ContextRestore(context);
}

void RenderFloatingText(entity_t *entity, context_t *context) {
  ContextDrawText(context, (char *)entity->data, entity->position, 0.025, 0);
}

void RenderSprite(entity_t *e, context_t *context) {
  if (e->invisible)
    return;

  spriteSheet_t *ss = e->spriteSheet;
  if (ss && ss->images[0] == NULL) {
    for (int i = 0; i < ss->frames; i++) {
      char temp[255];
      sprintf(temp, ss->path, i);
      ss->images[i] = loadImage(context, temp);
    }
  }

  int frame = ((int)e->frame) % ss->frames;
  void *img = ss->images[frame];
  if (img) {
    drawImage(context, img, e->position, e->flipSprite);
  }

  // collision bounds
  if (context->renderDebug && e->renderCollisionBounds) {
    vector_t lt = e->collisionBounds.lt;
    vector_t rb = e->collisionBounds.rb;
    float points[] = {0,    0,    0, lt.x, lt.y, 0, rb.x, lt.y, 0,
                      rb.x, rb.y, 0, lt.x, rb.y, 0, -1,   -1,   -1};
    RenderShape(context, points, e->position, 0, 1, true);
    e->renderCollisionBounds = false;
  }
}

void RenderEntities(list_t *entityList, context_t *context) {
  node_t *n = entityList->first;
  while (n) {
    entity_t *e = (entity_t *)n->data;
    if (e->onRender) {
      if (e->onEffect) {
        printf("--\n");
      }
      e->onRender(e, context);
    } else {
      RenderSprite(e, context);
    }
    n = n->next;
  }
}
