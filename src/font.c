#include "font.h"
#include <ctype.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>

#define P(x, y) (((x)&0xF) << 4) | (((y)&0xF) << 0)
#define C(c) ord(c)

int fnt[255][8];

void FontInit() {
  int _C0[8] = {P(0, 0), P(8, 0),  P(8, 12), P(0, 12),
                P(0, 0), P(8, 12), FONT_LAST};
  memcpy(fnt['0' - 0x20], _C0, sizeof(int) * 8);
  int _C1[8] = {P(4, 0), P(4, 12), P(3, 10), FONT_LAST};
  memcpy(fnt['1' - 0x20], _C1, sizeof(int) * 8);
  int _C2[8] = {P(0, 12), P(8, 12), P(8, 7),  P(0, 5),
                P(0, 0),  P(8, 0),  FONT_LAST};
  memcpy(fnt['2' - 0x20], _C2, sizeof(int) * 8);
  int _C3[8] = {P(0, 12), P(8, 12), P(8, 0), P(0, 0),
                FONT_UP,  P(0, 6),  P(8, 6), FONT_LAST};
  memcpy(fnt['3' - 0x20], _C3, sizeof(int) * 8);
  int _C4[8] = {P(0, 12), P(0, 6), P(8, 6),  FONT_UP,
                P(8, 12), P(8, 0), FONT_LAST};
  memcpy(fnt['4' - 0x20], _C4, sizeof(int) * 8);
  int _C5[8] = {P(0, 0),  P(8, 0),  P(8, 6),  P(0, 7),
                P(0, 12), P(8, 12), FONT_LAST};
  memcpy(fnt['5' - 0x20], _C5, sizeof(int) * 8);
  int _C6[8] = {P(0, 12), P(0, 0), P(8, 0), P(8, 5), P(0, 7), FONT_LAST};
  memcpy(fnt['6' - 0x20], _C6, sizeof(int) * 8);
  int _C7[8] = {P(0, 12), P(8, 12), P(8, 6), P(4, 0), FONT_LAST};
  memcpy(fnt['7' - 0x20], _C7, sizeof(int) * 8);
  int _C8[8] = {P(0, 0), P(8, 0), P(8, 12), P(0, 12),
                P(0, 0), FONT_UP, P(0, 6),  P(8, 6)};
  memcpy(fnt['8' - 0x20], _C8, sizeof(int) * 8);
  int _C9[8] = {P(8, 0), P(8, 12), P(0, 12), P(0, 7), P(8, 5), FONT_LAST};
  memcpy(fnt['9' - 0x20], _C9, sizeof(int) * 8);
  int _C10[8] = {FONT_LAST};
  memcpy(fnt[' ' - 0x20], _C10, sizeof(int) * 8);
  int _C11[8] = {P(3, 0), P(4, 0), FONT_LAST};
  memcpy(fnt['.' - 0x20], _C11, sizeof(int) * 8);
  int _C12[8] = {P(2, 0), P(4, 2), FONT_LAST};
  memcpy(fnt[',' - 0x20], _C12, sizeof(int) * 8);
  int _C13[8] = {P(2, 6), P(6, 6), FONT_LAST};
  memcpy(fnt['-' - 0x20], _C13, sizeof(int) * 8);
  int _C14[8] = {P(1, 6), P(7, 6), FONT_UP, P(4, 9), P(4, 3), FONT_LAST};
  memcpy(fnt['+' - 0x20], _C14, sizeof(int) * 8);
  int _C15[8] = {P(4, 0), P(3, 2), P(5, 2),  P(4, 0),
                 FONT_UP, P(4, 4), P(4, 12), FONT_LAST};
  memcpy(fnt['!' - 0x20], _C15, sizeof(int) * 8);
  int _C16[8] = {P(0, 4), P(8, 4), P(6, 2),  P(6, 10),
                 P(8, 8), P(0, 8), P(2, 10), P(2, 2)};
  memcpy(fnt['#' - 0x20], _C16, sizeof(int) * 8);
  int _C17[8] = {P(2, 6), P(4, 12), P(6, 6), FONT_LAST};
  memcpy(fnt['^' - 0x20], _C17, sizeof(int) * 8);
  int _C18[8] = {P(1, 4), P(7, 4), FONT_UP, P(1, 8), P(7, 8), FONT_LAST};
  memcpy(fnt['=' - 0x20], _C18, sizeof(int) * 8);
  int _C19[8] = {P(0, 0), P(4, 12), P(8, 0),  P(0, 8),
                 P(8, 8), P(0, 0),  FONT_LAST};
  memcpy(fnt['*' - 0x20], _C19, sizeof(int) * 8);
  int _C20[8] = {P(0, 0), P(8, 0), FONT_LAST};
  memcpy(fnt['_' - 0x20], _C20, sizeof(int) * 8);
  int _C21[8] = {P(0, 0), P(8, 12), FONT_LAST};
  memcpy(fnt['/' - 0x20], _C21, sizeof(int) * 8);
  int _C22[8] = {P(0, 12), P(8, 0), FONT_LAST};
  memcpy(fnt['\\' - 0x20], _C22, sizeof(int) * 8);
  int _C23[8] = {P(8, 4),  P(4, 0), P(0, 4), P(0, 8),
                 P(4, 12), P(8, 8), P(4, 4), P(3, 6)};
  memcpy(fnt['@' - 0x20], _C23, sizeof(int) * 8);
  int _C24[8] = {P(6, 2),  P(2, 6), P(6, 10), FONT_UP,
                 P(4, 12), P(4, 0), FONT_LAST};
  memcpy(fnt['$' - 0x20], _C24, sizeof(int) * 8);
  int _C25[8] = {P(8, 0), P(4, 12), P(8, 8),  P(0, 4),
                 P(4, 0), P(8, 4),  FONT_LAST};
  memcpy(fnt['&' - 0x20], _C25, sizeof(int) * 8);
  int _C26[8] = {P(6, 0), P(2, 0), P(2, 12), P(6, 12), FONT_LAST};
  memcpy(fnt['[' - 0x20], _C26, sizeof(int) * 8);
  int _C27[8] = {P(2, 0), P(6, 0), P(6, 12), P(2, 12), FONT_LAST};
  memcpy(fnt[']' - 0x20], _C27, sizeof(int) * 8);
  int _C28[8] = {P(6, 0), P(2, 4), P(2, 8), P(6, 12), FONT_LAST};
  memcpy(fnt['(' - 0x20], _C28, sizeof(int) * 8);
  int _C29[8] = {P(2, 0), P(6, 4), P(6, 8), P(2, 12), FONT_LAST};
  memcpy(fnt[')' - 0x20], _C29, sizeof(int) * 8);
  int _C30[8] = {P(6, 0), P(4, 2), P(4, 10), P(6, 12),
                 FONT_UP, P(2, 6), P(4, 6),  FONT_LAST};
  memcpy(fnt['{' - 0x20], _C30, sizeof(int) * 8);
  int _C31[8] = {P(4, 0), P(6, 2), P(6, 10), P(4, 12),
                 FONT_UP, P(6, 6), P(8, 6),  FONT_LAST};
  memcpy(fnt['}' - 0x20], _C31, sizeof(int) * 8);
  int _C32[8] = {P(0, 0), P(8, 12), FONT_UP, P(2, 10),
                 P(2, 8), FONT_UP,  P(6, 4), P(6, 2)};
  memcpy(fnt['%' - 0x20], _C32, sizeof(int) * 8);
  int _C33[8] = {P(6, 0), P(2, 6), P(6, 12), FONT_LAST};
  memcpy(fnt['<' - 0x20], _C33, sizeof(int) * 8);
  int _C34[8] = {P(2, 0), P(6, 6), P(2, 12), FONT_LAST};
  memcpy(fnt['>' - 0x20], _C34, sizeof(int) * 8);
  int _C35[8] = {P(4, 0), P(4, 5), FONT_UP, P(4, 6), P(4, 12), FONT_LAST};
  memcpy(fnt['|' - 0x20], _C35, sizeof(int) * 8);
  int _C36[8] = {P(4, 9), P(4, 7), FONT_UP, P(4, 5), P(4, 3), FONT_LAST};
  memcpy(fnt[':' - 0x20], _C36, sizeof(int) * 8);
  int _C37[8] = {P(4, 9), P(4, 7), FONT_UP, P(4, 5), P(1, 2), FONT_LAST};
  memcpy(fnt[';' - 0x20], _C37, sizeof(int) * 8);
  int _C38[8] = {P(2, 10), P(2, 6), FONT_UP, P(6, 10), P(6, 6), FONT_LAST};
  memcpy(fnt['"' - 0x20], _C38, sizeof(int) * 8);
  int _C39[8] = {P(2, 6), P(6, 10), FONT_LAST};
  memcpy(fnt['\'' - 0x20], _C39, sizeof(int) * 8);
  int _C40[8] = {P(2, 10), P(6, 6), FONT_LAST};
  memcpy(fnt['`' - 0x20], _C40, sizeof(int) * 8);
  int _C41[8] = {P(0, 4), P(2, 8), P(6, 4), P(8, 8), FONT_LAST};
  memcpy(fnt['~' - 0x20], _C41, sizeof(int) * 8);
  int _C42[8] = {P(0, 8), P(4, 12), P(8, 8), P(4, 4),
                 FONT_UP, P(4, 1),  P(4, 0), FONT_LAST};
  memcpy(fnt['?' - 0x20], _C42, sizeof(int) * 8);
  int _C43[8] = {P(0, 0), P(0, 8), P(4, 12), P(8, 8),
                 P(8, 0), FONT_UP, P(0, 4),  P(8, 4)};
  memcpy(fnt['A' - 0x20], _C43, sizeof(int) * 8);
  int _C44[8] = {P(0, 0), P(0, 12), P(4, 12), P(8, 10),
                 P(4, 6), P(8, 2),  P(4, 0),  P(0, 0)};
  memcpy(fnt['B' - 0x20], _C44, sizeof(int) * 8);
  int _C45[8] = {P(8, 0), P(0, 0), P(0, 12), P(8, 12), FONT_LAST};
  memcpy(fnt['C' - 0x20], _C45, sizeof(int) * 8);
  int _C46[8] = {P(0, 0), P(0, 12), P(4, 12), P(8, 8),
                 P(8, 4), P(4, 0),  P(0, 0),  FONT_LAST};
  memcpy(fnt['D' - 0x20], _C46, sizeof(int) * 8);
  int _C47[8] = {P(8, 0), P(0, 0), P(0, 12), P(8, 12),
                 FONT_UP, P(0, 6), P(6, 6),  FONT_LAST};
  memcpy(fnt['E' - 0x20], _C47, sizeof(int) * 8);
  int _C48[8] = {P(0, 0), P(0, 12), P(8, 12), FONT_UP,
                 P(0, 6), P(6, 6),  FONT_LAST};
  memcpy(fnt['F' - 0x20], _C48, sizeof(int) * 8);
  int _C49[8] = {P(6, 6),  P(8, 4),  P(8, 0),  P(0, 0),
                 P(0, 12), P(8, 12), FONT_LAST};
  memcpy(fnt['G' - 0x20], _C49, sizeof(int) * 8);
  int _C50[8] = {P(0, 0), P(0, 12), FONT_UP,  P(0, 6),
                 P(8, 6), FONT_UP,  P(8, 12), P(8, 0)};
  memcpy(fnt['H' - 0x20], _C50, sizeof(int) * 8);
  int _C51[8] = {P(0, 0),  P(8, 0), FONT_UP,  P(4, 0),
                 P(4, 12), FONT_UP, P(0, 12), P(8, 12)};
  memcpy(fnt['I' - 0x20], _C51, sizeof(int) * 8);
  int _C52[8] = {P(0, 4), P(4, 0), P(8, 0), P(8, 12), FONT_LAST};
  memcpy(fnt['J' - 0x20], _C52, sizeof(int) * 8);
  int _C53[8] = {P(0, 0), P(0, 12), FONT_UP,  P(8, 12),
                 P(0, 6), P(6, 0),  FONT_LAST};
  memcpy(fnt['K' - 0x20], _C53, sizeof(int) * 8);
  int _C54[8] = {P(8, 0), P(0, 0), P(0, 12), FONT_LAST};
  memcpy(fnt['L' - 0x20], _C54, sizeof(int) * 8);
  int _C55[8] = {P(0, 0), P(0, 12), P(4, 8), P(8, 12), P(8, 0), FONT_LAST};
  memcpy(fnt['M' - 0x20], _C55, sizeof(int) * 8);
  int _C56[8] = {P(0, 0), P(0, 12), P(8, 0), P(8, 12), FONT_LAST};
  memcpy(fnt['N' - 0x20], _C56, sizeof(int) * 8);
  int _C57[8] = {P(0, 0), P(0, 12), P(8, 12), P(8, 0), P(0, 0), FONT_LAST};
  memcpy(fnt['O' - 0x20], _C57, sizeof(int) * 8);
  int _C58[8] = {P(0, 0), P(0, 12), P(8, 12), P(8, 6), P(0, 5), FONT_LAST};
  memcpy(fnt['P' - 0x20], _C58, sizeof(int) * 8);
  int _C59[8] = {P(0, 0), P(0, 12), P(8, 12), P(8, 4),
                 P(0, 0), FONT_UP,  P(4, 4),  P(8, 0)};
  memcpy(fnt['Q' - 0x20], _C59, sizeof(int) * 8);
  int _C60[8] = {P(0, 0), P(0, 12), P(8, 12), P(8, 6),
                 P(0, 5), FONT_UP,  P(4, 5),  P(8, 0)};
  memcpy(fnt['R' - 0x20], _C60, sizeof(int) * 8);
  int _C61[8] = {P(0, 2), P(2, 0),  P(8, 0),  P(8, 5),
                 P(0, 7), P(0, 12), P(6, 12), P(8, 10)};
  memcpy(fnt['S' - 0x20], _C61, sizeof(int) * 8);
  int _C62[8] = {P(0, 12), P(8, 12), FONT_UP, P(4, 12), P(4, 0), FONT_LAST};
  memcpy(fnt['T' - 0x20], _C62, sizeof(int) * 8);
  int _C63[8] = {P(0, 12), P(0, 2), P(4, 0), P(8, 2), P(8, 12), FONT_LAST};
  memcpy(fnt['U' - 0x20], _C63, sizeof(int) * 8);
  int _C64[8] = {P(0, 12), P(4, 0), P(8, 12), FONT_LAST};
  memcpy(fnt['V' - 0x20], _C64, sizeof(int) * 8);
  int _C65[8] = {P(0, 12), P(2, 0), P(4, 4), P(6, 0), P(8, 12), FONT_LAST};
  memcpy(fnt['W' - 0x20], _C65, sizeof(int) * 8);
  int _C66[8] = {P(0, 0), P(8, 12), FONT_UP, P(0, 12), P(8, 0), FONT_LAST};
  memcpy(fnt['X' - 0x20], _C66, sizeof(int) * 8);
  int _C67[8] = {P(0, 12), P(4, 6), P(8, 12), FONT_UP,
                 P(4, 6),  P(4, 0), FONT_LAST};
  memcpy(fnt['Y' - 0x20], _C67, sizeof(int) * 8);
  int _C68[8] = {P(0, 12), P(8, 12), P(0, 0), P(8, 0),
                 FONT_UP,  P(2, 6),  P(6, 6), FONT_LAST};
  memcpy(fnt['Z' - 0x20], _C68, sizeof(int) * 8);
}

int *FontCharPoints(char c) { return fnt[toupper(c) - ' ']; }