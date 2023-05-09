#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"
#include "renderer.h"
#include "sprites.h"

void SpiderOnUpdate(entity_t *t, float dt);

void SpiderOnEnter(entity_t *t) { t->state = IDLE; }

void SpiderHangOnRender(entity_t *t, context_t *context) {
  if (t->anchor.x == 0 && t->anchor.y == 0)
    return; // not ready yet

  vector_t c = RectCenter(RectOffset(t->collisionBounds, t->position));
  vector_t a = t->anchor;
  ContextSave(context);
  context->state->r = 255;
  context->state->g = 255;
  context->state->b = 255;
  ContextDrawLine(context, c, a);
  ContextRestore(context);
  RenderSprite(t, context);
}

void SpiderHangOnUpdate(entity_t *t, float dt) {
  if (t->life > 0 || t->onEffect) {
    // dead or dying
    VectorZero(&t->direction);
    VectorZero(&t->velocity);
    t->frameSpeed = 0;
    return;
  }

  game_t *gm = GameInstance();

  float fallSpeed = 32 * 6;
  float flipFallSpeed = fallSpeed * 0.05;
  float climbSpeed = 32 * 4;

  RectInitXYWH(&t->collisionBounds, 0, 0, 32, 32 - 8);
  EntityCollideEnvironment(t, &t->velocity);

  rect_t tr = RectOffset(t->collisionBounds, t->position);
  vector_t tc = RectCenter(tr);

  // t->renderCollisionBounds = true;

  vector_t head = VectorAdded(&t->position, &t->collisionBounds.lt);
  vector_t foot = VectorAdded(&t->position, &t->collisionBounds.rb);
  head.y -= 1;
  foot.y += 1;

  entity_t *ceiling = NULL;
  entity_t *platform = NULL;

  bool downGoesTheSpider = false;

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (e == t) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    vector_t c = RectCenter(r);
    if (e == gm->player) {
      if (e->onEffect)
        continue;
      if (RectCollide(r, tr)) {
        if (e->state == FALLING && e->position.y + 16 < t->position.y) {
          EnemyEntityDie(t);
        } else {
          PlayerHurt(e, 1);
        }
      }

      float d = ABS((tc.x - c.x));
      float area = !ceiling ? 128 : 8;
      if (d < area && tc.y < c.y) {
        downGoesTheSpider = true;
        // e->renderCollisionBounds = true;
        // t->renderCollisionBounds = true;
      }
      continue;
    }

    if (RectContains(r, head)) {
      // e->renderCollisionBounds = true;
      ceiling = e;
    }
    if (RectContains(r, foot)) {
      // e->renderCollisionBounds = true;
      platform = e;
    }
  }

  // spider logic
  VectorZero(&t->direction);
  t->direction.y = (downGoesTheSpider ? fallSpeed : -climbSpeed);

  if (t->direction.y < 0 && ceiling) {
    // hang and rest
    if (t->spriteSheet->frames != 1) {
      t->spriteSheet = SpriteSheet(SPIDER_HANG, 0);
    }
    t->frame = 0;
    t->direction.y = 0;
    t->anchor = t->position;
    t->anchor.x = RectCenter(tr).x;
  }
  if (!ceiling) {
    // flip
    if (t->spriteSheet->frames == 1) {
      t->frameSpeed = 12;
      t->spriteSheet = SpriteSheet(SPIDER_HANG, JUMPING);
    }
    if (t->frame >= t->spriteSheet->frames) {
      t->frame = t->spriteSheet->frames - 1;
    } else {
      fallSpeed = flipFallSpeed;
    }
  }
  if (platform || t->bottomCollision) {
    t->direction.y = 0;
    t->position.y -= 12;
    // be a jumping spider
    t->onUpdate = SpiderOnUpdate;
    t->onRender = NULL;
    t->spriteSheet = SpriteSheet(SPIDER, 0);
  }

  t->velocity = t->direction;
}

void SpiderOnUpdate(entity_t *t, float dt) {
  if (t->life > 0 || t->onEffect) {
    // dead or dying
    VectorZero(&t->direction);
    VectorZero(&t->velocity);
    t->frameSpeed = 0;
    return;
  }

  game_t *gm = GameInstance();

  bool falling = t->velocity.y > 0;
  bool jumping = t->velocity.y < 0;
  bool tryJump = gm->keysPressed[FIRE1];
  if (gm->keysPressed[LEFT]) {
    t->direction.x = -1;
  }
  if (gm->keysPressed[RIGHT]) {
    t->direction.x = 1;
  }
  float fallSpeed = 32 * 14;
  float crawlSpeed = 32 * 1.5;
  float jumpSpeed = 32 * 8;
  float jumpTime = 0.35;
  float jumpHeight = 32 * 2.25; // 3 tiles

  RectInitXYWH(&t->collisionBounds, 6, 8, 32 - 12, 32 - 8);
  EntityCollideEnvironment(t, &t->velocity);

  rect_t tr = RectOffset(t->collisionBounds, t->position);

  t->renderCollisionBounds = t->state == JUMPING;

  vector_t lfoot = VectorAdded(&t->position, &t->collisionBounds.lb);
  vector_t rfoot = VectorAdded(&t->position, &t->collisionBounds.rb);
  vector_t lshoulder = VectorAdded(&t->position, &t->collisionBounds.lt);
  vector_t rshoulder = VectorAdded(&t->position, &t->collisionBounds.rt);
  lfoot.x += 4;
  lfoot.y += 1;
  rfoot.x -= 4;
  rfoot.y += 1;
  lshoulder.x -= 2;
  lshoulder.y += 2;
  rshoulder.x += 2;
  rshoulder.y += 2;

  entity_t *leftPlatform = NULL;
  entity_t *rightPlatform = NULL;
  entity_t *leftBlock = NULL;
  entity_t *rightBlock = NULL;

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (!AreEntitiesNear(e, t) || e == t) {
      continue;
    }
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (e == gm->player) {
      if (e->onEffect)
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
    if (RectContains(r, lshoulder)) {
      // e->renderCollisionBounds = true;
      leftBlock = e;
    }
    if (RectContains(r, rshoulder)) {
      // e->renderCollisionBounds = true;
      rightBlock = e;
    }
  }

  bool onPlatform = leftPlatform || rightPlatform;

  if (t->topCollision) {
    t->jumpTime = 0;
  }

  // spider logic

  // thud - fell on the ground
  if (falling) {
    if (onPlatform) {
      t->state = IDLE;
      t->jumpTime = 0;
      t->velocity.y = 0;
    }
  }

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

  if (tryJump && t->jumpTime <= 0 && onPlatform && !jumping) {
    t->jumpTime = jumpTime;
    t->jumpStart = t->position.y;
    t->state = JUMPING;
  }

  VectorNormalize(&t->direction);

  t->velocity.y = 0;
  t->velocity.x = t->direction.x * crawlSpeed;

  // jump (todo: simplify, code too complex)
  if (t->jumpTime > 0) {
    t->jumpTime -= dt;
    t->state = JUMPING;
    if (t->jumpStart - t->position.y > jumpHeight) {
      t->position.y = t->jumpStart - jumpHeight;
      t->jumpTime = 0;
    } else {
      t->velocity.x = t->direction.x * jumpSpeed * 0.8;
      t->velocity.y = -jumpSpeed;
    }
  } else if (!onPlatform) {
    t->velocity.x = t->direction.x * jumpSpeed * 0.8;
    if (leftBlock || rightBlock) {
      t->velocity.x = 0;
      t->direction.x = 0;
      if (leftBlock) {
        t->position.x += 1;
      }
      if (rightBlock) {
        t->position.x -= 1;
      }
    }
  }

  if (!onPlatform && t->jumpTime <= 0) {
    vector_t g;
    VectorInit(&g, 0, fallSpeed, 0);
    t->velocity = VectorAdded(&t->velocity, &g);
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
    t->frameSpeed = 12;
  } else {
    t->frameSpeed = 0;
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
