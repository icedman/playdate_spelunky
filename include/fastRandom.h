#ifndef _FAST_RANDOM_H_
#define _FAST_RANDOM_H_

#include "stdtypes.h"

void FastRandomInit(int seed);
int Next();
int NextUpper(int upperBound);
int NextLowerUpper(int lowerBound, int upperBound);
float NextFloat();
int NextUInt();
int NextInt();
bool NextBool();

#endif // _FAST_RANDOM_H_