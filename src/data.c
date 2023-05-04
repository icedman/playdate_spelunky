#include "data.h"
#include "context.h"
#include "game.h"

void PlayerOnEnter(entity_t *t);
void PlayerOnUpdate(entity_t *t, float dt);
void PushBlockOnEnter(entity_t *t);
void PushBlockOnUpdate(entity_t *t, float dt);
void SnakeOnEnter(entity_t *t);
void SnakeOnUpdate(entity_t *t, float dt);
void WhipOnEnter(entity_t *t);
void WhipOnUpdate(entity_t *t, float dt);

// clang-format off
static objectDefinition_t defs[] = {
  {EMPTY_SPACE, NULL, NULL, NULL, NULL},
  {PUSH_BLOCK, PushBlockOnEnter, NULL, PushBlockOnUpdate, NULL},
  {BLOCK, NULL, NULL, NULL, NULL},
  {BRICK, NULL, NULL, NULL, NULL},
  {BRICK_2, NULL, NULL, NULL, NULL},
  {LADDER, NULL, NULL, NULL, NULL},
  {LADDER_TOP, NULL, NULL, NULL, NULL},
  {PLAYER, PlayerOnEnter, NULL, PlayerOnUpdate, NULL},
  {SNAKE, SnakeOnEnter, NULL, SnakeOnUpdate, NULL},
  {WHIP, WhipOnEnter, NULL, WhipOnUpdate, NULL},
  {SPIKES, NULL, NULL, NULL, NULL},
  {ENTRANCE, NULL, NULL, NULL, NULL},
  {EXIT, NULL, NULL, NULL, NULL},
  {TYPE_END}
};
// clang-format on

objectDefinition_t *ObjectDefinition(objectType_e t) {
  for (int i = 0;; i++) {
    if (i == TYPE_END)
      break;
    if (defs[i].type == t) {
      return &defs[i];
    }
  }
  return NULL;
}

bool AreEntitiesNear(entity_t *entity1, entity_t *entity2) {
  vector_t dist = VectorSubtracted(&entity1->position, &entity2->position);
  int nearDistance = 64;
  return ABS(dist.x) < nearDistance && ABS(dist.y) < nearDistance;
}

bool IsLadderEntity(entity_t *entity) {
  switch (entity->type) {
  case LADDER:
  case LADDER_TOP:
    return true;
  }
  return false;
}

bool IsSolidEntity(entity_t *entity) {
  switch (entity->type) {
  case PUSH_BLOCK:
  case BLOCK:
  case BRICK:
  case BRICK_2:
    return true;
  }
  return false;
}

bool IsEnemyEntity(entity_t *entity) {
  return (entity->type > START_ENEMIES && entity->type < END_ENEMIES);
}

bool IsBlockEntity(entity_t *entity) {
  return (entity->type > START_BLOCKS && entity->type < END_BLOCKS);
}

bool IsCharacterEntity(entity_t *entity) {
  return (entity->type > START_CHARACTERS && entity->type < END_CHARACTERS);
}

void EnemyEntityDie(entity_t *entity) {
  entity->renderCollisionBounds = true;
  entity->life = 1.0;
  entity->onEffect = EffectFlicker;
}

void EntityCollideEnvironment(entity_t *t, vector_t *direction) {
  game_t *gm = GameInstance();

  rect_t tr = RectOffset(t->collisionBounds, t->position);
  vector_t tc = RectCenter(tr);

  memset(t->collisions, 0, sizeof(void *) * 4);

  node_t *n = gm->entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;

    rect_t r = RectOffset(e->collisionBounds, e->position);
    if (!IsSolidEntity(e) || !AreEntitiesNear(e, t) || e == t) {
      continue;
    }

    if (RectCollide(tr, r)) {
      float tolerance = 2;
      t->renderCollisionBounds = true;
      // top
      if (r.lb.y > tr.lt.y && (ABS((r.lb.y - tr.lt.y)) < tolerance)) {
        // e->renderCollisionBounds = true;
        t->position.y = r.lb.y - t->collisionBounds.lt.y;
        t->topCollision = e;
      }
      // bottom
      if (r.lt.y < tr.lb.y && (ABS((r.lt.y - tr.lb.y)) < tolerance)) {
        // e->renderCollisionBounds = true;
        t->position.y = r.lt.y - t->collisionBounds.rb.y;
        t->bottomCollision = e;
      }
      // left
      if (r.rt.x > tr.lt.x && (ABS((r.rt.x - tr.lt.x)) < tolerance)) {
        // e->renderCollisionBounds = true;
        t->position.x = r.rt.x - t->collisionBounds.lt.x;
        t->leftCollision = e;
      }
      // right
      if (r.lt.x < tr.rt.x && (ABS((r.lt.x - tr.rt.x)) < tolerance)) {
        // e->renderCollisionBounds = true;
        t->position.x = r.lt.x - t->collisionBounds.rt.x;
        t->rightCollision = e;
      }
    }
  }
}