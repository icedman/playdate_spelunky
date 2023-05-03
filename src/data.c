#include "data.h"
#include "context.h"

void PlayerOnEnter(entity_t *t);
void PlayerOnUpdate(entity_t *t, float dt);
void SnakeOnEnter(entity_t *t);
void SnakeOnUpdate(entity_t *t, float dt);

// clang-format off
static objectDefinition_t defs[] = {
  {EMPTY_SPACE, NULL, NULL, NULL, NULL},
  {BLOCK, NULL, NULL, NULL, NULL},
  {BRICK, NULL, NULL, NULL, NULL},
  {BRICK_2, NULL, NULL, NULL, NULL},
  {LADDER, NULL, NULL, NULL, NULL},
  {LADDER_TOP, NULL, NULL, NULL, NULL},
  {PLAYER, PlayerOnEnter, NULL, PlayerOnUpdate, NULL},
  {SNAKE, SnakeOnEnter, NULL, SnakeOnUpdate, NULL},
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
  return ABS(dist.x) < 98 && ABS(dist.y) < 98;
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
  case BLOCK:
  case BRICK:
  case BRICK_2:
    return true;
  }
  return false;
}
