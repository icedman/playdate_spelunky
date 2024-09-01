#include "context.h"
#include "data.h"
#include "entity.h"
#include "game.h"
#include "util.h"

#if 0
#include <math.h>

bool checkLeft() { return false; }
bool checkLeftPressed() { return false; }
bool checkLeftReleased() { return false; }
bool checkRight() { return false; }
bool checkRightPressed() { return false; }
bool checkRightReleased() { return false; }
bool checkUp() { return false; }
bool checkDown() { return false; }
bool checkJump() { return false; }
bool checkJumpPressed() { return false; }
bool checkJumpReleased() { return false; }
bool checkItem() { return false; }
bool checkItemPressed() { return false; }
bool checkItemReleased() { return false; }
bool checkAttack() { return false; }
bool checkAttackPressed() { return false; }
bool checkAttackReleased() { return false; }

entity_t *collision_point(int, int, int, int, int) { return 0; }
entity_t *collision_line(int, int, int, int, int, int, int) { return 0; }

bool approximatelyZero() { return 0; }
bool platformCharacterIs(int s) { return 0; }

entity_t *instance_exists(int) { return 0; }
float distance_to_object(entity_t*) { return 0; }

void playSound(int) {}

struct {
  bool hasCape;
  bool hasGloves;
  bool hasJetpack;
  bool hasJordans;
  bool hasSpikeShoes;
  bool hasSpringShoes;
  int sndJump;
  int downToRun;
} global;

void characterStepEvent(entity_t *e) {
  /*
This script should be placed in the step event for the platform character.
It updates the keys used by the character, moves all of the solids, moves the
character, sets the sprite index, and sets the animation speed for the sprite.
*/
  int hangCount;
  int hangCountMax = 3;

  //////////////////////////////////////
  // KEYS
  //////////////////////////////////////
  bool kLeft, kLeftPushedSteps, kLeftPressed, kLeftReleased;
  bool kRight, kRightPushedSteps, kRightPressed, kRightReleased;
  bool kUp, kUpPressed;
  bool kDown, kDownPressed;
  bool kJumped;
  bool kJump, kJumpPressed, kJumpReleased;
  bool kAttack, kAttackPressed, kAttackReleased;
  bool kItem, kItemPressed, kItemReleased;
  bool kRun;

  int jumps;
  int jumpTime;
  int jumpTimeTotal;
  int jumpButtonReleased;
  int alarm[12];

  int swimming;

  int statePrev;
  int statePrevPrev;
  int runAnimSpeed;
  int climbAnimSpeed;
  int image_speed;
  int image_index;
  float ration;

  float frictionRunningX, frictionRunningY;
  float frictionRunningFastX, frictionRunningFastY;
  float frictionClimbingX, frictionClimbingY;

  int canJump, cantJump, canRun;

  kLeft = checkLeft();

  if (kLeft)
    kLeftPushedSteps += 1;
  else
    kLeftPushedSteps = 0;

  kLeftPressed = checkLeftPressed();
  kLeftReleased = checkLeftReleased();

  kRight = checkRight();

  if (kRight)
    kRightPushedSteps += 1;
  else
    kRightPushedSteps = 0;

  kRightPressed = checkRightPressed();
  kRightReleased = checkRightReleased();

  kUp = checkUp();
  kDown = checkDown();

  // key "run"
  if (canRun)
    kRun = 0;
  // kRun=runKey
  else
    kRun = 0;

  kJump = checkJump();
  kJumpPressed = checkJumpPressed();
  kJumpReleased = checkJumpReleased();

  if (cantJump > 0) {
    kJump = 0;
    kJumpPressed = 0;
    kJumpReleased = 0;
    cantJump -= 1;
  } else {
    //   if (global.isTunnelMan && sprite_index == sTunnelAttackL && !holdItem)
    //   {
    //     kJump = 0;
    //     kJumpPressed = 0;
    //     kJumpReleased = 0;
    //     cantJump -= 1;
    //   }
  }

  kAttack = checkAttack();
  kAttackPressed = checkAttackPressed();
  kAttackReleased = checkAttackReleased();

  kItemPressed = checkItemPressed();

  float xPrev = e->x;
  float yPrev = e->y;
  float upYPrev;
  int maxSlope;
  int maxDownSlope;
  float dist;
  float ratio;
  float yPrevHigh;
  int slopeChangeInY;
  int slopeYPrev;
  int excess;

  bool stunned;
  bool dead;
  bool whipping;
  int state = 0;
  int facing = 0;
  int fallTimer = 0;
  int pushTimer = 0;
  int ladderTimer = 0;
  int runHeld = 0;
  int runAcc = 0;
  int climbAcc = 0;
  int grav = 0;
  int gravityIntensity = 0;
  int departLadderXVel = 0;
  int departLadderYVel = 0;
  int looking;

  int jetpackFuel;

  int ON_GROUND;
  int IN_AIR;
  int ON_LADDER;
  int STANDING;
  int RUNNING;
  int LOOKING_UP;
  int DUCKING;
  int DUCKTOHANG;

  int oLadder;
  int oLadderTop;
  int oWeb;
  int oWater;
  int oArrow;
  int oBall;
  int oCape;
  int oIce;
  int oMonkey;
  int oSolid;
  int oParachute;
  int oTree;
  int oTreeBranch;

  int initialJumpAcc;
  int gravNorm;

  entity_t *obj;
  entity_t *ladder;
  entity_t *holdItem;
  entity_t *ball;
  entity_t *colPointLadder;

  if (stunned || dead) {
    kLeft = false;
    kLeftPressed = false;
    kLeftReleased = false;
    kRight = false;
    kRightPressed = false;
    kRightReleased = false;
    kUp = false;
    kDown = false;
    kJump = false;
    kJumpPressed = false;
    kJumpReleased = false;
    kAttack = false;
    kAttackPressed = false;
    kAttackReleased = false;
    kItemPressed = false;
  }

  //////////////////////////////////////////
  // Collisions
  //////////////////////////////////////////

  bool colSolidLeft = false;
  bool colSolidRight = false;
  bool colLeft = false;
  bool colRight = false;
  bool colTop = false;
  bool colBot = false;
  bool colLadder = false;
  bool colPlatBot = false;
  bool colPlat = false;
  bool colWaterTop = false;
  bool colIceBot = false;
  bool runKey = false;

  // if (isCollisionMoveableSolidLeft(1)) colSolidLeft = true;
  // if (isCollisionMoveableSolidRight(1)) colSolidRight = true;
  // if (isCollisionLeft(1)) colLeft = true;
  // if (isCollisionRight(1)) colRight = true;
  // if (isCollisionTop(1)) colTop = true;
  // if (isCollisionBottom(1)) colBot = true;
  // if (isCollisionLadder()) colLadder = true;
  // if (isCollisionPlatformBottom(1)) colPlatBot = true;
  // if (isCollisionPlatform()) colPlat = true;
  // if (isCollisionWaterTop(1)) colWaterTop = true;
  // if (collision_point(e->x, e->y + 8, oIce, 0, 0)) colIceBot = true;
  // if (checkRun()) {
  //   runHeld = 100;
  //   runKey = true;
  // }

  if (checkAttack() && !whipping) {
    runHeld += 1;
    runKey = true;
  }

  if (!runKey || (!kLeft && !kRight))
    runHeld = 0;

  // allows the character to run left && right
  // if state!=DUCKING && state!=LOOKING_UP && state!=CLIMBING
  if (state != CLIMBING && state != HANGING) {
    if (kLeftReleased && approximatelyZero(e->xVel))
      e->xAcc -= 0.5;
    if (kRightReleased && approximatelyZero(e->xVel))
      e->xAcc += 0.5;

    if (kLeft && !kRight) {
      if (colSolidLeft) {
        // e->xVel = 3;
        if (platformCharacterIs(ON_GROUND) && state != DUCKING) {
          e->xAcc -= 1;
          pushTimer += 10;
          // if (!SS_IsSoundPlaying(global.sndPush)) playSound(global.sndPush);
        }
      } else if (kLeftPushedSteps > 2 &&
                 (facing = LEFT || approximatelyZero(e->xVel))) {
        e->xAcc -= runAcc;
      }
      facing = LEFT;
      // if (platformCharacterIs(ON_GROUND) && ABS(e->xVel) > 0 && alarm[3] < 1)
      // alarm[3] = floor(16/-e->xVel);
    }

    if (kRight && !kLeft) {
      if (colSolidRight) {
        // e->xVel = 3;
        if (platformCharacterIs(ON_GROUND) && state != DUCKING) {
          e->xAcc += 1;
          pushTimer += 10;
          // if (!SS_IsSoundPlaying(global.sndPush)) playSound(global.sndPush);
        }
      } else if ((kRightPushedSteps > 2 || colSolidLeft) &&
                 (facing == RIGHT || approximatelyZero(e->xVel))) {
        e->xAcc += runAcc;
      }
      facing = RIGHT;
      // if (platformCharacterIs(ON_GROUND) && ABS(e->xVel) > 0 && alarm[3] < 1)
      // alarm[3] = floor(16/e->xVel);
    }
  }

  /******************************************
  LADDERS
  *******************************************/

  if (state == CLIMBING) {
    // TODO
    // if (instance_exists(oCape)) {
    //   oCape.open = false;
    // }
    kJumped = false;
    ladderTimer = 10;
    ladder = collision_point(e->x, e->y, oLadder, 0, 0);
    if (ladder)
      e->x = ladder->x + 8;

    if (kLeft)
      facing = LEFT;
    else if (kRight)
      facing = RIGHT;
    if (kUp) {
      if (collision_point(e->x, e->y - 8, oLadder, 0, 0) ||
          collision_point(e->x, e->y - 8, oLadderTop, 0, 0)) {
        e->yAcc -= climbAcc;
        if (alarm[2] < 1)
          alarm[2] = 8;
      }
    } else if (kDown) {
      if (collision_point(e->x, e->y + 8, oLadder, 0, 0) ||
          collision_point(e->x, e->y + 8, oLadderTop, 0, 0)) {
        e->yAcc += climbAcc;
        if (alarm[2] < 1)
          alarm[2] = 8;
      } else
        state = FALLING;
      if (colBot)
        state = STANDING;
    }

    if (kJumpPressed && !whipping) {
      if (kLeft)
        e->xVel = -departLadderXVel;
      else if (kRight)
        e->xVel = departLadderXVel;
      else
        e->xVel = 0;
      e->yAcc += departLadderYVel;
      state = JUMPING;
      jumpButtonReleased = 0;
      jumpTime = 0;
      ladderTimer = 5;
    }
  } else {
    if (ladderTimer > 0)
      ladderTimer -= 1;
  }

  if (platformCharacterIs(IN_AIR) && state != HANGING) {
    e->yAcc += gravityIntensity;
  }

  // Player has landed
  if ((colBot || colPlatBot) && platformCharacterIs(IN_AIR) && e->yVel >= 0) {
    if (!colPlat || colBot) {
      e->yVel = 0;
      e->yAcc = 0;
      state = RUNNING;
      jumps = 0;
    }
    // playSound(global.sndLand);
  }
  if ((colBot || colPlatBot) && !colPlat)
    e->yVel = 0;

  // Player has just walked off of the edge of a solid
  if (colBot == 0 && (!colPlatBot || colPlat) &&
      platformCharacterIs(ON_GROUND)) {
    state = FALLING;
    e->yAcc += grav;
    kJumped = true;
    if (global.hasGloves)
      hangCount = 5;
  }

  if (colTop) {
    if (dead || stunned)
      e->yVel = -e->yVel * 0.8;
    else if (state == JUMPING)
      e->yVel = ABS(e->yVel * 0.3);
  }

  if ((colLeft && facing == LEFT) || (colRight && facing == RIGHT)) {
    if (dead || stunned)
      e->xVel = -e->xVel * 0.5;
    else
      e->xVel = 0;
  }

  /******************************************
  JUMPING
  *******************************************/

  if (kJumpReleased && platformCharacterIs(IN_AIR)) {
    kJumped = true;
  } else if (platformCharacterIs(ON_GROUND)) {
    // oCape.open = false;
    kJumped = false;
  }

  if (kJumpPressed && collision_point(e->x, e->y, oWeb, 0, 0)) {
    // obj = instance_place(e->x, e->y, oWeb);
    obj->life -= 1;
    e->yAcc += initialJumpAcc * 2;
    e->yVel -= 3;
    e->xAcc += e->xVel / 2;

    state = JUMPING;
    jumpButtonReleased = 0;
    jumpTime = 0;

    grav = gravNorm;
  } else if (kJumpPressed && colWaterTop) {
    e->yAcc += initialJumpAcc * 2;
    e->yVel -= 3;
    e->xAcc += e->xVel / 2;

    state = JUMPING;
    jumpButtonReleased = 0;
    jumpTime = 0;

    grav = gravNorm;
  } else if (global.hasCape && kJumpPressed && kJumped &&
             platformCharacterIs(IN_AIR)) {
  //   if (!oCape.open)
  //     oCape.open = true;
  //   else
  //     oCape.open = false;
  // } else if (global.hasJetpack && kJump && kJumped &&
  //            platformCharacterIs(IN_AIR) && jetpackFuel > 0) {
    e->yAcc += initialJumpAcc;
    e->yVel = -1;
    jetpackFuel -= 1;
    if (alarm[10] < 1)
      alarm[10] = 3;

    state = JUMPING;
    jumpButtonReleased = 0;
    jumpTime = 0;

    grav = 0;
  } else if (platformCharacterIs(ON_GROUND) && kJumpPressed && fallTimer == 0) {
    if (e->xVel > 3 || e->xVel < -3) {
      e->yAcc += initialJumpAcc * 2;
      e->xAcc += e->xVel * 2;
    } else {
      e->yAcc += initialJumpAcc * 2;
      e->xAcc += e->xVel / 2;
    }

    if (global.hasJordans) {
      e->yAcc *= 3;
      e->yAccLimit = 12;
      grav = 0.5;
    } else if (global.hasSpringShoes)
      e->yAcc *= 1.5;
    else {
      e->yAccLimit = 6;
      grav = gravNorm;
    }

    playSound(global.sndJump);

    pushTimer = 0;

    // the "state" gets changed to JUMPING later on in the code
    state = FALLING;
    // "variable jumping" states
    jumpButtonReleased = 0;
    jumpTime = 0;
  }

  if (jumpTime < jumpTimeTotal)
    jumpTime += 1;
  // let the character continue to jump
  if (kJump == 0)
    jumpButtonReleased = 1;
  if (jumpButtonReleased)
    jumpTime = jumpTimeTotal;

  gravityIntensity = (jumpTime / jumpTimeTotal) * grav;

  if (kUp && platformCharacterIs(ON_GROUND) && !colLadder) {
    looking = UP;
    if (e->xVel == 0 && e->xAcc == 0)
      state = LOOKING_UP;
  } else
    looking = 0;

  if (!kUp && state == LOOKING_UP) {
    state = STANDING;
  }

/******************************************
HANGING
*******************************************/

  if (!colTop) {
    if (global.hasGloves && e->yVel > 0) {
      if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
          kRight && colRight &&
          (collision_point(e->x + 9, e->y - 5, oSolid, 0, 0) ||
           collision_point(e->x + 9, e->y - 6, oSolid, 0, 0))) {
        state = HANGING;
        move_snap(1, 8);
        e->yVel = 0;
        e->yAcc = 0;
        grav = 0;
      } else if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
                 kLeft && colLeft &&
                 (collision_point(e->x - 9, e->y - 5, oSolid, 0, 0) ||
                  collision_point(e->x - 9, e->y - 6, oSolid, 0, 0))) {
        state = HANGING;
        move_snap(1, 8);
        e->yVel = 0;
        e->yAcc = 0;
        grav = 0;
      }
    } else if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
               kRight && colRight &&
               (collision_point(e->x + 9, e->y - 5, oTree, 0, 0) ||
                collision_point(e->x + 9, e->y - 6, oTree, 0, 0))) {
      state = HANGING;
      move_snap(1, 8);
      e->yVel = 0;
      e->yAcc = 0;
      grav = 0;
    } else if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
               kLeft && colLeft &&
               (collision_point(e->x - 9, e->y - 5, oTree, 0, 0) ||
                collision_point(e->x - 9, e->y - 6, oTree, 0, 0))) {
      state = HANGING;
      move_snap(1, 8);
      e->yVel = 0;
      e->yAcc = 0;
      grav = 0;
    } else if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
               kRight && colRight &&
               (collision_point(e->x + 9, e->y - 5, oSolid, 0, 0) ||
                collision_point(e->x + 9, e->y - 6, oSolid, 0, 0)) &&
               !collision_point(e->x + 9, e->y - 9, oSolid, 0, 0) &&
               !collision_point(e->x, e->y + 9, oSolid, 0, 0)) {
      state = HANGING;
      move_snap(1, 8);
      e->yVel = 0;
      e->yAcc = 0;
      grav = 0;
    } else if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
               kLeft && colLeft &&
               (collision_point(e->x - 9, e->y - 5, oSolid, 0, 0) ||
                collision_point(e->x - 9, e->y - 6, oSolid, 0, 0)) &&
               !collision_point(e->x - 9, e->y - 9, oSolid, 0, 0) &&
               !collision_point(e->x, e->y + 9, oSolid, 0, 0)) {
      state = HANGING;
      move_snap(1, 8);
      e->yVel = 0;
      e->yAcc = 0;
      grav = 0;
    }

    if (hangCount == 0 && e->y > 16 && !platformCharacterIs(ON_GROUND) &&
        state == FALLING &&
        (collision_point(e->x, e->y - 5, oArrow, 0, 0) ||
         collision_point(e->x, e->y - 6, oArrow, 0, 0)) &&
        !collision_point(e->x, e->y - 9, oArrow, 0, 0) &&
        !collision_point(e->x, e->y + 9, oArrow, 0, 0)) {
      obj = instance_nearest(e->x, e->y - 5, oArrow);
      if (false /*obj->stuck*/) {
        state = HANGING;
        // move_snap(1, 8);
        e->yVel = 0;
        e->yAcc = 0;
        grav = 0;
      }
    }

    /*
if (hangCount == 0 and e->y > 16 and !platformCharacterIs(ON_GROUND) and state ==
FALLING and (collision_point(e->x, e->y-5, oTreeBranch, 0, 0) or
collision_point(e->x, y-6, oTreeBranch, 0, 0)) and not collision_point(e->x,
e->y-9, oTreeBranch, 0, 0) and not collision_point(e->x, e->y+9, oTreeBranch, 0,
0))
{
state = HANGING;
// move_snap(1, 8);
e->yVel = 0;
e->yAcc = 0;
grav = 0;
}
*/
  }

  if (hangCount > 0)
    hangCount -= 1;

  if (state == HANGING) {
    // if (instance_exists(oCape))
    //   oCape.open = false;
    kJumped = false;

    if (kDown && kJumpPressed) {
      grav = gravNorm;
      state = FALLING;
      e->yAcc -= grav;
      hangCount = 5;
      if (global.hasGloves)
        hangCount = 10;
    } else if (kJumpPressed) {
      grav = gravNorm;
      if ((facing == RIGHT && kLeft) || (facing == LEFT && kRight)) {
        state = FALLING;
        e->yAcc -= grav;
      } else {
        state = JUMPING;
        e->yAcc += initialJumpAcc * 2;
        if (facing == RIGHT)
          e->x -= 2;
        else
          e->x += 2;
      }
      hangCount = hangCountMax;
    }

    if ((facing == LEFT && !isCollisionLeft(2)) ||
        (facing == RIGHT && !isCollisionRight(2))) {
      grav = gravNorm;
      state = FALLING;
      e->yAcc -= grav;
      hangCount = 4;
    }
  } else {
    grav = gravNorm;
  }

  // pressing down while standing
  if (kDown && platformCharacterIs(ON_GROUND) && !whipping) {
    if (colBot) {
      state = DUCKING;
    } else if (colPlatBot) {
      // climb down ladder if possible, else jump down
      fallTimer = 0;
      if (!colBot) {
        ladder = 0;
        ladder = instance_place(e->x, e->y + 16, oLadder);
        if (instance_exists(ladder)) {
          if (ABS(e->x - (ladder->x + 8)) < 4) {
            e->x = ladder->x + 8;

            e->xVel = 0;
            e->yVel = 0;
            e->xAcc = 0;
            e->yAcc = 0;
            state = CLIMBING;
          }
        } else {
          e->y += 1;
          state = FALLING;
          e->yAcc += grav;
        }
      } else {
        // the character can't move down because there is a solid in the way
        state = RUNNING;
      }
    }
  }
  if (!kDown && state == DUCKING) {
    state = STANDING;
    e->xVel = 0;
    e->xAcc = 0;
  }
  if (e->xVel == 0 && e->xAcc == 0 && state == RUNNING) {
    state = STANDING;
  }
  if (e->xAcc != 0 && state == STANDING) {
    state = RUNNING;
  }
  if (e->yVel < 0 && platformCharacterIs(IN_AIR) && state != HANGING) {
    state = JUMPING;
  }
  if (e->yVel > 0 && platformCharacterIs(IN_AIR) && state != HANGING) {
    state = FALLING;
    setCollisionBounds(-5, -6, 5, 8);
  } else
    setCollisionBounds(-5, -8, 5, 8);

  // CLIMB LADDER
  colPointLadder = collision_point(e->x, e->y, oLadder, 0, 0) ||
                   collision_point(e->x, e->y, oLadderTop, 0, 0);

  if ((kUp && platformCharacterIs(IN_AIR) &&
       collision_point(e->x, e->y - 8, oLadder, 0, 0) && ladderTimer == 0) ||
      (kUp && colPointLadder && ladderTimer == 0) ||
      (kDown && colPointLadder && ladderTimer == 0 &&
       platformCharacterIs(ON_GROUND) &&
       collision_point(e->x, e->y + 9, oLadderTop, 0, 0) && e->xVel == 0)) {
    ladder = 0;
    ladder = instance_place(e->x, e->y - 8, oLadder);
    if (instance_exists(ladder)) {
      if (ABS(e->x - (ladder->x + 8)) < 4) {
        e->x = ladder->x + 8;
        if (!collision_point(e->x, e->y, oLadder, 0, 0) &&
            !collision_point(e->x, e->y, oLadderTop, 0, 0)) {
          e->y = ladder->y + 14;
        }

        e->xVel = 0;
        e->yVel = 0;
        e->xAcc = 0;
        e->yAcc = 0;
        state = CLIMBING;
      }
    }
  }

  /*
if (sprite_index == sDuckToHangL or sprite_index == sDamselDtHL)
{
  ladder = 0;
  if (facing == LEFT and collision_rectangle(e->x-8, e->y, e->x, e->y+16, oLadder,
0, 0) and not collision_point(e->x-4, e->y+16, oSolid, 0, 0))
  {
      ladder = instance_nearest(e->x-4, e->y+16, oLadder);
  }
  else if (facing == RIGHT and collision_rectangle(e->x, e->y, x+8, e->y+16,
oLadder, 0, 0) and not collision_point(e->x+4, e->y+16, oSolid, 0, 0))
  {
      ladder = instance_nearest(e->x+4, e->y+16, oLadder);
  }

  if (ladder)
  {
      e->x = ladder->x + 8;

      e->xVel = 0;
      e->yVel = 0;
      e->xAcc = 0;
      e->yAcc = 0;
      state = CLIMBING;
  }
}
*/
  /*
if (colLadder and state == CLIMBING and kJumpPressed and not whipping)
{
  if (kLeft)
      e->xVel = -departLaddere->XVel;
  else if (kRight)
      e->xVel = departLaddere->XVel;
  else
      e->xVel = 0;
  e->yAcc += departLadderYVel;
  state = JUMPING;
  jumpButtonReleased = 0;
  jumpTime = 0;
  ladderTimer = 5;
}
*/

  // Calculate horizontal/vertical friction
  if (state == CLIMBING) {
    e->xFric = frictionClimbingX;
    e->yFric = frictionClimbingY;
  } else {
    if (runKey && platformCharacterIs(ON_GROUND) && runHeld >= 10) {
      if (kLeft) {
        // run
        e->xVel -= 0.1;
        e->xVelLimit = 6;
        e->xFric = frictionRunningFastX;
      } else if (kRight) {
        e->xVel += 0.1;
        e->xVelLimit = 6;
        e->xFric = frictionRunningFastX;
      }
    } else if (state == DUCKING) {
      if (e->xVel < 2 && e->xVel > -2) {
        e->xFric = 0.2;
        e->xVelLimit = 3;
        image_speed = 0.8;
      } else if (kLeft && global.downToRun) {
        // run
        e->xVel -= 0.1;
        e->xVelLimit = 6;
        e->xFric = frictionRunningFastX;
      } else if (kRight && global.downToRun) {
        e->xVel += 0.1;
        e->xVelLimit = 6;
        e->xFric = frictionRunningFastX;
      } else {
        e->xVel *= 0.8;
        if (e->xVel < 0.5)
          e->xVel = 0;
        e->xFric = 0.2;
        e->xVelLimit = 3;
        image_speed = 0.8;
      }
    } else {
      // decrease the friction when the character is "flying"
      if (platformCharacterIs(IN_AIR)) {
        if (dead || stunned)
          e->xFric = 1.0;
        else
          e->xFric = 0.8;
      } else {
        e->xFric = frictionRunningX;
      }
    }

    // Stuck on web || underwater
    if (collision_point(e->x, e->y, oWeb, 0, 0)) {
      e->xFric = 0.2;
      e->yFric = 0.2;
      fallTimer = 0;
    } else if (collision_point(e->x, e->y, oWater, -1, -1)) {
      // if (instance_exists(oCape))
      //   oCape.open = false;

      if (state == FALLING && e->yVel > 0) {
        e->yFric = 0.5;
      } else if (!collision_point(e->x, e->y - 9, oWater, -1, -1)) {
        e->yFric = 1;
      } else {
        e->yFric = 0.9;
      }
    } else {
      swimming = false;
      e->yFric = 1;
    }
  }

  if (colIceBot && state != DUCKING && !global.hasSpikeShoes) {
    e->xFric = 0.98;
    e->yFric = 1;
  }

  // RUNNING

  if (platformCharacterIs(ON_GROUND)) {
    if (state == RUNNING && kLeft && colLeft) {
      pushTimer += 1;
    } else if (state == RUNNING && kRight && colRight) {
      pushTimer += 1;
    } else {
      pushTimer = 0;
    }

    if (platformCharacterIs(ON_GROUND) && !kJump && !kDown && !runKey) {
      e->xVelLimit = 3;
    }

    // ledge flip
    if (state == DUCKING && ABS(e->xVel) < 3 && facing == LEFT &&
        collision_point(e->x, e->y + 9, oSolid, 0, 0) &&
        !collision_line(e->x - 1, e->y + 9, e->x - 10, e->y + 9, oSolid, 0, 0) &&
        kLeft) {
      state = DUCKTOHANG;

      if (holdItem) {
        // holdItem->held = false;
        if (holdItem->type == 'Gold Idol')
          holdItem->y -= 8;
        scrDropItem(-1, -4);
      }

  // instances_of(oMonkey).forEach(($) => {
  //   with ($) {
  //     // knock off monkeys that grabbed you
  //     if (status == 7) {
  //       e->xVel = -1;
  //       e->yVel = -4;
  //       status = 1;
  //       vineCounter = 20;
  //       grabCounter = 60;
  //   }
  // }
  // });
}
else if (state == DUCKING && ABS(e->xVel) < 3 && facing == RIGHT &&
         collision_point(e->x, e->y + 9, oSolid, 0, 0) &&
         !collision_line(e->x + 1, e->y + 9, e->x + 10, e->y + 9, oSolid, 0, 0) &&
         kRight) {
  state = DUCKTOHANG;

  if (holdItem) {
    // holdItem->held = false;
    if (holdItem->type == 'Gold Idol')
        holdItem->y -= 8;
    scrDropItem(1, -4);
  }

//         instances_of(oMonkey).forEach(($) => {
//           with ($) {
//             // knock off monkeys that grabbed you
//             if (status == 7) {
//               e->xVel = 1;
//               e->yVel = -4;
//               status = 1;
//               vineCounter = 20;
//               grabCounter = 60;
// }
// }
// });

}
}

if (state == DUCKTOHANG) {
        e->x = xPrev;
        e->y = yPrev;
        e->xVel = 0;
        e->yVel = 0;
        e->xAcc = 0;
        e->yAcc = 0;
        grav = 0;
}

// PARACHUTE AND CAPE
if (instance_exists(oParachute)) {
        e->yFric = 0.5;
}
// if (instance_exists(oCape)) {
//         if (oCape.open)
//           e->yFric = 0.5;
// }

if (pushTimer > 100)
        pushTimer = 100;

// limits the acceleration if it is too extreme
if (e->xAcc > e->xAccLimit)
        e->xAcc = e->xAccLimit;
else if (e->xAcc < -e->xAccLimit)
        e->xAcc = -e->xAccLimit;
if (e->yAcc > e->yAccLimit)
        e->yAcc = e->yAccLimit;
else if (e->yAcc < -e->yAccLimit)
        e->yAcc = -e->yAccLimit;

// applies the acceleration
e->xVel += e->xAcc;
if (dead || stunned)
        e->yVel += 0.6;
else
        e->yVel += e->yAcc;

// nullifies the acceleration
e->xAcc = 0;
e->yAcc = 0;

// applies the friction to the velocity, now that the velocity has been
// calculated
e->xVel *= e->xFric;
e->yVel *= e->yFric;

// apply ball && chain
if (instance_exists(oBall)) {
        if (distance_to_object(ball) >= 24) {
          if (e->xVel > 0 && ball->x < e->x && ABS(ball->x - e->x) > 24)
        e->xVel = 0;
          if (e->xVel < 0 && ball->x > e->x && ABS(ball->x - e->x) > 24)
        e->xVel = 0;
          if (e->yVel > 0 && ball->y < e->y && ABS(ball->y - e->y) > 24) {
        if (ABS(ball->x - e->x) < 1) {
          e->x = ball->x;
        } else if (ball->x < e->x && !kRight) {
          if (e->xVel > 0)
            e->xVel *= -0.25;
          else if (e->xVel == 0)
            e->xVel -= 1;
        } else if (ball->x > e->x && !kLeft) {
          if (e->xVel < 0)
            e->xVel *= -0.25;
          else if (e->xVel == 0)
            e->xVel += 1;
        }
        e->yVel = 0;
        fallTimer = 0;
          }
          if (e->yVel < 0 && ball->y > e->y && ABS(ball->y - e->y) > 24)
        e->yVel = 0;
        }
}

// apply the limits since the velocity may be too extreme
if (!dead && !stunned) {
        if (e->xVel > e->xVelLimit)
          e->xVel = e->xVelLimit;
        else if (e->xVel < -e->xVelLimit)
          e->xVel = -e->xVelLimit;
}
if (e->yVel > e->yVelLimit)
        e->yVel = e->yVelLimit;
else if (e->yVel < -e->yVelLimit)
        e->yVel = -e->yVelLimit;

// approximates the "active" variables
if (approximatelyZero(e->xVel))
        e->xVel = 0;
if (approximatelyZero(e->yVel))
        e->yVel = 0;
if (approximatelyZero(e->xAcc))
        e->xAcc = 0;
if (approximatelyZero(e->yAcc))
        e->yAcc = 0;

// prepares the character to move up a hill
// we need to use the "slopeYPrev" variable later to know the "true" e->y previous
// value keep this condition the same
if (maxSlope > 0 && platformCharacterIs(ON_GROUND) && e->xVel != 0) {
        slopeYPrev = e->y;
        for (; e->y >= slopeYPrev - maxSlope; e->y -= 1)
          if (colTop)
        break;
        slopeChangeInY = slopeYPrev - e->y;
} else
        slopeChangeInY = 0;

// moves the character, && balances out the effects caused by other processes
// keep this condition the same
if (maxSlope * ABS(e->xVel) > 0 && platformCharacterIs(ON_GROUND)) {
        // we need to check if we should dampen out the speed as the character
        // runs on upward slopes
        xPrev = e->x;
        yPrev = slopeYPrev; // we don't want to use y, because e->y is too high
        yPrevHigh = e->y;      // we'll use the higher previous variable later
        moveTo(e->xVel, e->yVel + slopeChangeInY);
        dist = point_distance(xPrev, yPrev, e->x,
                              e->y); // overall distance that has been traveled
        // we should have only ran at e->xVel
        if (dist > ABS(e->xVelInteger)) {
          // show_message(string(dist)+ " "+string(ABS(e->xVelInteger)))
          excess = dist - ABS(e->xVelInteger);
          if (e->xVelInteger < 0)
        excess *= -1;
          // move back since the character moved too far
          e->x = xPrev;
          e->y = yPrevHigh; // we need the character to be high so the character
                         // can move down
          // this time we'll move the correct distance, but we need to shorten
          // out the e->xVel a little these lines can be changed for different
          // types of slowing down when running up hills
          ratio = (ABS(e->xVelInteger) / dist) * 0.9; // can be changed
          moveTo(round(e->xVelInteger * ratio),
                 round(e->yVelInteger * ratio + slopeChangeInY));
        }
} else {
        // we simply move e->xVel && e->yVel while in the air || on a ladder
        moveTo(e->xVel, e->yVel);
}
// move the character downhill if possible
// we need to multiply maxDownSlope by the absolute value of e->xVel since the
// character normally runs at an e->xVel larger than 1
if (!colBot && maxDownSlope > 0 && e->xVelInteger != 0 &&
    platformCharacterIs(ON_GROUND)) {
        // the character is floating just above the slope, so move the character
        // down
        upYPrev = e->y;
        for (; e->y <= upYPrev + maxDownSlope; e->y += 1)
          if (colBot) {
        // we hit a solid below
        upYPrev = e->y; // I know that this doesn't seem to make sense, because of
                     // the name of the variable, but it all works out correctly
                     // after we break out of this loop
        break;
          }
        e->y = upYPrev;
}

// figures out what the sprite index of the character should be
// characterSprite();

// sets the previous state && the previously previous state
statePrevPrev = statePrev;
statePrev = state;

// calculates the image_speed based on the character's velocity
if (state == RUNNING || state == DUCKING || state == LOOKING_UP) {
        if (state == RUNNING || state == LOOKING_UP)
          image_speed = ABS(e->xVel) * runAnimSpeed + 0.1;
}

if (state == CLIMBING)
        image_speed = sqrt(sqr(ABS(e->xVel)) + sqr(ABS(e->yVel))) * climbAnimSpeed;
if (e->xVel >= 4 || e->xVel <= -4) {
        image_speed = 1;
        if (platformCharacterIs(ON_GROUND))
          setCollisionBounds(-8, -8, 8, 8);
        else
          setCollisionBounds(-5, -8, 5, 8);
} else
        setCollisionBounds(-5, -8, 5, 8);
if (whipping)
        image_speed = 1;
if (state == DUCKTOHANG) {
        image_index = 0;
        image_speed = 0.8;
}
// limit the image_speed at 1 so the animation always looks good
if (image_speed > 1)
        image_speed = 1;

}

#endif