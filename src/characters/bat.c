#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"

void BatOnEnter(entity_t *t) {
  VectorInit(&t->direction, -1, 0, 0);
  t->state = HANGING;
}

void BatOnUpdate(entity_t *t, float dt) {
  if (t->life > 0 || t->onEffect) {
    // dead or dying
    VectorZero(&t->direction);
    VectorZero(&t->velocity);
    t->frameSpeed = 0;
    return;
  }

  game_t *gm = GameInstance();

  float flySpeed = 4 * 32;
  t->frameSpeed = 8;

  RectInitXYWH(&t->collisionBounds, 6, 8, 32 - 12, 32 - 14);
  if (t->state == HANGING) {
    RectInitXYWH(&t->collisionBounds, 6, 0, 32 - 12, 32 - 4);
  }
  EntityCollideEnvironment(t, &t->velocity);

  rect_t tr = RectOffset(t->collisionBounds, t->position);

  // t->renderCollisionBounds = true;

  vector_t head = VectorAdded(&t->position, &t->collisionBounds.lt);
  vector_t rfoot = VectorAdded(&t->position, &t->collisionBounds.rb);
  head.x += RectWidth(tr) / 2;
  head.y -= 16;

  if (t->leftCollision) {
    t->direction.x = 1;
  }
  if (t->rightCollision) {
    t->direction.x = -1;
  }

  t->flipSprite = t->direction.x > 0;

  entity_t *topBlock = NULL;

  vector_t pos = t->position;
  float area = 160;
  pos.y += (area / 2);
  float distanceToPlayer = VectorDistanceTo(&pos, &gm->player->position);

  // bat logic
  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;

    if (AreEntitiesNear(e, t) && !e->onEffect) {
      rect_t r = RectOffset(e->collisionBounds, e->position);
      if (e == gm->player) {
        if (RectCollide(r, tr)) {
          if (e->state == FALLING && e->position.y + 16 < t->position.y) {
            EnemyEntityDie(t);
          } else {
            PlayerHurt(e, 1);
          }
        }
        continue;
      }
      if (RectContains(r, head)) {
        topBlock = e;
        ;
        // e->renderCollisionBounds = true;
      }
    }
  }

  if (!topBlock && t->state == HANGING) {
    t->state = FLYING;
  }

  if (t->state == HANGING) {
    t->frame = 0;
    VectorZero(&t->velocity);
    t->spriteSheet = SpriteSheet(BAT, HANGING);
    if (distanceToPlayer < area) {
      t->state = FLYING;
    }
    return;
  } else {
    t->spriteSheet = SpriteSheet(BAT, 0);
  }

  if (t->state == FLYING) {
    if (t->direction.x == 0) {
      t->direction.x = RndOr(-1, 1);
    }
    if (distanceToPlayer > 300) {
      t->direction.x = 0;
      t->direction.y = -1;
      if (topBlock && t->topCollision) {
        t->state = HANGING;
        t->position.y = topBlock->position.y + topBlock->collisionBounds.lb.y;
      }
    } else {
      if (topBlock) {
        t->direction.y = 0;
        t->position.y = topBlock->position.y + topBlock->collisionBounds.lb.y;
      }
    }
  }

  VectorNormalize(&t->direction);
  t->direction = VectorScaled(&t->direction, flySpeed);
  t->velocity = t->direction;
}
