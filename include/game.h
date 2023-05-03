#ifndef _GAME_H_
#define _GAME_H_

#include "context.h"
#include "entity.h"
#include "util.h"
#include "vector.h"

typedef enum {
  UNKNOWN_KEY = 0,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  FIRE1,
  FIRE2,
  ESCAPE,
  SPACE,
  CRANK_CW,
  CRANK_CCW,
  CRANK,
  KEYS_END
} KeysType;

typedef struct {
  void (*onEnter)(struct game_t *gm, struct scene_t *scn);
  void (*onExit)(struct game_t *gm, struct scene_t *scn);
  void (*onUpdate)(struct game_t *gm, struct scene_t *scn, float delta_time);
  void (*onRender)(struct game_t *gm, struct scene_t *scn, context_t *context);
} scene_t;

void SceneInit(scene_t *scene);

typedef struct {
  KeysType keysPressed[KEYS_END];
  KeysType keysReleased[KEYS_END];
  KeysType keys[KEYS_END];
  KeysType previousKeys[KEYS_END];
  bool gamePad;
  int crank;

  scene_t *scene;
  scene_t *previousScene;

  list_t *entities;
  scene_t *menu;
  entity_t *player;

  int currentLevel;
  float countDown;
  float ticks;
  float endTicks;
  bool done;
  bool paused
} game_t;

void GameInit(game_t *game);
void GameDestroy(game_t *game);
void GameUpdate(game_t *game, float delta_time);
void GameRender(game_t *game, context_t *context);
void GameEnterMenu(game_t *game);

game_t *GameInstance();

#endif //  _GAME_H_