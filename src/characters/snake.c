#include "context.h"
#include "entity.h"
#include "game.h"

// snake
void SnakeOnEnter(entity_t *t) {}

void SnakeOnUpdate(entity_t *t, float dt) {
  if (t->life > 0 || t->onEffect) {
    // dead or dying
    return;
  }

  game_t *gm = GameInstance();

  float fallSpeed = 32 * 14;

  RectInitXYWH(&t->collisionBounds, 6, 8, 32 - 12, 32 - 8);
  EntityCollideEnvironment(t, &t->velocity);

  rect_t tr = RectOffset(t->collisionBounds, t->position);

  // t->renderCollisionBounds = true;

  vector_t lfoot = VectorAdded(&t->position, &t->collisionBounds.lb);
  vector_t rfoot = VectorAdded(&t->position, &t->collisionBounds.rb);
  lfoot.x += 4;
  lfoot.y += 1;
  rfoot.x -= 4;
  rfoot.y += 1;

  entity_t *leftPlatform = NULL;
  entity_t *rightPlatform = NULL;

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (!AreEntitiesNear(e, t) || e == t) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (e == gm->player) {
      if (e->attackTime > 0 || e->effectTime > 0)
        continue;
      if (RectCollide(r, tr)) {
        if (e->state == FALLING) {
          EnemyEntityDie(t);
        } else {
          e->onEffect = EffectFlicker;
          e->effectTime = 0.75;
          e->renderCollisionBounds = true;
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
