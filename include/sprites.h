#ifndef _SPRITES_H_
#define _SPRITES_H_

typedef struct {
  int id;
  int frames;
  char *path;
  int w;
  int h;
  void *images[16];
} spriteSheet_t;

void SpritesInit();
spriteSheet_t *SpriteSheet(int id, int offset);

#endif // _SPRITES_H_