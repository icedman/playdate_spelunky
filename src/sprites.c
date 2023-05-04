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
    {BLOCK * SHEET_OFFSET, 1, "sprites/blocks/sBlock.png", 0, 0, {NULL}},
    {BRICK * SHEET_OFFSET, 1, "sprites/blocks/sBrick.png", 0, 0, {NULL}},
    {BRICK_2 * SHEET_OFFSET, 1, "sprites/blocks/sBrick2.png", 0, 0, {NULL}},
    {LADDER * SHEET_OFFSET, 1, "sprites/blocks/sLadder.png", 0, 0, {NULL}},
    {LADDER_TOP * SHEET_OFFSET, 1, "sprites/blocks/sLadderTop.png", 0, 0, {NULL}},
    {ENTRANCE * SHEET_OFFSET, 1, "sprites/blocks/sEntrance.png", 0, 0, {NULL}},
    {EXIT * SHEET_OFFSET, 1, "sprites/blocks/sExit.png", 0, 0, {NULL}},
    {SNAKE * SHEET_OFFSET, 1, "sprites/enemies/sSnakeLeft.png", 0, 0, {NULL}},
    {SPIKES * SHEET_OFFSET, 1, "sprites/traps/sSpikes.png", 0, 0, {NULL}},
    {TYPE_END * SHEET_OFFSET}};
// clang-format on

spriteSheet_t *SpriteSheet(int id, int state) {
  id *= SHEET_OFFSET;
  id += state;
  for (int i = 0;; i++) {
    if (i == TYPE_END)
      break;
    if (sprite_defs[i].id == id) {
      return &sprite_defs[i];
    }
  }
  return NULL;
}