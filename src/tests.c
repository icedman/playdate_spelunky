#include "tests.h"
#include "game.h"
#include "map.h"
#include "renderer.h"
#include "util.h"

#include <stdio.h>

// base on Spelunky Room Generation by Derek Yu && Mossmouth, LLC
// <http://spelunkyworld.com/>

bool _buildLevel(game_t *gm, scene_t *scn) {
  GameDestroy(gm);
  ListDestroy(gm->entities);

  map_t *map = MapInstance();
  MapInit((void*)map);
  MapCreateEntities(map, gm->entities);
  MapSetupWalls(map, gm->entities);

  printf("s:%d,%d e:%d,%d\n", map->startX, map->startY, map->exitX, map->exitY);
  return (map->startX != 0 && map->startY != 0 && map->exitX != 0 &&
          map->exitY != 0);
}

void testEnter(game_t *gm, scene_t *scn) {
  for (int i = 0; i < 20; i++) {
    if (_buildLevel(gm, scn))
      break;
    printf("retry %d\n", (i + 1));
  }
}

void testUpdate(game_t *gm, scene_t *scn, float delta_time) {
  if (gm->keysPressed[ESCAPE]) {
    gm->done = true;
    return;
  }

  if (gm->keysPressed[SPACE]) {
    testEnter(gm, scn);
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
  SceneInit((void*)scene);
  scene->scene.onEnter = (void*)testEnter;
  scene->scene.onUpdate = (void*)testUpdate;
  scene->scene.onRender = (void*)testRender;
}