#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"
#include "util.h"

void PlayerHurt(entity_t *t, int amount) {
  t->onEffect = EffectFlicker;
  t->effectTime = 1.25;
  t->renderCollisionBounds = true;
}

void PlayerOnEnter(entity_t *t) { t->speed = 32 * 10; }

bool PlayerIsDucking(entity_t *t) {
  return t->state == DUCKING || t->state == CRAWLING;
}

bool PlayerIsIdle(entity_t *t) {
  if (t->state == JUMPING || t->state == ATTACKING || t->state == WALKING) {
    return false;
  }
  return t->state == IDLE || t->state == WHOA;
}

void PlayerOnUpdate(entity_t *t, float dt) {
  game_t *gm = GameInstance();
  t->frameSpeed = 12;

  bool tryAttack = false;
  bool tryJump = false;
  bool tryDuck = false;

  RectInitXYWH(&t->collisionBounds, 6, 6, 32 - 12, 32 - 6);

  // input
  bool pressingDown = gm->keys[DOWN];
  bool pressingUp = gm->keys[UP];
  bool pressingLeft = gm->keys[LEFT];
  bool pressingRight = gm->keys[RIGHT];
  bool pressingJump = gm->keysPressed[FIRE2];
  bool falling = t->velocity.y > 0;
  bool jumping = t->velocity.y < 0;
  bool running = false;
  bool crawling = false;

  float runTime = 3.5;

  if (gm->keys[FIRE2] && jumping) {
    pressingJump = true;
  }

  // settings
  float accel = 32 * 6;
  float jumpForce = 32 * 6;
  float maxJump = 32 * 3.35;
  float maxSpeedX = 32 * 10;
  float maxSpeedY = 32 * 20;
  float gravity = 32 * 20;
  float jumpTime = 0.5;

  // run
  int to180 = gm->keys[CRANK] - 180;
  to180 = ABS(to180);
  if (to180 < 40) {
    t->runTime = runTime;
  }
  if (t->runTime > 0) {
    t->runTime -= dt;
    running = true;
  }

  // speed
  t->frameSpeed = 12;
  if (!running) {
    t->frameSpeed = 6;
    accel *= 0.5;
  }

  if (jumping) {
    if (t->jumpTime > 0) {
      t->jumpTime -= dt;
      if (t->jumpTime <= 0) {
        jumping = false;
      }
    }
    float jumpHeight = t->anchor.y - t->position.y;
    if (jumpHeight > maxJump || !pressingJump) {
      t->velocity.y = 0;
      jumping = false;
    }
  }

  // horizontal movement
  if (jumping) {
    accel *= 1.5;
  }
  if (!pressingLeft && !pressingRight) {
    t->velocity.x = 0;
  }
  if (pressingLeft) {
    t->direction.x = -1;
  }
  if (pressingRight) {
    t->direction.x = 1;
  }
  t->acceleration.x = accel * t->direction.x;

  // sharp 360 turn
  if ((t->lt || pressingRight) && t->velocity.x < 0) {
    t->velocity.x = 0;
  }
  if ((t->rt || pressingLeft) && t->velocity.x > 0) {
    t->velocity.x = 0;
  }

  // duck

  // attack

  // collisions
  vector_t lfoot = VectorAdded(&t->position, &t->collisionBounds.lb);
  vector_t rfoot = VectorAdded(&t->position, &t->collisionBounds.rb);
  vector_t lshoulder = VectorAdded(&t->position, &t->collisionBounds.lt);
  vector_t rshoulder = VectorAdded(&t->position, &t->collisionBounds.rt);
  vector_t center = lfoot;
  vector_t midCenter = lshoulder;
  center.x += (rfoot.x - lfoot.x) / 2;
  midCenter.x += (rfoot.x - lfoot.x) / 2;
  lshoulder.x -= 2;
  lshoulder.y += 2;
  rshoulder.x += 2;
  rshoulder.y += 2;
  lfoot.x += 2;
  lfoot.y += 1;
  rfoot.x -= 2;
  rfoot.y += 1;

  entity_t *ladder = NULL;
  entity_t *ladderFoot = NULL;
  entity_t *leftPlatform = NULL;
  entity_t *rightPlatform = NULL;
  entity_t *centerPlatform = t->bottomCollision;
  entity_t *leftBlock = NULL;
  entity_t *rightBlock = NULL;
  entity_t *blockTop = t->topCollision;

  int collisionsChecked = 0;
  vector_t platformTop;

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (IsLadderEntity(e)) {
      if (RectContains(r, center)) {
        // ladderFoot->renderCollisionBounds = true;
        ladderFoot = e;
      }
      if (RectContains(r, midCenter)) {
        // ladder->renderCollisionBounds = true;
        ladder = e;
      }
    }
    if (!IsSolidEntity(e) || !AreEntitiesNear(e, t) || e == t) {
      continue;
    }
    collisionsChecked++;
    if (RectContains(r, lfoot)) {
      leftPlatform = e;
      platformTop = r.lt;
    }
    if (RectContains(r, rfoot)) {
      rightPlatform = e;
      platformTop = r.lt;
    }
    if (RectContains(r, lshoulder)) {
      leftBlock = e;
    }
    if (RectContains(r, rshoulder)) {
      rightBlock = e;
    }
  }
  
  if (blockTop) {
    jumping = false;
    blockTop->renderCollisionBounds = true;
  }

  bool onLeftPlatform = leftPlatform;
  bool onRightPlatform = rightPlatform;
  bool onPlatform = leftPlatform || rightPlatform;
  bool onLadder = ladder && ladderFoot;
  bool onTopLadder = !ladder && ladderFoot;

  // jump
  if (pressingJump && onPlatform) {
    t->velocity.y = -jumpForce;
    t->position.y -= 6;
    t->anchor = platformTop;
    if (t->jumpTime <= 0) {
      t->jumpTime = jumpTime;
    }
  }

  // gravity
  if (!onPlatform && !jumping) {
    t->acceleration.y = gravity;
    t->jumpTime = 0;
  }

  // sprite
  t->flipSprite = t->direction.x > 0;
  if (jumping || !onPlatform) {
    t->spriteSheet = SpriteSheet(PLAYER, JUMPING);
  } else if (t->velocity.x != 0) {
    t->spriteSheet = SpriteSheet(PLAYER, WALKING);
  } else {
    t->spriteSheet = SpriteSheet(PLAYER, IDLE);
  }

  // cap speeds
  if (crawling) {
    maxSpeedX *= 0.05;
  } else if (!running) {
    maxSpeedX *= 0.25;
  }
  if (ABS(t->velocity.x) > maxSpeedX) {
    t->velocity.x = maxSpeedX * SGN(t->velocity.x);
  }
  if (falling) {
    maxSpeedY = gravity;
  }
  if (ABS(t->velocity.y) > maxSpeedY) {
    t->velocity.y = maxSpeedY * SGN(t->velocity.y);
  }

  // process collisions
  EntityUpdate(t, dt);
  EntityCollideEnvironment(t, &t->velocity);

  rect_t tr = RectOffset(t->collisionBounds, t->position);

  // falling
  if (falling && t->bottomCollision) {
    rect_t tb = RectOffset(t->bottomCollision->collisionBounds,
                           t->bottomCollision->position);
    t->position.y = tb.lt.y - t->collisionBounds.lb.y;
    t->acceleration.y = 0;
    t->velocity.y = 0;
  }

}
