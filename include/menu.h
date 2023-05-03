#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "game.h"

typedef struct {
  scene_t scene;
} sceneMenu_t;

void MenuSceneInit(sceneMenu_t *scene);

#endif // _MENU_SCENE_H_