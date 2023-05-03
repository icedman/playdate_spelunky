#ifndef _DATA_H_
#define _DATA_H_

#include "entity.h"

typedef enum {
  EMPTY_SPACE = 0,
  //
  BLOCK,
  BRICK,
  BRICK_2,
  BRICK_DOWN,
  BRICK_GOLD,
  CAVE_BOTTOM,
  CAVE_BOTTOM_L,
  CAVE_BOTTOM_R,
  CAVE_LEFT,
  CAVE_RIGHT,
  CAVE_SMOOTH,
  CAVE_TOP,
  CAVE_TOP_2,
  CAVE_UP,
  CAVE_UP_2,
  LADDER,
  LADDER_TOP,
  VINE,
  VINE_BOTTOM,
  VINE_SOURCE,
  VINE_TOP,
  //
  ENTRANCE,
  EXIT,
  // traps
  SPIKES,
  SPIKES_BLOOD,
  // characters
  PLAYER,
  SNAKE,
  DAMSEL,
  TYPE_END
} objectType_e;

typedef struct {
  objectType_e type;
  void (*onEnter)(struct entity_t *);
  void (*onExit)(struct entity_t *);
  void (*onUpdate)(struct entity_t *, float delta_time);
  void (*onRender)(struct entity_t *, context_t *context);
  char *path;
} objectDefinition_t;

objectDefinition_t *ObjectDefinition(objectType_e t);

bool AreEntitiesNear(entity_t *entity1, entity_t *entity2);
bool IsSolidEntity(entity_t *entity);
bool IsLadderEntity(entity_t *entity);

#endif // _DATA_H_