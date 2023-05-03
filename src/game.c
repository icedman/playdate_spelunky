#include "game.h"

static game_t *gameInstance = NULL;

void onEnter(struct game_t *, struct scene_t *scn) {}

void onExit(struct game_t *, struct scene_t *scn) {}

void onUpdate(struct game_t *, struct scene_t *scn, float delta_time) {}

void onRender(struct game_t *, struct scene_t *scn, context_t *context) {}

void SceneInit(scene_t *scn) {
  memset(scn, 0, sizeof(scene_t));
  scn->onEnter = onEnter;
  scn->onExit = onExit;
  scn->onUpdate = onUpdate;
  scn->onRender = onRender;
}

void GameInit(game_t *gm) {
  memset(gm, 0, sizeof(game_t));
  gameInstance = gm;
}

game_t *GameInstance() { return gameInstance; }

void GameDestroy(game_t *gm) {}

void GameUpdate(game_t *gm, float delta_time) {
  gm->ticks += delta_time;
  if (gm->endTicks > 0) {
    gm->endTicks += delta_time;
  }

  // take inputs
  memset(&gm->keysPressed, 0, sizeof(int) * KEYS_END);
  memset(&gm->keysReleased, 0, sizeof(int) * KEYS_END);
  for (int i = 0; i < KEYS_END; i++) {
    if (!gm->previousKeys[i] && gm->keys[i]) {
      gm->keysPressed[i] = 1;
    }
    if (gm->previousKeys[i] && !gm->keys[i]) {
      gm->keysReleased[i] = 1;
    }
  }
  memcpy(&gm->previousKeys, &gm->keys, sizeof(int) * KEYS_END);

  if (gm->scene) {
    if (gm->previousScene != gm->scene) {
      if (gm->previousScene) {
        gm->previousScene->onExit(gm, gm->scene);
      }
      gm->scene->onEnter(gm, gm->scene);
      gm->previousScene = gm->scene;
    }

    gm->scene->onUpdate(gm, gm->scene, delta_time);
  }
}

void GameRender(game_t *gm, context_t *context) {
  if (gm->scene) {
    gm->scene->onRender(gm, gm->scene, context);
  }
}

void GameEnterMenu(game_t *game) {
  game->scene = game->menu;
  GameUpdate(game, 0);
}

void GameEnterRace(game_t *game) { GameUpdate(game, 0); }
