#ifndef _MAP_H_
#define _MAP_H_

#include "entity.h"
#include "stdtypes.h"

typedef struct {
  int currentLevel;
  int levelType;
  int startRoomX;
  int startRoomY;
  int startX;
  int startY;
  int endRoomX;
  int endRoomY;
  int exitX;
  int exitY;
  int roomPath[16];
  bool damsel;
  bool altar;
  bool idol;
  bool snakePit;
  int probSnakePit;
  char map[10 * 8 * 4 * 4];
  // map_gfx_t gfx[10 * 8 * 4 * 4];
  // map_gfx_t borderTB[(10 * 4) + 2];
  // map_gfx_t borderLR[(8 * 4) + 2];
} map_t;

map_t *MapInstance();
void MapCreateEntities(map_t *map, list_t *entities);

int scrGetRoomY(float ty);
int scrGetRoomX(float tx);
void srcLevelGen(map_t *map);
void srcRoomGen1(map_t *map);
void scrRoomGen2(map_t *map, int x, int y);
void scrRoomGen3(map_t *map, int x, int y);

#endif // _MAP_H_