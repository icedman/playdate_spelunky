#include "context.h"
#include "entity.h"
#include "game.h"

void WhipOnEnter(entity_t *t) { t->invisible = true; }

void WhipOnUpdate(entity_t *t, float dt) {
  if (t->invisible)
    return;
  game_t *gm = GameInstance();

  if (t->frame < 1.5)
    return;

  RectInitXYWH(&t->collisionBounds, 0, 8, 32, 32 - 16);
  rect_t tr = RectOffset(t->collisionBounds, t->position);

  // t->renderCollisionBounds = true;

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (!AreEntitiesNear(e, t) || e == t) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (IsEnemyEntity(e) && e->life == 0) {
      if (RectCollide(r, tr)) {
        EnemyEntityDie(e);
      }
    }
  }
}
