#include "sprites.h"
#include "data.h"

#define SHEET_OFFSET 100
// clang-format off
static spriteSheet_t sprite_defs[] = {
    {EMPTY_SPACE, 0, "", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET, 1, "sprites/character/sStandLeft.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + WALKING, 6, "sprites/character/sRunLeft_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + DUCKING, 1, "sprites/character/sDuckLeft.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + CRAWLING, 10, "sprites/character/sCrawlLeft_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + PUSHING, 7, "sprites/character/sPushLeft_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + FALLING, 1, "sprites/character/sFallLeft.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + HANGING, 1, "sprites/character/sHangLeft.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + JUMPING, 1, "sprites/character/sJumpLeft.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + CLIMBING, 6, "sprites/character/sClimbUp_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + CLIMBING_ROPE, 12, "sprites/character/sClimbUp2_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + CLIMBING_VINE, 12, "sprites/character/sClimbUp3_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + ATTACKING, 11, "sprites/character/sAttackLeft_%d.png", 0, 0, {NULL}},
    {PLAYER * SHEET_OFFSET + WHOA, 7, "sprites/character/sWhoaLeft_%d.png", 0, 0, {NULL}},
    {WHIP * SHEET_OFFSET + 0, 1, "sprites/items/sWhipPreR.png", 0, 0, {NULL}},
    {WHIP * SHEET_OFFSET + 1, 1, "sprites/items/sWhipRight.png", 0, 0, {NULL}},
    {PUSH_BLOCK * SHEET_OFFSET, 1, "sprites/blocks/sBlock.png", 0, 0, {NULL}},
    {ALTAR_LEFT * SHEET_OFFSET, 1, "sprites/blocks/sAltarLeft.png", 0, 0, {NULL}},
    {ALTAR_RIGHT * SHEET_OFFSET, 1, "sprites/blocks/sAltarRight.png", 0, 0, {NULL}},
    {SAC_ALTAR_LEFT * SHEET_OFFSET, 1, "sprites/blocks/sSacAltarLeft.png", 0, 0, {NULL}},
    {SAC_ALTAR_RIGHT * SHEET_OFFSET, 1, "sprites/blocks/sSacAltarRight.png", 0, 0, {NULL}},
    {GOLD_IDOL * SHEET_OFFSET, 1, "sprites/cave/sGoldIdol.png", 0, 0, {NULL}},
    {BLOCK * SHEET_OFFSET, 1, "sprites/blocks/sBlock.png", 0, 0, {NULL}},
    {BRICK * SHEET_OFFSET, 1, "sprites/blocks/sBrick.png", 0, 0, {NULL}},
    {BRICK_2 * SHEET_OFFSET, 1, "sprites/blocks/sBrick2.png", 0, 0, {NULL}},
    {LADDER * SHEET_OFFSET, 1, "sprites/blocks/sLadder.png", 0, 0, {NULL}},
    {LADDER_TOP * SHEET_OFFSET, 1, "sprites/blocks/sLadderTop.png", 0, 0, {NULL}},
    {ENTRANCE * SHEET_OFFSET, 1, "sprites/blocks/sEntrance.png", 0, 0, {NULL}},
    {EXIT * SHEET_OFFSET, 1, "sprites/blocks/sExit.png", 0, 0, {NULL}},
    {SNAKE * SHEET_OFFSET, 1, "sprites/enemies/sSnakeLeft.png", 0, 0, {NULL}},
    {SNAKE * SHEET_OFFSET + WALKING, 4, "sprites/enemies/sSnakeWalkL_%d.png", 0, 0, {NULL}},
    {BAT * SHEET_OFFSET, 3, "sprites/enemies/sBatLeft_%d.png", 0, 0, {NULL}},
    {BAT * SHEET_OFFSET + HANGING, 1, "sprites/enemies/sBatHang.png", 0, 0, {NULL}},
    {SPIDER * SHEET_OFFSET, 4, "sprites/enemies/sSpider_%d.png", 0, 0, {NULL}},
    {SPIDER_HANG * SHEET_OFFSET, 1, "sprites/enemies/sSpiderHang.png", 0, 0, {NULL}},
    {SPIDER_HANG * SHEET_OFFSET + JUMPING, 9, "sprites/enemies/sSpiderFlip_%d.png", 0, 0, {NULL}},
    {SPIKES * SHEET_OFFSET, 1, "sprites/traps/sSpikes.png", 0, 0, {NULL}},
    {GIANT_TIKI_HEAD * SHEET_OFFSET, 1, "sprites/traps/sGitantTikiHead.png", 0, 0, {NULL}},
    {CAVE_UP * SHEET_OFFSET, 1, "sprites/blocks/sCaveUp.png", 0, 0, {NULL}},
    {CAVE_UP_2 * SHEET_OFFSET, 1, "sprites/blocks/sCaveUp2.png", 0, 0, {NULL}},
    {BRICK_DOWN * SHEET_OFFSET, 1, "sprites/blocks/sBrickDown.png", 0, 0, {NULL}},
    {TYPE_END * SHEET_OFFSET}};
// clang-format on

static spriteSheet_t *sprite_defs_cache[TYPE_END];

void SpritesInit() {
  for (int i = 0;; i++) {
    if (i == TYPE_END)
      break;
    sprite_defs_cache[i] = NULL;
  }
}

spriteSheet_t *SpriteSheet(int id, int offset) {
  int _id = id * SHEET_OFFSET + offset;

  if (sprite_defs_cache[id]) {
    spriteSheet_t *sheet = sprite_defs_cache[id];
    sheet += offset;
    if (sheet && sheet->id == _id) {
      return sheet;
    } else {
      // printf("from cache %d %d %d\n", id, sheet->id, _id);
    }
  }

  for (int i = 0;; i++) {
    if (sprite_defs[i].id == TYPE_END * SHEET_OFFSET)
      break;
    if (sprite_defs[i].id == id * SHEET_OFFSET) {
      sprite_defs_cache[id] = &sprite_defs[i];
    }
    if (sprite_defs[i].id == _id) {
      return &sprite_defs[i];
    }
  }
  return NULL;
}