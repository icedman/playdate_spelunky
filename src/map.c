#include "map.h"
#include "data.h"
#include "game.h"
#include "sprites.h"

static map_t map;

map_t *MapInstance() { return &map; }

entity_t *CreateEntityFromTile(char tile, int x, int y, map_t *map) {
  objectDefinition_t *def = NULL;

  switch (tile) {
  case PLAYER:
    def = ObjectDefinition(PLAYER);
    break;
  case WHIP:
    def = ObjectDefinition(WHIP);
    break;

  case '.': { // block/brick
    if (Rand(1, 10) == 1) {
      def = ObjectDefinition(BLOCK);
    } else {
      def = ObjectDefinition(BRICK);
    }
    break;
  }
  case 'b':   // brick smooth
  case '1': { // block/brick
    if (Rand(1, 10) == 1) {
      def = ObjectDefinition(BLOCK);
    } else {
      def = ObjectDefinition(BRICK);
    }
    break;
  }
  case '2': { // block/brick
    if (Rand(1, 2) == 1) {
      if (Rand(1, 10) == 1) {
        def = ObjectDefinition(BLOCK);
      } else {
        def = ObjectDefinition(BRICK);
      }
    }
    break;
  }
  case '4': { // push block
    def = ObjectDefinition(PUSH_BLOCK);
    break;
  }
  case 's': { // snake
    if (Rand(1, 10) == 1) {
      def = ObjectDefinition(SNAKE);
    } else if (Rand(1, 2) == 1) {
      def = ObjectDefinition(BRICK);
    }
    break;
  }
  case 'S': // snake
    def = ObjectDefinition(SNAKE);
    break;
  case '7': { // spikes
    if (Rand(1, 3) == 1) {
      def = ObjectDefinition(SPIKES);
    }
    break;
  }
  case 'L': // ladder
    def = ObjectDefinition(LADDER);
    break;
  case 'P': // ladder top
    def = ObjectDefinition(LADDER_TOP);
    break;
  case '9': // entrance/exit
    if (scrGetRoomX(x) == map->startRoomX &&
        scrGetRoomY(y) == map->startRoomY) {
      def = ObjectDefinition(ENTRANCE);
      map->startX = x;
      map->startY = y;
    } else {
      def = ObjectDefinition(EXIT);
    }
    break;
  default:
    printf("unimplemented tile %c\n", tile);
    break;
  }

  if (!def)
    return NULL;

  entity_t *e = (entity_t *)tx_malloc(sizeof(entity_t));
  EntityInit(e);
  VectorInit(&e->position, x * 32, y * 32, 1);

  e->type = def->type;
  e->onEnter = def->onEnter;
  e->onExit = def->onExit;
  e->onUpdate = def->onUpdate;
  e->spriteSheet = SpriteSheet(def->type, 0);

  RectInitXYWH(&e->collisionBounds, 0, 0, 32, 32);
  return e;
}

void MapCreateEntities(map_t *map, list_t *entities) {
  for (int y = 0; y < 8 * 4; y++) {
    for (int x = 0; x < 10 * 4; x++) {
      char tile = map->map[x + y * (10 * 4)];

      // walls
      if (x == 0 || y == 0 || x + 1 == 10 * 4 || y + 1 == 8 * 4) {
        tile = '1';
      }

      if (tile != '0') {
        entity_t *e = CreateEntityFromTile(tile, x, y, map);
        if (e) {
          node_t *n = NodeCreate(e, true);
          ListAppend(entities, n);
        }
      }
    }
  }

  // create player
  {
    // whip
    {
      entity_t *e = CreateEntityFromTile(WHIP, map->startX, map->startY, map);
      GameInstance()->whip = e;
      node_t *n = NodeCreate(e, true);
      ListAppend(entities, n);
    }
    // player1
    entity_t *e = CreateEntityFromTile(PLAYER, map->startX, map->startY, map);
    GameInstance()->player = e;
    node_t *n = NodeCreate(e, true);
    ListAppend(entities, n);

    // snake test
    {
      entity_t *e =
          CreateEntityFromTile('4', map->startX + 14, map->startY, map);
      node_t *n = NodeCreate(e, true);
      ListAppend(entities, n);
    }
  }
}

void MapInit(map_t *map) {
  memset(map, 0, sizeof(map_t));

  srcLevelGen(map);

  for (int yy = 0; yy < 4; yy++) {
    for (int xx = 0; xx < 4; xx++) {
      scrRoomGen1(map, xx * 10, yy * 8);
    }
  }
}
