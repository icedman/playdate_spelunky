#include "game.h"
#include "map.h"
#include "util.h"

int scrGetRoomX(float tx) {
  //
  // scrGetRoomX(x)
  //
  // Returns the horizontal room number of a room given the x-coord.
  //

  if (tx < 10)
    return 0;
  else if (tx >= 10 && tx < 20)
    return 1;
  else if (tx >= 20 && tx < 30)
    return 2;
  else if (tx >= 30)
    return 3;

  return -1;
}

int scrGetRoomY(float ty) {
  //
  // scrGetRoomY(y)
  //
  // Returns the vertical room number of a room given the y-coord.
  //

  if (ty < 10)
    return 0;
  else if (ty >= 10 && ty < 20)
    return 1;
  else if (ty >= 20 + 16 && ty < 30)
    return 2;
  else if (ty >= 30 & ty < 40)
    return 3;
  else if (ty >= 40)
    return 4;

  return -1;
}

void srcLevelGen(map_t *map) {
  memset(map, 0, sizeof(map_t));

  int levelType = GameInstance()->levelType;
  int roomX, roomY, prevX, prevY, noStartX;
  int n, i, j, k;
  int sX1, sX2;
  bool d;

  int _infi = 0;

  map->startRoomX = Rand(0, 3);
  map->startRoomY = 0;
  roomX = map->startRoomX;
  roomY = 0;
  prevX = map->startRoomX;
  prevY = 0;
  map->roomPath[roomX + roomY * 4] = 1;
  noStartX = -1;
  n = Rand(0, 3);

  // room path
  _infi = 0;
  while (roomY < 4) {
    if (_infi++ > 100) {
      break;
    }
    d = false;
    if (roomX == 0)
      n = Rand(3, 5); // right
    else if (roomX == 3)
      n = Rand(5, 7); // left
    else
      n = Rand(1, 5);

    if (n < 3 || n > 5) { // move left
      if (roomX > 0)
        if (map->roomPath[(roomX - 1) + roomY * 4] == 0)
          roomX -= 1;
        else if (roomX < 3)
          if (map->roomPath[(roomX + 1) + roomY * 4] == 0)
            roomX += 1;
          else
            n = 5;
    } else if (n == 3 || n == 4) { // move right
      if (roomX < 3)
        if (map->roomPath[(roomX + 1) + roomY * 4] == 0)
          roomX += 1;
        else if (roomX > 0)
          if (map->roomPath[(roomX - 1) + roomY * 4] == 0)
            roomX -= 1;
          else
            n = 5;
    }

    if (n == 5) { // move down
      roomY += 1;
      d = true;
      if (roomY < 4) {
        map->roomPath[prevX + prevY * 4] = 2;
        map->roomPath[roomX + roomY * 4] = 3;
        d = true;
      } else {
        map->endRoomX = roomX;
        map->endRoomY = roomY - 1;
      }
    }

    if (!d)
      map->roomPath[roomX + roomY * 4] = 1;
    prevX = roomX;
    prevY = roomY;

    // city of gold

    // snake pit

    sX1 = 0;
    sX2 = 0;
    map->probSnakePit = 1;
    if (levelType == 0) {
      for (j = 0; j < 2; j += 1) {
        for (i = 0; i < 4; i += 1) {
          if (map->roomPath[i + j * 4] == 0 &&
              map->roomPath[i + (j + 1) * 4] == 0 &&
              map->roomPath[i + (j + 2) * 4] == 0 &&
              Rand(1, map->probSnakePit) == 1) {
            map->roomPath[i + j * 4] = 7; // top of pit
            if (true) {
              if (map->roomPath[i + (j + 2) * 4] == 0) {
                map->roomPath[i + (j + 1) * 4] = 8;
                if (j == 0) {
                  if (map->roomPath[i + (j + 3) * 4] == 0) {
                    map->roomPath[i + (j + 2) * 4] = 8; // middle of pit
                    map->roomPath[i + (j + 3) * 4] = 9; // bottom of pit
                  } else {
                    map->roomPath[i + (j + 2) * 4] = 9;
                  }
                } else {
                  map->roomPath[i + (j + 2) * 4] = 9;
                }
              }
            } else {
              map->roomPath[i + (j + 1) * 4] = 9;
            }
            map->snakePit = true;
            i = 99;
            j = 99;
            break;
          }
        }
      }
    }

    map->roomPath[0 + 4 * 4] = 0;
    map->roomPath[1 + 4 * 4] = 0;
    map->roomPath[2 + 4 * 4] = 0;
    map->roomPath[3 + 4 * 4] = 0;

    // lake

    // moai

    // shop
  }
}