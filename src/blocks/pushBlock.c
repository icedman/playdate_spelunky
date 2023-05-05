#include "context.h"
#include "entity.h"
#include "game.h"

void PushBlockOnEnter(entity_t *t) {}

void PushBlockOnUpdate(entity_t *t, float dt) {
  game_t *gm = GameInstance();

  float fallSpeed = 32 * 14;

  RectInitXYWH(&t->collisionBounds, 2, 0, 32 - 4, 32);
  EntityCollideEnvironment(t, &t->velocity);

  rect_t tr = RectOffset(t->collisionBounds, t->position);

  t->renderCollisionBounds = true;

  vector_t lfoot = VectorAdded(&t->position, &t->collisionBounds.lb);
  vector_t rfoot = VectorAdded(&t->position, &t->collisionBounds.rb);
  lfoot.x += 4;
  lfoot.y += 1;
  rfoot.x -= 4;
  rfoot.y += 1;

  entity_t *leftPlatform = NULL;
  entity_t *rightPlatform = NULL;

  VectorZero(&t->direction);

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (!AreEntitiesNear(e, t) || e == t) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (e == gm->player) {
      if (RectCollide(r, tr)) {
        if (t == e->push && e->state == PUSHING && e->pushTime >= 0.5) {
          t->direction = VectorScaled(&e->velocity, 0.8);
        }
      }
      continue;
    }

    if (RectContains(r, lfoot)) {
      // e->renderCollisionBounds = true;
      leftPlatform = e;
    }
    if (RectContains(r, rfoot)) {
      // e->renderCollisionBounds = true;
      rightPlatform = e;
    }
  }

  t->velocity = t->direction;

  bool onPlatform = leftPlatform || rightPlatform;
  if (!onPlatform) {
    vector_t g;
    VectorInit(&g, 0, fallSpeed, 0);
    t->velocity = VectorAdded(&t->velocity, &g);
  }
}
