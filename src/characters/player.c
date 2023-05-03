#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"

void PlayerOnEnter(entity_t *t) {}

bool PlayerIsDucking(entity_t *t) {
  return t->state == DUCKING || t->state == CRAWLING;
}

bool PlayerIsIdle(entity_t *t) { return t->state == IDLE || t->state == WHOA; }

void PlayerOnUpdate(entity_t *t, float dt) {
  game_t *gm = GameInstance();
  t->frameSpeed = 12;

  float walkSpeed = 64;
  float runMultiplier = 1.5;
  float crawlSpeed = 32;
  float climbSpeed = 64;
  float jumpSpeed = 32 * 10;
  float fallSpeed = 32 * 12;

  bool tryJump = false;
  bool tryDuck = false;

  RectInitXYWH(&t->collisionBounds, 6, 0, 32 - 12, 32);

  // climb
  if (t->state == CLIMBING) {
    t->frameSpeed = 0;
    t->direction.y = 0;
    if (gm->keys[DOWN]) {
      t->frameSpeed = 6;
      t->direction.y = climbSpeed;
    }
    if (gm->keys[UP]) {
      t->frameSpeed = 6;
      t->direction.y = -climbSpeed;
    }
  }

  // duck
  if (gm->keys[DOWN] && t->state != CLIMBING) {
    tryDuck = true;
  }
  if (t->state == CRAWLING) {
    walkSpeed = crawlSpeed;
  }
  if (gm->keys[UP]) {
    // set temporarily
    t->state = IDLE;
  }

  if (gm->keys[LEFT]) {
    t->direction.x = -walkSpeed;
    t->state = PlayerIsDucking(t) ? CRAWLING : WALKING;
    t->flipSprite = false;
  } else if (gm->keys[RIGHT]) {
    t->direction.x = walkSpeed;
    t->state = PlayerIsDucking(t) ? CRAWLING : WALKING;
    t->flipSprite = true;
  } else {
    t->direction.x = 0;
    t->state = PlayerIsDucking(t) ? DUCKING : IDLE;
  }

  // jump
  if (gm->keysPressed[FIRE1]) {
    tryJump = true;
  }

  // collisions
  // t->renderCollisionBounds = true;

  vector_t lfoot = VectorAdded(&t->position, &t->collisionBounds.lb);
  vector_t rfoot = VectorAdded(&t->position, &t->collisionBounds.rb);
  vector_t lshoulder = VectorAdded(&t->position, &t->collisionBounds.lt);
  vector_t rshoulder = VectorAdded(&t->position, &t->collisionBounds.rt);
  vector_t center = lfoot;
  vector_t midCenter = lshoulder;
  center.x += (rfoot.x - lfoot.x) / 2;
  midCenter.x += (rfoot.x - lfoot.x) / 2;
  lshoulder.y += 2;
  rshoulder.y += 2;
  lfoot.x += 4;
  lfoot.y += 2;
  rfoot.x -= 4;
  rfoot.y += 2;

  entity_t *ladder = NULL;
  entity_t *ladderFoot = NULL;
  entity_t *leftPlatform = NULL;
  entity_t *rightPlatform = NULL;
  entity_t *leftBlock = NULL;
  entity_t *rightBlock = NULL;
  entity_t *blockTop = NULL;

  int collisionsChecked = 0;

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (IsLadderEntity(e)) {
      if (RectContains(r, center)) {
        ladderFoot = e;
        ladderFoot->renderCollisionBounds = true;
      }
      if (RectContains(r, midCenter)) {
        ladder = e;
        ladder->renderCollisionBounds = true;
      }
    }
    if (!IsSolidEntity(e) || !AreEntitiesNear(e, t) || e == t) {
      n = n->next;
      continue;
    }
    collisionsChecked++;
    if (RectContains(r, midCenter)) {
      e->renderCollisionBounds = true;
      blockTop = e;
    }
    if (RectContains(r, lfoot)) {
      e->renderCollisionBounds = true;
      leftPlatform = e;
    }
    if (RectContains(r, rfoot)) {
      e->renderCollisionBounds = true;
      rightPlatform = e;
    }
    if (RectContains(r, lshoulder)) {
      e->renderCollisionBounds = true;
      leftBlock = e;
    }
    if (RectContains(r, rshoulder)) {
      e->renderCollisionBounds = true;
      rightBlock = e;
    }
    n = n->next;
  }

  bool onLeftPlatform = leftPlatform;
  bool onRightPlatform = rightPlatform;
  bool onPlatform = leftPlatform || rightPlatform;
  bool onLadder = ladder || ladderFoot;

  // jump only on plaforms or getting off ladder
  if (tryJump && t->jumpTime <= 0 &&
      (onPlatform || (onLadder && (gm->keys[LEFT] || gm->keys[RIGHT])))) {
    t->jumpTime = 0.25;
  }

  // on edge
  if (t->idleTime > 1.2 && onLeftPlatform != onRightPlatform &&
      ((leftPlatform && !leftBlock) || (rightPlatform && !rightBlock))) {
    t->flipSprite = leftPlatform;
    if (t->state == IDLE) {
      t->state = WHOA;
      t->frameSpeed = 6;
    }
  }

  // block
  if (blockTop && t->jumpTime > 0) {
    t->position.y = blockTop->position.y + 32 - t->collisionBounds.rt.y;
    t->jumpTime *= 0.98;
    if (t->jumpTime < 0.1)
      t->jumpTime = 0;
    leftBlock = NULL;
    rightBlock = NULL;
  }

  if (leftBlock && t->direction.x < 0) {
    t->position.x = leftBlock->position.x + leftBlock->collisionBounds.rt.x -
                    t->collisionBounds.lt.x;
    if (t->state == WALKING && !onLadder) {
      t->state = PUSHING;
    }
  }
  if (rightBlock && t->direction.x > 0) {
    t->position.x = rightBlock->position.x + rightBlock->collisionBounds.lt.x -
                    t->collisionBounds.rt.x;
    if (t->state == WALKING && !onLadder) {
      t->state = PUSHING;
    }
  }
  if (onPlatform && t->direction.y > -1) {
    entity_t *platform = leftPlatform ? leftPlatform : rightPlatform;
    t->position.y = platform->position.y - t->collisionBounds.rb.y - 0.25;
  }

  if (onLadder) {
    t->renderCollisionBounds = true;
  }

  // duck / crawl
  if (tryDuck && !onLadder) {
    t->state = DUCKING;
  }

  // fall
  if (!onLadder && !onPlatform) {
    t->state = FALLING;
  }

  // climbing down
  if (ladderFoot && (!onPlatform || gm->keys[DOWN])) {
    t->state = CLIMBING;
    t->renderCollisionBounds = true;
  }
  // climbing up
  if (gm->keys[UP]) {
    if (ladder) {
      t->state = CLIMBING;
      t->renderCollisionBounds = true;
    }
  }

  if (!PlayerIsIdle(t)) {
    t->idleTime = 0;
  } else {
    t->idleTime += dt;
  }

  // jump
  if (t->jumpTime > 0) {
    t->jumpTime -= dt;
    t->state = JUMPING;
  }

  // run
  if (t->runTime > 0) {
    t->runTime -= dt;
    t->direction.x *= runMultiplier;
    t->frameSpeed *= runMultiplier;
  }

  t->spriteSheet = SpriteSheet(PLAYER, t->state);
  t->velocity = t->direction;

  if (t->state == JUMPING) {
    vector_t j;
    VectorInit(&j, 0, -jumpSpeed, 0);
    t->velocity = VectorAdded(&t->velocity, &j);
  }

  // gravity
  if (t->state == FALLING) {
    vector_t g;
    VectorInit(&g, 0, fallSpeed, 0);
    t->velocity = VectorAdded(&t->velocity, &g);
  }

  if (t->state == IDLE) {
    t->frame = 0;
  }
}
