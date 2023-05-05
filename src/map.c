#include "map.h"
#include "data.h"
#include "game.h"
#include "sprites.h"

static map_t map;

map_t *MapInstance() { return &map; }

entity_t *CreateEntityFromTile(char tile, float x, float y, map_t *map) {
  objectDefinition_t *def = NULL;

  if (tile == 0) {
    return NULL;
  }

  switch (tile) {
  // altar
  case 'A':
    def = ObjectDefinition(ALTAR_LEFT);
    break;
  // sacrifice altar
  case 'x':
    def = ObjectDefinition(SAC_ALTAR_LEFT);
    break;
  // idol
  case 'I':
    def = ObjectDefinition(GOLD_IDOL);
    x += 0.5;
    break;
  // giant tiki head
  case 'B':
    def = ObjectDefinition(GIANT_TIKI_HEAD);
    break;

    // // wanted sign
    // case 'W':
    //   break;
    // // lamp/lampRed
    // case 'l':
    //   break;
    // // shopKeeper
    // case 'K':
    //   break;
    // // shop sign
    // case 'k':
    //   break;
    // // shop item
    // case 'i':
    //   break;
    // // dice
    // case 'd':
    //   break;
    // // craps
    // case 'Q':
    //   break;
    // // generate item in diceHouse
    // case 'q':
    //   break;
    // // Damsel
    // case 'D':
    //   break;
    // // RubyBig
    // case 'T':
    //   break;
    // // Mattock
    // case 'M':
    //   break;
    // // brickSmooth
    // case 'b':
    //   break;
    // // ice block
    // case '+':
    //   break;

  case '.': { // block/brick
    if (Rand(1, 10) == 1) {
      def = ObjectDefinition(BLOCK);
    } else {
      def = ObjectDefinition(BRICK);
    }
    break;
  }
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
    if (map->startX == 0 && map->startY == 0 &&
        scrGetRoomX(x) == map->startRoomX &&
        scrGetRoomY(y) == map->startRoomY) {
      def = ObjectDefinition(ENTRANCE);
      map->startX = x;
      map->startY = y;
    } else {
      def = ObjectDefinition(EXIT);
      map->exitX = x;
      map->exitY = y;
    }
    // printf(">> entrance:%d,%d exit:%d,%d\n", map->startX, map->startY,
    // map->exitX, map->exitY);
    break;
  default:
    def = ObjectDefinition(tile);
    if (!def) {
      printf("unimplemented tile %c %d\n", tile, tile);
    }
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

// segmentation fault
#include "srcEntityGen.c"

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

          if (e->type == ALTAR_LEFT) {
            entity_t *e = CreateEntityFromTile(ALTAR_RIGHT, x + 1, y, map);
            if (e) {
              node_t *n = NodeCreate(e, true);
              ListAppend(entities, n);
            }
          }
          if (e->type == SAC_ALTAR_LEFT) {
            entity_t *e = CreateEntityFromTile(SAC_ALTAR_RIGHT, x + 1, y, map);
            if (e) {
              node_t *n = NodeCreate(e, true);
              ListAppend(entities, n);
            }
          }
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
          CreateEntityFromTile(BAT, map->startX + 14, map->startY, map);
      node_t *n = NodeCreate(e, true);
      ListAppend(entities, n);
    }
  }

  // entities and treasures
  srcEntityGen(map, entities);
}

void MapSetupWalls(map_t *map, list_t *entities) {
  node_t *n = entities->first;
  while (n) {
    entity_t *e = n->data;
    n = n->next;
    if (e->type != BRICK) {
      continue;
    }
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    vector_t v = e->position;
    v.x += 16;
    v.y -= 16;
    up = EntityAtPoint(v, entities, IsBrickOrBlock) != NULL;

    v = e->position;
    v.x += 16;
    v.y += (16 + 32);
    down = EntityAtPoint(v, entities, IsBrickOrBlock) != NULL;

    v = e->position;
    v.x -= 16;
    v.y += 16;
    left = EntityAtPoint(v, entities, IsBrickOrBlock) != NULL;

    v = e->position;
    v.x += (16 + 32);
    v.y += 16;
    right = EntityAtPoint(v, entities, IsBrickOrBlock) != NULL;

    if (!up) {
      e->spriteSheet = SpriteSheet(CAVE_UP, 0);
    }

    if (!down) {
      if (!up) {
        e->spriteSheet = SpriteSheet(CAVE_UP_2, 0);
      } else {
        e->spriteSheet = SpriteSheet(BRICK_DOWN, 0);
      }
    }
  }
}

void MapInit(map_t *map) {
  game_t *gm = GameInstance();
  gm->currentLevel = 3;
  gm->levelType = 0;
  if (gm->currentLevel > 4 && gm->currentLevel < 9)
    gm->levelType = 1;
  if (gm->currentLevel > 8 && gm->currentLevel < 13)
    gm->levelType = 2;
  if (gm->currentLevel > 12 && gm->currentLevel < 16)
    gm->levelType = 3;
  if (gm->currentLevel == 16)
    gm->levelType = 4;

  // if (gm->currentLevel <= 1 ||
  //     gm->currentLevel == 5 ||
  //     gm->currentLevel == 9 ||
  //     gm->currentLevel == 13) {
  //   gm->hadDarkLevel = false;
  // }

  srcLevelGen(map);
  for (int yy = 0; yy < 4; yy++) {
    for (int xx = 0; xx < 4; xx++) {
      scrRoomGen1(map, xx * 10, yy * 8);
    }
  }
}
