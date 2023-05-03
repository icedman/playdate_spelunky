#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "game.h"
#include "map.h"

typedef struct {
  scene_t scene;
} sceneTest_t;

void TestSceneInit(sceneTest_t *scene);

#endif // _TEST_SCENE_H_