#include "tests.h"
#include "game.h"
#include "map.h"
#include "renderer.h"
#include "util.h"

// base on Spelunky Room Generation by Derek Yu && Mossmouth, LLC
// <http://spelunkyworld.com/>

void testEnter(game_t *gm, scene_t *scn) {
  GameDestroy(gm);
  ListDestroy(gm->entities);
  MapInit(MapInstance());
  MapCreateEntities(MapInstance(), gm->entities);
}

void testUpdate(game_t *gm, scene_t *scn, float delta_time) {
  if (gm->keysPressed[ESCAPE]) {
    gm->done = true;
    return;
  }

  if (gm->keysPressed[FIRE1]) {
    // GameDestroy(gm);
    // ListDestroy(gm->entities);
    // MapInit(MapInstance());
    // MapCreateEntities(MapInstance(), gm->entities);
  }

  if (gm->keys[LEFT]) {
  }

  if (gm->keys[RIGHT]) {
  }

  EntitiesUpdate(gm->entities, delta_time);
}

void testRender(game_t *gm, scene_t *scn, context_t *context) {
  int width = context->width;
  int height = context->height;
  ContextSave(context);

  RenderEntities(gm->entities, context);

  ContextRestore(context);
}

void TestSceneInit(sceneTest_t *scene) {
  SceneInit(scene);
  scene->scene.onEnter = testEnter;
  scene->scene.onUpdate = testUpdate;
  scene->scene.onRender = testRender;
}