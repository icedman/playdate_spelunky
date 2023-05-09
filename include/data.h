#ifndef _DATA_H_
#define _DATA_H_

#include "entity.h"

typedef struct {
  entityType_t type;
  void (*onEnter)(struct entity_t *);
  void (*onExit)(struct entity_t *);
  void (*onUpdate)(struct entity_t *, float delta_time);
  void (*onRender)(struct entity_t *, context_t *context);
  char *path;
} objectDefinition_t;

objectDefinition_t *ObjectDefinition(entityType_t t);

bool AreEntitiesNear(entity_t *entity1, entity_t *entity2);
bool IsSolidEntity(entity_t *entity);
bool IsItemEntity(entity_t *entity);
bool IsEnemyEntity(entity_t *entity);
bool IsBlockEntity(entity_t *entity);
bool IsCharacterEntity(entity_t *entity);
bool IsLadderEntity(entity_t *entity);
bool IsBrickOrBlock(entity_t *entity);
void EnemyEntityDie(entity_t *entity);

void PlayerHurt(entity_t *t, int amount);

void EntityCollideEnvironment(entity_t *t, vector_t *direction);
entity_t *EntityAtPoint(vector_t pos, list_t *entities,
                        bool (*filter)(entity_t *));

#endif // _DATA_H_