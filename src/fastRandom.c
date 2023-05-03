#include "fastRandom.h"
#include "stdtypes.h"

/// Adopt from fast random number generator for .Net by
/// Colin Green, January 2005
///
/// September 4th 2005
///  Added NextBytesUnsafe() - commented out by default.
///  Fixed bug in Reinitialise() - y,z and w variables were not being reset.
///
/// Key points:
///  1) Based on a simple and fast xor-shift pseudo random number generator
///  (RNG) specified in: Marsaglia, George. (2003). Xorshift RNGs.
///  http://www.jstatsoft.org/v08/i14/xorshift.pdf
///
///  This particular implementation of xorshift has a period of 2^128-1. See the
///  above paper to see how this can be easily extened if you need a longer
///  period. At the time of writing I could find no information on the period of
///  System.Random for comparison.
///
///  2) Faster than System.Random. Up to 8x faster, depending on which methods
///  are called.
///
///  3) Direct replacement for System.Random. This class implements all of the
///  methods that System.Random does plus some additional methods. The like
///  named methods are functionally equivalent.
///
///  4) Allows fast re-initialisation with a seed, unlike System.Random which
///  accepts a seed at construction time which then executes a relatively
///  expensive initialisation routine. This provides a vast speed improvement if
///  you need to reset the pseudo-random number sequence many times, e.g. if you
///  want to re-generate the same sequence many times. An alternative might be
///  to cache random numbers in an array, but that approach is limited by memory
///  capacity and the fact that you may also want a large number of different
///  sequences cached. Each sequence can each be represented by a single seed
///  value (int) when using FastRandom.
///
///  Notes.
///  A further performance improvement can be obtained by declaring local
///  variables as static, thus avoiding re-allocation of variables on each call.
///  However care should be taken if multiple instances of FastRandom are in use
///  or if being used in a multi-threaded environment.
///

#define MAX_INT 2147483647
#define MAX_UINT 4294967295

float REAL_UNIT_INT = 1.0 / ((float)MAX_INT + 1.0);
float REAL_UNIT_UINT = 1.0 / ((float)MAX_UINT + 1.0);
long Y = 842502087, Z = 3579807591, W = 273326509;
int x, y, z, w;

void FastRandomInit(int seed) {
  // The only stipulation stated for the xorshift RNG is that at least one of
  // the seeds x,y,z,w is non-zero. We fulfill that requirement by only allowing
  // resetting of the x seed
  x = (int)seed;
  y = Y;
  z = Z;
  w = W;
}

int Next() {
  int t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;
  w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));

  // Handle the special case where the value int.MaxValue is generated. This is
  // outside of the range of permitted values, so we therefore call Next() to
  // try again.
  int rtn = w & 0x7FFFFFFF;
  if (rtn == 0x7FFFFFFF)
    return Next();
  return (int)rtn;
}

int NextUpper(int upperBound) {
  if (upperBound < 0) {
    // throw new ArgumentOutOfRangeException ("upperBound", upperBound,
    // "upperBound must be >=0");
  }

  int t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;
  // The explicit int cast before the first multiplication gives better
  // performance. See comments in NextFloat.
  return (int)((REAL_UNIT_INT *
                (int)(0x7FFFFFFF & (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8))))) *
               upperBound);
}

int NextLowerUpper(int lowerBound, int upperBound) {
  // if (lowerBound > upperBound)
  //     throw new ArgumentOutOfRangeException ("upperBound", upperBound,
  //     "upperBound must be >=lowerBound");

  int t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;

  // The explicit int cast before the first multiplication gives better
  // performance. See comments in NextFloat.
  int range = upperBound - lowerBound;
  if (range < 0) { // If range is <0 then an overflow has occured and must
                   // resort to using long integer arithmetic instead (slower).
    // We also must use all 32 bits of precision, instead of the normal 31,
    // which again is slower.
    return lowerBound + (int)((REAL_UNIT_UINT *
                               (float)(w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)))) *
                              (float)((long)upperBound - (long)lowerBound));
  }

  // 31 bits of precision will suffice if range<=int.MaxValue. This allows us to
  // cast to an int and gain a little more performance.
  return lowerBound + (int)((REAL_UNIT_INT *
                             (float)(int)(0x7FFFFFFF & (w = (w ^ (w >> 19)) ^
                                                            (t ^ (t >> 8))))) *
                            (float)range);
}

float NextFloat() {
  int t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;

  // Here we can gain a 2x speed improvement by generating a value that can be
  // cast to an int instead of the more easily available uint. If we then
  // explicitly cast to an int the compiler will then cast the int to a float
  // to perform the multiplication, this final cast is a lot faster than casting
  // from a uint to a float. The extra cast to an int is very fast (the
  // allocated bits remain the same) and so the overall effect of the extra cast
  // is a significant performance improvement.
  //
  // Also note that the loss of one bit of precision is equivalent to what
  // occurs within System.Random.
  return (REAL_UNIT_INT *
          (int)(0x7FFFFFFF & (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)))));
}

int NextUInt() {
  int t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;
  return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

int NextInt() {
  int t = (x ^ (x << 11));
  x = y;
  y = z;
  z = w;
  return (int)(0x7FFFFFFF & (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8))));
}

// Buffer 32 bits in bitBuffer, return 1 at a time, keep track of how many have
// been returned with bitBufferIdx.
int bitBuffer;
int bitMask = 1;

bool NextBool() {
  if (bitMask == 1) {
    // Generate 32 more bits.
    int t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    bitBuffer = w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));

    // Reset the bitMask that tells us which bit to read next.
    bitMask = 0x80000000;
    return (bitBuffer & bitMask) == 0;
  }

  return (bitBuffer & (bitMask >>= 1)) == 0;
}