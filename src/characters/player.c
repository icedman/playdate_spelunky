#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"

void PlayerHurt(entity_t *t, int amount) {
  t->onEffect = EffectFlicker;
  t->effectTime = 1.25;
  t->renderCollisionBounds = true;
}

void PlayerOnEnter(entity_t *t) {}

bool PlayerIsDucking(entity_t *t) {
  return t->state == DUCKING || t->state == CRAWLING;
}

bool PlayerIsIdle(entity_t *t) {
  if (t->jumpTime > 0 || t->attackTime > 0 || t->pushTime > 0) {
    return false;
  }
  return t->state == IDLE || t->state == WHOA;
}

void PlayerOnUpdate(entity_t *t, float dt) {
  game_t *gm = GameInstance();
  t->frameSpeed = 12;

  float walkSpeed = 32 * 3;
  float runMultiplier = 1.5;
  float runFrameMultipler = 1.2;
  float crawlSpeed = 32 * 1;
  float climbSpeed = 32 * 2;
  float jumpSpeed = 32 * 8;
  float fallSpeed = 32 * 10;

  float attackTime = 0.4;
  float runTime = 0.25;
  float jumpTime = 0.35;

  bool tryAttack = false;
  bool tryJump = false;
  bool tryDuck = false;
  bool hanging = false;

  RectInitXYWH(&t->collisionBounds, 6, 6, 32 - 12, 32 - 6);
  EntityCollideEnvironment(t, &t->velocity);

  VectorZero(&t->direction);

  // float speed = 32*4;
  // if (gm->keys[UP]) {
  //   t->position.y -= speed*dt;
  // }
  // if (gm->keys[DOWN]) {
  //   t->position.y += speed*dt;
  // }
  // if (gm->keys[LEFT]) {
  //   t->position.x -= speed*dt;
  // }
  // if (gm->keys[RIGHT]) {
  //   t->position.x += speed*dt;
  // }
  // return;

  // run
  int to180 = gm->keys[CRANK] - 180;
  to180 = ABS(to180);
  if (to180 < 40) {
    t->runTime = 0.25;
  }

  // attack
  if (gm->keysPressed[FIRE1]) {
    tryAttack = true;
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
    if (!t->leftCollision || t->state == FALLING) {
      hanging = t->state == FALLING;
      t->direction.x = -walkSpeed;
    } else {
      t->direction.x = walkSpeed;
    }
    t->state = PlayerIsDucking(t) ? CRAWLING : WALKING;
    t->flipSprite = false;
  } else if (gm->keys[RIGHT]) {
    if (!t->rightCollision || t->state == FALLING) {
      hanging = t->state == FALLING;
      t->direction.x = walkSpeed;
    } else {
      t->direction.x = -walkSpeed;
    }
    t->state = PlayerIsDucking(t) ? CRAWLING : WALKING;
    t->flipSprite = true;
  } else {
    t->direction.x = 0;
    t->state = PlayerIsDucking(t) ? DUCKING : IDLE;
  }

  if (hanging) {
    if ((gm->keys[LEFT] && t->leftCollision) ||
        (gm->keys[RIGHT] && t->rightCollision)) {
      // todo only allow climb to ledge
      jumpTime *= 0.5;
    } else {
      hanging = false;
    }
  }

  // jump
  if (gm->keys[FIRE2]) {
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
  lshoulder.x -= 2;
  lshoulder.y += 2;
  rshoulder.x += 2;
  rshoulder.y += 2;
  lfoot.x += 4;
  lfoot.y += 1;
  rfoot.x -= 4;
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

  bool onLeftPlatform = leftPlatform;
  bool onRightPlatform = rightPlatform;
  bool onPlatform = leftPlatform || rightPlatform;
  bool onLadder = ladder && ladderFoot;
  bool onTopLadder = !ladder && ladderFoot;

  // jump only on plaforms or getting off ladder
  if (tryJump && t->jumpTime <= 0 &&
      (onPlatform || onLadder || onTopLadder || hanging)) {
    t->jumpTime = jumpTime;
  }

  if (!tryJump) {
    t->jumpTime *= 0.8;
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
  }

  if (onLadder) {
    t->renderCollisionBounds = true;
  }

  // duck / crawl
  if (tryDuck && !onLadder) {
    t->state = DUCKING;
  }

  // fall
  if (!ladder && !ladderFoot && !onPlatform) {
    t->state = FALLING;
  }

  // climbing down
  if (ladderFoot && (ladder || gm->keys[DOWN])) {
    t->state = CLIMBING;
    t->renderCollisionBounds = true;
  }

  // climbing up
  if (gm->keys[UP]) {
    if (ladderFoot) {
      t->state = CLIMBING;
      t->renderCollisionBounds = true;
    } else if (t->state == CLIMBING) {
      t->state = IDLE;
      t->frameSpeed = 0;
      t->direction.y = 0;
    }
  }

  // climb
  if (t->state == CLIMBING) {
    t->frameSpeed = 0;
    t->direction.y = 0;
    if (gm->keys[DOWN]) {
      t->frameSpeed = 8;
      t->direction.y = climbSpeed;
    }
    if (gm->keys[UP]) {
      t->frameSpeed = 8;
      t->direction.y = -climbSpeed;
      if (onPlatform) {
        t->direction.y *= 10;
      }
    }
  }

  // pushing
  if (onPlatform || onLadder) {
    if (leftBlock && gm->keys[LEFT]) {
      if (t->state != PUSHING && (!onLadder || leftBlock)) {
        t->state = PUSHING;
        t->push = leftBlock;
      }
    }
    if (rightBlock && gm->keys[RIGHT]) {
      if (t->state != PUSHING && (!onLadder || rightBlock)) {
        t->state = PUSHING;
        t->push = rightBlock;
      }
    }
  }
  if (t->state != PUSHING) {
    t->pushTime = 0;
    t->push = NULL;
  }

  // idle
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
    t->frameSpeed *= runFrameMultipler;
  }

  int finalFrame = t->state;
  if (hanging) {
    finalFrame = JUMPING;
  }

  if (tryAttack) {
    // check if holding something
    if (t->attackTime <= 0) {
      t->attackTime = attackTime;
      t->frame = 0;
    }
  }

  if (finalFrame == PUSHING) {
    if (t->pushTime < 0.5) {
      finalFrame = WALKING;
    }
    t->pushTime += dt;
  }

  if (finalFrame == CLIMBING && !gm->keys[DOWN] && !gm->keys[UP]) {
    if (ladder == ladderFoot) {
      finalFrame = IDLE;
    }
  }

  // attack
  entity_t *w = GameInstance()->whip;
  w->invisible = true;
  if (t->attackTime > 0) {
    t->attackTime -= dt;
    finalFrame = ATTACKING;
    w->invisible = false;
    w->flipSprite = !t->flipSprite;
    w->frame = t->frame;
    w->position = t->position;
    w->position.y += 4;
    if (t->frame < 1.5) {
      w->spriteSheet = SpriteSheet(WHIP, 0);
      w->position.x += 24 * (t->flipSprite ? -1 : 1);
    } else {
      w->spriteSheet = SpriteSheet(WHIP, 1);
      w->position.x += 24 * (t->flipSprite ? 1 : -1);
    }
    if (t->frame > 10) {
      t->frame = 10;
    }
  }

  t->spriteSheet = SpriteSheet(PLAYER, finalFrame);
  t->velocity = t->direction;

  if (t->state == JUMPING && !ladder && !blockTop) {
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

  if (finalFrame == IDLE) {
    t->frame = 0;
  }

  // printf("%d\n", collisionsChecked);
}
