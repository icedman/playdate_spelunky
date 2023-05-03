#ifndef _FONT_H_
#define _FONT_H_

#include "stdtypes.h"

#define FONT_UP 0xFE
#define FONT_LAST 0xFF

void FontInit();
int *FontCharPoints(char c);

#endif // _FONT_H_
