#include "game.h"
#include "map.h"
#include "util.h"

/*
Note:

ROOMS are 10x8 tile areas.

strTemp = "
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
";

OBSTACLES are 5x3 tile chunks that are randomized within rooms.

strObs = "00000
00000
00000";
*/

void scrRoomGen1(map_t *map, int x, int y) {
  int currentLevel = GameInstance()->currentLevel;
  map->roomGen = 1;

  char strTemp[] =
      "000000000000000000000000000000000000000000000000000000000000"
      "00000000000000000000";
  int n;
  int i;
  int j;

  int roomPath = map->roomPath[scrGetRoomX(x) + scrGetRoomY(y) * 4];
  int roomPathAbove = -1;

  char *shopType = "General";

  if (scrGetRoomY(y) != 0)
    roomPathAbove = map->roomPath[scrGetRoomX(x) + scrGetRoomY(y - 128) * 4];

  if (scrGetRoomX(x) == map->startRoomX &&
      scrGetRoomY(y) == map->startRoomY) { // start room
    if (roomPath == 2)
      n = Rand(5, 8);
    else
      n = Rand(1, 4);
    switch (n) {
    case 1: {
      strcpy(strTemp, "60000600000000000000000000000000000000000008000000000000"
                      "000000000000001111111111");
      break;
    }
    case 2: {
      strcpy(strTemp, "11111111112222222222000000000000000000000008000000000000"
                      "000000000000001111111111");
      break;
    }
    case 3: {
      strcpy(strTemp, "00000000000008000000000000000000L000000000P111111000L111"
                      "111000L00111111111111111");
      break;
    }
    case 4: {
      strcpy(strTemp, "0000000000008000000000000000000000000L000111111P00011111"
                      "1L001111100L001111111111");
      break;
    }
    // hole
    case 5: {
      strcpy(strTemp, "60000600000000000000000000000000000000000008000000000000"
                      "000000000000002021111120");
      break;
    }
    case 6: {
      strcpy(strTemp, "11111111112222222222000000000000000000000008000000000000"
                      "000000000000002021111120");
      break;
    }
    case 7: {
      strcpy(strTemp, "00000000000008000000000000000000L000000000P111111000L111"
                      "111000L00011111111101111");
      break;
    }
    case 8: {
      strcpy(strTemp, "0000000000008000000000000000000000000L000111111P00011111"
                      "1L001111000L001111011111");
      break;
    }
    }
  } else if (scrGetRoomX(x) == map->endRoomX &&
             scrGetRoomY(y) == map->endRoomY) { // end room
    if (roomPathAbove == 2)
      n = Rand(2, 4);
    else
      n = Rand(3, 6);
    switch (n) {
    case 1: {
      strcpy(strTemp, "00000000006000060000000000000000000000000008000000000000"
                      "000000000000001111111111");
      break;
    }
    case 2: {
      strcpy(strTemp, "00000000000000000000000000000000000000000008000000000000"
                      "000000000000001111111111");
      break;
    }
    case 3: {
      strcpy(strTemp, "00000000000010021110001001111000110111129012000000111111"
                      "111021111111201111111111");
      break;
    }
    case 4: {
      strcpy(strTemp, "00000000000111200100011110010021111011000000002109011111"
                      "111102111111121111111111");
      break;
    }
    // no drop
    case 5: {
      strcpy(strTemp, "60000600000000000000000000000000000000000008000000000000"
                      "000000000000001111111111");
      break;
    }
    case 6: {
      strcpy(strTemp, "11111111112222222222000000000000000000000008000000000000"
                      "000000000000001111111111");
      break;
    }
    }
  } else if (roomPath == 0) { // side room
    if (currentLevel > 1 && !map->altar && Rand(1, 16) == 1) {
      n = 11;
      map->altar = true;
    } else if (map->idol || scrGetRoomY(y) == 3) {
      n = Rand(1, 9);
    } else {
      n = Rand(1, 10);
      if (n == 10)
        map->idol = true;
      // else n = rand(1,9);
    }

    switch (n) {
    // upper plats
    case 1: {
      strcpy(strTemp, "00000000000010111100000000000000011010000050000000000000"
                      "000000000000001111111111");
      break;
    }
    // high walls
    case 2: {
      strcpy(strTemp, "110000000040L600000011P000000011L000000011L5000000110000"
                      "000011000000001111111111");
      break;
    }
    case 3: {
      strcpy(strTemp, "00000000110060000L040000000P110000000L110050000L11000000"
                      "001100000000111111111111");
      break;
    }
    case 4: {
      strcpy(strTemp, "110000000040L600000011P000000011L000000011L0000000110000"
                      "000011000000001112222111");
      break;
    }
    case 5: {
      strcpy(strTemp, "00000000110060000L040000000P110000000L110000000L11000000"
                      "001100000000111112222111");
      break;
    }
    case 6: {
      strcpy(strTemp, "11111111110221111220002111120000022220000002222000002111"
                      "120002211112201111111111");
      break;
    }
    case 7: {
      strcpy(strTemp, "11111111111112222111112000021111102201111120000211111022"
                      "011111200002111112222111");
      break;
    }
    case 8: {
      strcpy(strTemp, "11111111110000000000110000001111222222111111111111112222"
                      "221122000000221100000011");
      break;
    }
    case 9: {
      strcpy(strTemp, "121111112100L2112L0011P1111P1111L2112L1111L1111L1111L122"
                      "1L1100L0000L001111221111");
      break;
    }
    // idols
    case 10: {
      strcpy(strTemp, "22000000220000B00000000000000000000000000000000000000000"
                      "00000000I000001111A01111");
      break;
    }
    // altars
    case 11: {
      strcpy(strTemp, "220000002200000000000000000000000000000000000000000000x0"
                      "000002211112201111111111");
      break;
    }
    }
  } else if (roomPath == 0 || roomPath == 1) { // main room
    switch (Rand(1, 12)) {

    // basic rooms
    case 1: {
      strcpy(strTemp, "60000600000000000000000000000000000000000050000000000000"
                      "000000000000001111111111");
      break;
    }
    case 2: {
      strcpy(strTemp, "60000600000000000000000000000000000000005000050000000000"
                      "000000000000001111111111");
      break;
    }
    case 3: {
      strcpy(strTemp, "60000600000000000000000000000000050000000000000000000000"
                      "000011111111111111111111");
      break;
    }
    case 4: {
      strcpy(strTemp, "60000600000000000000000600000000000000000000000000000222"
                      "220000111111001111111111");
      break;
    }
    case 5: {
      strcpy(strTemp, "11111111112222222222000000000000000000000050000000000000"
                      "000000000000001111111111");
      break;
    }
    case 6: {
      strcpy(strTemp, "11111111112111111112022222222000000000000050000000000000"
                      "000000000000001111111111");
      break;
    }
    // low ceiling
    case 7: {
      strcpy(strTemp, "11111111112111111112211111111221111111120111111110022222"
                      "222000000000001111111111");
      break;
    }
    // ladders
    case 8: {
      if (Rand(1, 2) == 1)
        strcpy(strTemp, "1111111111000000000L111111111P000000000L50000500000000"
                        "00000000000000001111111111");
      else
        strcpy(strTemp, "1111111111L000000000P111111111L00000000050000500000000"
                        "00000000000000001111111111");
      break;
    }
    case 9: {
      strcpy(strTemp, "000000000000L0000L0000P1111P0000L0000L0000P1111P0000L111"
                      "1L0000L1111L001111111111");
      break;
    }
    // upper plats
    case 10: {
      strcpy(strTemp, "00000000000111111110001111110000000000005000050000000000"
                      "000000000000001111111111");
      break;
    }
    case 11: {
      strcpy(strTemp, "00000000000000000000000000000000000000000021111200021111"
                      "112021111111121111111111");
      break;
    }
    // treasure below
    case 12: {
      if (Rand(1, 2) == 1)
        strcpy(strTemp, "2222222222000000000000000000L001111111P001050000L01100"
                        "0000L010000000L01111111111");
      else
        strcpy(strTemp, "222222222200000000000L000000000P111111100L500000100L00"
                        "0000110L000000011111111111");
      break;
    }
    }
  } else if (roomPath == 3) { // main room
    switch (Rand(1, 8)) {

    // basic rooms
    case 1: {
      strcpy(strTemp, "00000000000000000000000000000000000000000050000000000000"
                      "000000000000001111111111");
      break;
    }
    case 2: {
      strcpy(strTemp, "00000000000000000000000000000000000000005000050000000000"
                      "000000000000001111111111");
      break;
    }
    case 3: {
      strcpy(strTemp, "00000000000000000000000000000050000500000000000000000000"
                      "000011111111111111111111");
      break;
    }
    case 4: {
      strcpy(strTemp, "00000000000000000000000600000000000000000000000000000111"
                      "110000111111001111111111");
      break;
    }
    // upper plats
    case 5: {
      strcpy(strTemp, "00000000000111111110001111110000000000005000050000000000"
                      "000000000000001111111111");
      break;
    }
    case 6: {
      strcpy(strTemp, "00000000000000000000000000000000000000000021111200021111"
                      "112021111111121111111111");
      break;
    }
    case 7: {
      strcpy(strTemp, "10000000011112002111111200211100000000000022222000111111"
                      "111111111111111111111111");
      break;
    }
    // treasure below
    case 8: {
      if (Rand(1, 2) == 1)
        strcpy(strTemp, "0000000000000000000000000000L001111111P001050000L01100"
                        "0000L010000000L01111111111");
      else
        strcpy(strTemp, "000000000000000000000L000000000P111111100L500000100L00"
                        "0000110L000000011111111111");
      break;
    }
    }
  } else if (roomPath == 4) { // shop
    strcpy(strTemp, "111111111111111111111111221111111l000211...000W010..."
                    "00000k0..Kiiii000bbbbbbbbbb");
    n = Rand(1, 7);
    // n = 6;
    switch (n) {
    case 1: {
      strcpy(shopType, "General");
      break;
    }
    case 2: {
      strcpy(shopType, "Bomb");
      break;
    }
    case 3: {
      strcpy(shopType, "Weapon");
      break;
    }
    case 4: {
      strcpy(shopType, "Rare");
      break;
    }
    case 5: {
      strcpy(shopType, "Clothing");
      break;
    }
    case 6: {
      strcpy(shopType, "Craps");
      strcpy(strTemp, "11111111111111111111111122111111Kl000211..bQ00W010.0+"
                      "00000k0.q+dd00000bbbbbbbbbb");
      break;
    }
    case 7: {
      strcpy(shopType, "Kissing");
      strcpy(strTemp, "111111111111111111111111221111111l000211...000W010..."
                      "00000k0..K00D0000bbbbbbbbbb");
      map->damsel = true;
      break;
    }
    }
  } else if (roomPath == 5) { // shop
    strcpy(strTemp, "111111111111111111111111221111112000l11101W0000...0k00000."
                    "..000iiiiK..bbbbbbbbbb");
    n = Rand(1, 7);
    // n = 6;
    switch (n) {
    case 1: {
      strcpy(shopType, "General");
      break;
    }
    case 2: {
      strcpy(shopType, "Bomb");
      break;
    }
    case 3: {
      strcpy(shopType, "Weapon");
      break;
    }
    case 4: {
      strcpy(shopType, "Rare");
      break;
    }
    case 5: {
      strcpy(shopType, "Clothing");
      break;
    }
    case 6: {
      strcpy(shopType, "Craps");
      strcpy(strTemp, "111111111111111111111111221111112000lK1101W0Q00b.."
                      "0k00000+0.00000dd+q.bbbbbbbbbb");
      break;
    }
    case 7: {
      strcpy(shopType, "Kissing");
      strcpy(strTemp, "111111111111111111111111221111112000l11101W0000..."
                      "0k00000...0000D00K..bbbbbbbbbb");
      map->damsel = true;
      break;
    }
    }
  } else if (roomPath == 8) { // snake pit
    switch (Rand(1, 1)) {
    case 1: {
      strcpy(strTemp, "111000011111s0000s11111200211111s0000s11111200211111s000"
                      "0s11111200211111s0000s11");
      break;
    }
    }
  } else if (roomPath == 9) { // snake pit bottom
    switch (Rand(1, 1)) {
    case 1: {
      strcpy(strTemp, "111000011111s0000s1111100001111100S0001111S0110S11111STT"
                      "S1111111M111111111111111");
      break;
    }
    }
  } else { // drop
    if (roomPath == 7)
      n = Rand(4, 12);
    else if (roomPathAbove != 2)
      n = Rand(1, 12);
    else
      n = Rand(1, 8);
    switch (n) {
    case 1: {
      strcpy(strTemp, "00000000006000060000000000000000000000006000060000000000"
                      "000000000000000000000000");
      break;
    }
    case 2: {
      strcpy(strTemp, "00000000006000060000000000000000000000000000050000000000"
                      "000000000000001202111111");
      break;
    }
    case 3: {
      strcpy(strTemp, "00000000006000060000000000000000000000050000000000000000"
                      "000000000000001111112021");
      break;
    }
    case 4: {
      strcpy(strTemp, "00000000006000060000000000000000000000000000000000000000"
                      "000002200002201112002111");
      break;
    }
    case 5: {
      strcpy(strTemp, "00000000000000220000000000000000200002000112002110011100"
                      "111012000000211111001111");
      break;
    }
    case 6: {
      strcpy(strTemp, "00000000000060000000000000000000000000000000000000001112"
                      "220002100000001110111111");
      break;
    }
    case 7: {
      strcpy(strTemp, "00000000000060000000000000000000000000000000000000002221"
                      "110000000001201111110111");
      break;
    }
    case 8: {
      strcpy(strTemp, "00000000000060000000000000000000000000000000000000002022"
                      "020000100001001111001111");
      break;
    }
    case 9: {
      strcpy(strTemp, "11111111112222222222000000000000000000000000000000000000"
                      "000000000000001120000211");
      break;
    }
    case 10: {
      strcpy(strTemp, "11111111112222111111000002211100000002110000000000200000"
                      "000000000000211120000211");
      break;
    }
    case 11: {
      strcpy(strTemp, "11111111111111112222111220000011200000000000000000000000"
                      "000012000000001120000211");
      break;
    }
    case 12: {
      strcpy(strTemp, "11111111112111111112021111112000211112000002112000000022"
                      "000002200002201111001111");
      break;
    }
    }
  }

  char strObs1[] = "00000";
  char strObs2[] = "00000";
  char strObs3[] = "00000";

  // Add obstacles
  for (i = 0; i < 80; i += 1) {
    j = i;

    strcpy(strObs1, "00000");
    strcpy(strObs2, "00000");
    strcpy(strObs3, "00000");

    char tile = strTemp[i];
    //				tile = string_char_at(strTemp, i);

    if (tile == '8') {
      switch (Rand(1, 8)) {
      case 1: {
        strcpy(strObs1, "00900");
        strcpy(strObs2, "01110");
        strcpy(strObs3, "11111");
        break;
      }
      case 2: {
        strcpy(strObs1, "00900");
        strcpy(strObs2, "02120");
        strcpy(strObs3, "02120");
        break;
      }
      case 3: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00000");
        strcpy(strObs3, "92222");
        break;
      }
      case 4: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00000");
        strcpy(strObs3, "22229");
        break;
      }
      case 5: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "11001");
        strcpy(strObs3, "19001");
        break;
      }
      case 6: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "10011");
        strcpy(strObs3, "10091");
        break;
      }
      case 7: {
        strcpy(strObs1, "11111");
        strcpy(strObs2, "10001");
        strcpy(strObs3, "40094");
        break;
      }
      case 8: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "12021");
        strcpy(strObs3, "12921");
        break;
      }
      }
    } else if (tile == '5') { // ground
      switch (Rand(1, 16)) {
      case 1: {
        strcpy(strObs1, "11111");
        strcpy(strObs2, "00000");
        strcpy(strObs3, "00000");
        break;
      }
      case 2: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "11110");
        strcpy(strObs3, "00000");
        break;
      }
      case 3: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "01111");
        strcpy(strObs3, "00000");
        break;
      }
      case 4: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00000");
        strcpy(strObs3, "11111");
        break;
      }
      case 5: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "20200");
        strcpy(strObs3, "17177");
        break;
      }
      case 6: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "02020");
        strcpy(strObs3, "71717");
        break;
      }
      case 7: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00202");
        strcpy(strObs3, "77171");
        break;
      }
      case 8: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "22200");
        strcpy(strObs3, "11100");
        break;
      }
      case 9: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "02220");
        strcpy(strObs3, "01110");
        break;
      }
      case 10: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00222");
        strcpy(strObs3, "00111");
        break;
      }
      case 11: {
        strcpy(strObs1, "11100");
        strcpy(strObs2, "22200");
        strcpy(strObs3, "00000");
        break;
      }
      case 12: {
        strcpy(strObs1, "01110");
        strcpy(strObs2, "02220");
        strcpy(strObs3, "00000");
        break;
      }
      case 13: {
        strcpy(strObs1, "00111");
        strcpy(strObs2, "00222");
        strcpy(strObs3, "00000");
        break;
      }
      case 14: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "02220");
        strcpy(strObs3, "21112");
        break;
      }
      case 15: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "20100");
        strcpy(strObs3, "77117");
        break;
      }
      case 16: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00102");
        strcpy(strObs3, "71177");
        break;
      }
      }
    } else if (tile == '6') { // air
      switch (Rand(1, 10)) {
      case 1: {
        strcpy(strObs1, "11111");
        strcpy(strObs2, "00000");
        strcpy(strObs3, "00000");
        break;
      }
      case 2: {
        strcpy(strObs1, "22222");
        strcpy(strObs2, "00000");
        strcpy(strObs3, "00000");
        break;
      }
      case 3: {
        strcpy(strObs1, "11100");
        strcpy(strObs2, "22200");
        strcpy(strObs3, "00000");
        break;
      }
      case 4: {
        strcpy(strObs1, "01110");
        strcpy(strObs2, "02220");
        strcpy(strObs3, "00000");
        break;
      }
      case 5: {
        strcpy(strObs1, "00111");
        strcpy(strObs2, "00222");
        strcpy(strObs3, "00000");
        break;
      }
      case 6: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "01110");
        strcpy(strObs3, "00000");
        break;
      }
      case 7: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "01110");
        strcpy(strObs3, "02220");
        break;
      }
      case 8: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "02220");
        strcpy(strObs3, "01110");
        break;
      }
      case 9: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "00220");
        strcpy(strObs3, "01111");
        break;
      }
      case 10: {
        strcpy(strObs1, "00000");
        strcpy(strObs2, "22200");
        strcpy(strObs3, "11100");
        break;
      }
      }
    }

    if (tile == '5' || tile == '6' || tile == '8') {
      strcpy(strTemp + j, strObs1);
      j += 10;
      strcpy(strTemp + j, strObs2);
      j += 10;
      strcpy(strTemp + j, strObs3);
    }
  }

  // Generate the tiles
  for (j = 0; j < 8; j += 1) {
    for (i = 1; i < 11; i += 1) {
      char tile = strTemp[(i + j * 10) - 1];
      int xpos = x + (i - 1);
      int ypos = y + j;
      map->map[xpos + ypos * (10 * 4)] = tile;
    }
  }
}

void scrRoomGen2(map_t *map, int x, int y) {}
void scrRoomGen3(map_t *map, int x, int y) {}
