#include "menu.h"
#include "renderer.h"

void menuEnter(game_t *gm, scene_t *scn) {
  sceneMenu_t *menu = (sceneMenu_t *)scn;
}

void menuUpdate(game_t *gm, scene_t *scn, float delta_time) {
  if (gm->keysPressed[ESCAPE]) {
    gm->done = true;
    return;
  }
  if (gm->keysPressed[SPACE] || gm->keysPressed[FIRE1]) {
    return;
  }
}

void menuRender(game_t *gm, scene_t *scn, context_t *context) {
  sceneMenu_t *menu = (sceneMenu_t *)scn;
  context->state->dark = true;
}

void MenuSceneInit(sceneMenu_t *scene) {
  SceneInit(scene);
  scene->scene.onEnter = menuEnter;
  scene->scene.onUpdate = menuUpdate;
  scene->scene.onRender = menuRender;
}