#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "context.h"
#include "sprites.h"
#include "util.h"
#include "vector.h"

typedef enum {
  EMPTY_SPACE = 0,
  // blocks
  START_BLOCKS,
  PUSH_BLOCK,
  ALTAR_LEFT,
  ALTAR_RIGHT,
  SAC_ALTAR_LEFT,
  SAC_ALTAR_RIGHT,
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
  ENTRANCE,
  EXIT,
  END_BLOCKS,
  // traps
  START_TRAPS,
  GIANT_TIKI_HEAD,
  SPIKES,
  SPIKES_BLOOD,
  END_TRAPS,
  // characters
  START_CHARACTERS,
  PLAYER,
  DAMSEL,
  END_CHARACTERS,
  // enemies
  START_ENEMIES,
  SNAKE,
  SPIDER,
  SPIDER_HANG,
  BAT,
  END_ENEMIES,
  // items
  START_ITEMS,
  WHIP,
  END_ITEMS,
  // cave
  START_CAVE,
  GOLD_IDOL,
  END_CAVE,
  TYPE_END,
} entityType_t;

typedef enum {
  IDLE = 0,
  WALKING,
  ATTACKING,
  JUMPING,
  HANGING,
  FLYING,
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
  entityType_t type;
  entityState_t state;
  vector_t position;
  vector_t direction;
  vector_t acceleration;
  vector_t velocity;
  float speed;
  float radius;
  float life;
  float ticks;
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
  float pushTime;
  float jumpStart;
  vector_t anchor;

  spriteSheet_t *spriteSheet;
  float frameSpeed;
  float frame;
  bool flipSprite;

  rect_t collisionBounds;
  bool renderCollisionBounds;

  // hints
  struct entity_t *above;
  struct entity_t *below;
  struct entity_t *left;
  struct entity_t *right;

  union {
    struct entity_t *collisions[4];
    struct {
      struct entity_t *leftCollision;
      struct entity_t *rightCollision;
      struct entity_t *topCollision;
      struct entity_t *bottomCollision;
    };
  };

  union {
    struct entity_t *col[4];
    struct {
      struct entity_t *lt;
      struct entity_t *rt;
      struct entity_t *lb;
      struct entity_t *rb;
    };
  };

  struct entity_t *push;

  int hp;
} entity_t;

void EntityInit(entity_t *entity);
void EntityUpdate(entity_t *e, float dt);
void EntitiesUpdate(list_t *entityList, float dt);
void EntitiesCreateParticles(list_t *entityList, vector_t position, int count,
                             float speed);
void EntitiesCreateExplosion(list_t *entityList, vector_t position);
void EntitiesCreateFloatingText(list_t *entityList, char *text,
                                vector_t position);

void EffectFlicker(entity_t *, float delta_time);

#endif // _ENTITY_H_