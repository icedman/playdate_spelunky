#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector.h>

#include "context.h"
#include "data.h"
#include "entity.h"
#include "fastRandom.h"
#include "font.h"
#include "game.h"
#include "matrix.h"
#include "menu.h"
#include "polygon.h"
#include "renderer.h"
#include "tests.h"
#include "util.h"
#include "vector.h"

void SnakeRegister(int type);

SDL_Window *window;

int width = 400 * 2;
int height = 240 * 2;

int spriteWidth = 32;
int spriteHeight = 32;
float offsetX = 0;
float offsetY = 0;

void *_loadImage(context_t *context, char *path) {
  SDL_Renderer *renderer = (SDL_Renderer *)context->renderer;
  SDL_Surface *temp = IMG_Load(path);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);
  if (!texture) {
    printf("unable to load %s\n", path);
  }
  printf("loaded %s\n", path);
  return texture;
}

void _freeImage(void *context, void *image) {}

void _drawImage(context_t *context, void *image, vector_t pos, bool flipped) {
  vector_t vt = VectorTransformed(&pos, context->matrixStack.matrix);
  SDL_Renderer *renderer = (SDL_Renderer *)context->renderer;
  int sw = spriteWidth;
  int sh = spriteHeight;
  SDL_QueryTexture(image, NULL, NULL, &sw, &sh);
  SDL_Rect dest;
  dest.x = vt.x + 32 / 2 - sw / 2;
  dest.y = vt.y + 32 / 2 - sh / 2;
  dest.w = (sw * 2 + 32) / 3;
  dest.h = (sh * 2 + 32) / 3;
  // SDL_RenderCopy(renderer, image, NULL, &dest);
  SDL_Point center;
  center.x = sw / 2;
  center.y = sh / 2;
  SDL_RenderCopyEx(renderer, image, NULL, &dest, 0, &center,
                   flipped ? SDL_FLIP_HORIZONTAL : 0);
}

void _drawLine(void *ctx, vector_t v1, vector_t v2) {
  context_t *context = (context_t *)ctx;
  SDL_Renderer *renderer = (SDL_Renderer *)context->renderer;
  float alpha = context->state->dark ? 0.5 : 1;
  SDL_SetRenderDrawColor(renderer, context->state->r * alpha,
                         context->state->g * alpha, context->state->b * alpha,
                         255);
  // printf(">%d\n", context->state->r);
  SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
}

int main(int argc, char **argv) {
  RandomSeed(100);
  setImageFunctions(_loadImage, _freeImage, _drawImage);

  FontInit();

  game_t game;
  GameInit(&game);

  list_t entities;
  ListInit(&entities);
  game.entities = &entities;

  sceneTest_t testScene;
  TestSceneInit(&testScene);
  sceneMenu_t menuScene;
  MenuSceneInit(&menuScene);
  game.menu = &menuScene;
  GameEnterMenu(&game);

  game.scene = &testScene;

  int frames = 0;
  context_t context;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  SDL_EnableScreenSaver();
  SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  atexit(SDL_Quit);

  // SDL_DisplayMode dm;
  // SDL_GetCurrentDisplayMode(0, &dm);

  ContextInit(&context, width, height);

  window = SDL_CreateWindow(
      "", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);

  SDL_SetWindowTitle(window, "SDL");
  SDL_ShowWindow(window);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  context.renderer = renderer;
  context.drawLine = _drawLine;

  rect_t *tr = 0;
  vector_t tv;
  int trIdx = -1;

  int lastTicks = SDL_GetTicks();
  while (!game.done) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        game.done = true;
        break;
      case SDL_KEYUP:
      case SDL_KEYDOWN: {
        int down = e.type == SDL_KEYDOWN;
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          game.keys[ESCAPE] = down;
          break;
        case SDLK_LEFT:
          game.keys[LEFT] = down;
          break;
        case SDLK_RIGHT:
          game.keys[RIGHT] = down;
          break;
        case SDLK_UP:
          game.keys[UP] = down;
          break;
        case SDLK_DOWN:
          game.keys[DOWN] = down;
          break;
        case SDLK_SPACE:
          game.keys[SPACE] = down;
          break;
        case SDLK_a:
          game.keys[FIRE1] = down;
          break;
        case SDLK_s:
          game.keys[FIRE2] = down;
          break;
        }
      }
      }
    }

    int ticks = SDL_GetTicks();
    float dt = ticks - lastTicks;
    if (dt < 12)
      continue;
    lastTicks = ticks;
    if (dt > 64) {
      dt = 64;
    }

    GameUpdate(&game, dt / 1000);
    if (game.done)
      break;

    // camera
    float newOffsetX = (width / 2 - game.player->position.x);
    float newOffsetY = (height / 2 - game.player->position.y);
    if (offsetX == 0 && offsetY == 0) {
      offsetX = newOffsetX;
      offsetY = newOffsetY;
    } else {
      offsetX *= 4;
      offsetX += newOffsetX;
      offsetX /= 5;
      offsetY *= 4;
      offsetY += newOffsetY;
      offsetY /= 5;
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    ContextSave(&context);
    ContextTranslate(&context, offsetX, offsetY);
    GameRender(&game, &context);
    ContextRestore(&context);

    SDL_RenderPresent(renderer);
  }

  GameDestroy(&game);
  ListDestroy(&entities);

  tx_stats();
  printf("bye\n");

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}
