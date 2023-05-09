//
//  main.c
//  Extension
//
//

// find . -maxdepth 1 -iname "*.png" | xargs -L1 -I{} convert -resize 32x32 "{}"
// "{}"

#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "context.h"
#include "data.h"
#include "entity.h"
#include "font.h"
#include "game.h"
#include "map.h"
#include "matrix.h"
#include "menu.h"
#include "renderer.h"
#include "tests.h"
#include "vector.h"

#define PATTERN_IMPLEMENTATION
#include "pattern.h"

static int update(void *userdata);
const char *fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
LCDFont *font = NULL;

static PlaydateAPI *pd = NULL;

void setPDPtr(PlaydateAPI *p) { pd = p; }

LCDBitmap *loadImageAtPath(const char *path) {
  const char *outErr = NULL;
  LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
  if (outErr != NULL) {
    pd->system->logToConsole("Error loading image at path '%s': %s", path,
                             outErr);
  }
  printf("load %s\n", path);
  return img;
}

int width = 400;
int height = 240;

int tilesWidth = 26;
int tilesHeight = 16;

int spriteWidth = 32;
int spriteHeight = 32;

context_t context;

sceneMenu_t menuScene;
sceneMenu_t testScene;
game_t game;
list_t entities;

void _drawLine(void *ctx, vector_t v1, vector_t v2) {
  context_t *context = (context_t *)ctx;
  PlaydateAPI *pd = (PlaydateAPI *)context->renderer;
  int x1 = (int)v1.x;
  int y1 = (int)v1.y;
  int x2 = (int)v2.x;
  int y2 = (int)v2.y;
  int width = (int)context->state->stroke;
  uint8_t *kColor = kColorWhite;
  if (context->state->g == 155) {
    kColor = get_pattern(gray);
  }
  if (context->state->g == 100) {
    kColor = get_pattern(gray_3);
  }
  if (context->state->dark) {
    kColor = get_pattern(darkgray_2);
  }
  pd->graphics->drawLine(x1, y1, x2, y2, width, kColor);
}

void *_loadImage(context_t *context, char *path) {
  return loadImageAtPath(path);
}

void _freeImage(context_t *context, void *image) {
  pd->graphics->freeBitmap(image);
}

void _drawImage(context_t *context, void *image, vector_t pos, bool flipped) {
  vector_t vt = VectorTransformed(&pos, context->matrixStack.matrix);
  // pd->graphics->setDrawOffset(offsetX, offsetY);

  int sw = 32;
  int sh = 32;
  pd->graphics->getBitmapData(image, &sw, &sh, NULL, NULL, NULL);
  float tw = ((sw * 3) + 32) / 4;
  float sz = (float)tw / sw;
  vt.x += 32 / 2 - sw / 2;
  vt.y += 32 / 2 - sh / 2;

  pd->graphics->drawScaledBitmap(image, vt.x, vt.y, flipped ? -sz : sz, sz);
  // pd->graphics->drawBitmap(image, vt.x, vt.y,
  //                          flipped ? kBitmapFlippedX : kBitmapUnflipped);
}

#ifdef _WINDLL
__declspec(dllexport)
#endif
    int eventHandler(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg) {
  (void)arg; // arg is currently only used for event = kEventKeyPressed

  if (event == kEventInit) {
    setPDPtr(pd);
    setImageFunctions(_loadImage, _freeImage, _drawImage);

    RandomSeed(100);

    ContextInit(&context, width, height);
    FontInit();
    SpritesInit();

    GameInit(&game);
    ListInit(&entities);
    game.entities = &entities;

    // RaceSceneInit(&gameScene);
    MenuSceneInit(&menuScene);
    TestSceneInit(&testScene);

    game.gamePad = true;
    game.menu = &menuScene;
    // game.race = &gameScene;
    // GameEnterMenu(&game);
    // GameEnterRace(&game);

    game.scene = &testScene;

    const char *err;
    font = pd->graphics->loadFont(fontpath, &err);

    if (font == NULL)
      pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__,
                        fontpath, err);

    // Note: If you set an update callback in the kEventInit handler, the system
    // assumes the game is pure C and doesn't run any Lua code in the game
    pd->system->setUpdateCallback(update, pd);
  }

  return 0;
}

static float offsetX = 0;
static float offsetY = 0;

static int update(void *userdata) {
  PlaydateAPI *pd = userdata;
  context.renderer = pd;
  context.drawLine = _drawLine;

  // float dt = pd->system->getElapsedTime();
  // pd->system->resetElapsedTime();

  PDButtons current;
  pd->system->getButtonState(&current, NULL, NULL);

  game.keys[UP] = (current & kButtonUp);
  game.keys[DOWN] = (current & kButtonDown);
  game.keys[LEFT] = (current & kButtonLeft);
  game.keys[RIGHT] = (current & kButtonRight);
  game.keys[FIRE1] = (current & kButtonA);
  game.keys[FIRE2] = (current & kButtonB);
  game.keys[CRANK] = pd->system->getCrankAngle();

  int pre = 8;
  float dt = 0.03 / pre;
  for (int i = 0; i < pre; i++) {
    GameUpdate(&game, dt);
  }

  // camera
  float newOffsetX = (width / 2 - game.player->position.x);
  float newOffsetY = (height / 2 - game.player->position.y);
  if (offsetX == 0 && offsetY == 0) {
    offsetX = newOffsetX;
    offsetY = newOffsetY;
  } else {
    int lerp = game.player->state == FALLING ? 8 : 20;
    float dx = offsetX - newOffsetX;
    float dy = offsetY - newOffsetY;
    int snapDistance = 4;
    if (ABS(dx) < snapDistance) {
      offsetX = newOffsetX;
    } else {
      offsetX *= (lerp - 1);
      offsetX += newOffsetX;
      offsetX /= lerp;
    }
    if (ABS(dy) < snapDistance) {
      offsetY = newOffsetY;
    } else {
      offsetY *= (lerp - 1);
      offsetY += newOffsetY;
      offsetY /= lerp;
    }
  }

  if (offsetX > 0) {
    offsetX = 0;
  }
  if (offsetY > 0) {
    offsetY = 0;
  }
  if (offsetX + (spriteWidth * 10 * 4) < width) {
    offsetX = width - (spriteWidth * 10 * 4);
  }
  if (offsetY + (spriteHeight * 8 * 4) < height) {
    offsetY = height - (spriteHeight * 8 * 4);
  }

  if (game.keysPressed[FIRE1]) {
    pd->sprite->removeAllSprites();
  }

  pd->graphics->clear(kColorBlack);
  pd->graphics->setBackgroundColor(kColorBlack);
  pd->graphics->setFont(font);

  ContextSave(&context);
  ContextTranslate(&context, offsetX, offsetY);
  GameRender(&game, &context);

  ContextRestore(&context);
  pd->system->drawFPS(0, 0);

  return 1;
}
