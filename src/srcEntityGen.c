// #include "game.h"
// #include "map.h"
// #include "data.h"

void srcEntityGen(map_t *map, list_t *entities) {
  game_t *gm = GameInstance();

  int roomHeight = (8 * 4) * 32;

  bool lockedChest = false;
  bool key = false;
  int lockedChestChance = 8;

  int newNodesMax = 512;
  node_t *newNodes[newNodesMax];
  int newNodeIdx = 0;

  if (gm->levelType == 0) {
    // gm->giantSpider = false;
    // gm->genGiantSpider = false;
    // if (Rand(1, 6) == 1)
    //   gm->genGiantSpider = true;

    node_t *n = entities->first;
    while (n && newNodeIdx < newNodesMax) {
      entity_t *e = n->data;
      n = n->next;

      float x = e->position.x;
      float y = e->position.y;

      if (y == 0)
        continue;
      if (!IsSolidEntity(e))
        continue;

      // printf("%f %f\n",x, y);

      if (scrGetRoomX(x) == map->startRoomX &&
          scrGetRoomY(y - 32) == map->startRoomY) {
        continue;
      }

      vector_t v = e->position;
      v.x += 16;
      v.y -= 16;
      entity_t *up = EntityAtPoint(v, entities, NULL);

      v = e->position;
      v.x += 16;
      v.y += (16 + 32);
      entity_t *down = EntityAtPoint(v, entities, NULL);

      v = e->position;
      v.x -= 16;
      v.y += 16;
      entity_t *left = EntityAtPoint(v, entities, NULL);

      v = e->position;
      v.x += (16 + 32);
      v.y += 16;
      entity_t *right = EntityAtPoint(v, entities, NULL);

      if (!down && y < roomHeight - 64) {
        // giant spider
        // lamp
        // scarab
        if (Rand(1, 60) == 1) {
          entity_t *ne = CreateEntityFromTile(BAT, x / 32, y / 32 + 1, map);
          node_t *nn = NodeCreate(ne, true);
          ListAppend(entities, nn);
          printf("bat!\n");
        } else if (rand(1, 80) == 1) {
          // instance_create (x, y + 16, ObjType.oSpiderHang);
        }
      }

      if (!up) {
        if (Rand(1, 60) == 1) {
          entity_t *ne = CreateEntityFromTile(SNAKE, x / 32, y / 32 - 1, map);
          node_t *nn = NodeCreate(ne, true);
          ListAppend(entities, nn);
        } else if (Rand(1, 800) == 1) {
          // instance_create (x, y - 16, ObjType.oCaveman);
        }
      }
    }
  }
}
