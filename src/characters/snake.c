#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"

// snake
void SnakeOnEnter(entity_t *t) { t->state = IDLE; }

void SnakeOnUpdate(entity_t *t, float dt) {
  if (t->life > 0 || ((entity_impl_t *)t)->onEffect) {
    // dead or dying
    VectorZero(&t->direction);
    VectorZero(&t->velocity);
    t->frameSpeed = 0;
    return;
  }

  game_t *gm = GameInstance();

  float fallSpeed = 32 * 14;
  float crawlSpeed = 32 * 1.5;

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
    n = (void*)n->next;
    if (!AreEntitiesNear(e, t) || e == t) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (e == gm->player) {
      if (((entity_impl_t *)e)->onEffect)
        continue;
      if (RectCollide(r, tr)) {
        if (e->state == FALLING && e->position.y + 16 < t->position.y) {
          EnemyEntityDie(t);
        } else {
          PlayerHurt(e, 1);
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

  // snake logic

  if (t->state == IDLE) {
    VectorZero(&t->direction);
    t->idleTime -= dt;
    if (t->idleTime <= 0) {
      if (Rand(1, 10) == 1) {
        t->runTime = 2 + Rand(0, 4);
        t->idleTime = 0;
        t->state = WALKING;
        if (Rand(0, 10) == 1) {
          t->direction.x = RndOr(-1, 1);
        } else {
          t->direction.x = t->flipSprite ? 1 : -1;
        }
      }
    }
  }

  VectorNormalize(&t->direction);
  t->direction = VectorScaled(&t->direction, crawlSpeed);
  t->velocity = t->direction;

  bool onPlatform = leftPlatform || rightPlatform;
  if (!onPlatform) {
    vector_t g;
    VectorInit(&g, 0, fallSpeed, 0);
    t->velocity = VectorAdded(&t->velocity, &g);
    if (!t->bottomCollision) {
      t->velocity.x = 0;
    }
  }

  if (t->state != IDLE) {
    t->idleTime = 0;
    if (t->runTime > 0) {
      t->runTime -= dt;
      if (t->runTime <= 0) {
        t->runTime = 0;
        t->idleTime = 0.1 + Rand(0, 3);
        t->state = IDLE;
      }
    }
  }

  if (t->velocity.x != 0) {
    t->spriteSheet = SpriteSheet(SNAKE, WALKING);
    t->frameSpeed = 8;
  } else {
    t->spriteSheet = SpriteSheet(SNAKE, 0);
  }
  if (t->velocity.x != 0) {
    t->flipSprite = t->direction.x > 0;
  }

  if ((!leftPlatform || t->leftCollision) && rightPlatform &&
      t->direction.x < 0) {
    t->direction.x = 1;
    t->flipSprite = RndOr(0, 1);
    if (Rand(1, 10) < 3) {
      t->state = IDLE;
    }
  }
  if ((!rightPlatform || t->rightCollision) && leftPlatform &&
      t->direction.x > 0) {
    t->direction.x = -1;
    t->flipSprite = RndOr(0, 1);
    if (Rand(1, 10) < 3) {
      t->state = IDLE;
    }
  }
}
