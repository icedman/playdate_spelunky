#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "context.h"
#include "sprites.h"
#include "util.h"
#include "vector.h"

typedef enum {
  IDLE = 0,
  WALKING,
  ATTACKING,
  JUMPING,
  HANGING,
  DUCKING,
  CRAWLING,
  FALLING,
  PUSHING,
  CLIMBING,
  CLIMBING_ROPE,
  CLIMBING_VINE,
  WHOA,
  STUNNED,
} entityState_t;

typedef struct entity_t {
  vector_t position;
  vector_t direction;
  vector_t velocity;
  float radius;
  float life;
  float ticks;
  int type;
  bool invisible;
  bool entered;

  void (*onEnter)(struct entity_t *);
  void (*onExit)(struct entity_t *);
  void (*onUpdate)(struct entity_t *, float delta_time);
  void (*onRender)(struct entity_t *, context_t *context);
  void (*onEffect)(struct entity_t *, float delta_time);
  void *data;

  float effectTime;
  float idleTime;
  float jumpTime;
  float runTime;
  float attackTime;

  spriteSheet_t *spriteSheet;
  entityState_t state;
  float frameSpeed;
  float frame;
  bool flipSprite;

  rect_t collisionBounds;
  bool renderCollisionBounds;

  union {
    struct entity_t *collisions[4];
    struct {
      struct entity_t *leftCollision;
      struct entity_t *rightCollision;
      struct entity_t *topCollision;
      struct entity_t *bottomCollision;
    };
  };

  int hp;
} entity_t;

void EntityInit(entity_t *entity);
void EntitiesUpdate(list_t *entityList, float dt);
void EntitiesCreateParticles(list_t *entityList, vector_t position, int count,
                             float speed);
void EntitiesCreateExplosion(list_t *entityList, vector_t position);
void EntitiesCreateFloatingText(list_t *entityList, char *text,
                                vector_t position);

void EffectFlicker(entity_t *, float delta_time);

#endif // _ENTITY_H_