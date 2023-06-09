/*
 * This is a collection of Playdate patterns compiled into a header-only library
 * for use in C SDK projects.
 *
 * The pattern definitions listed here are copied directly from Ivan Sergeev's
 * 'gfxp' library, which can be found here: https://github.com/ivansergeev/gfxp
 *
 *
 * USAGE:
 *
 *    // In EXACTLY ONE unit file, define PATTERN_IMPLEMENTATION prior to
 *    // including pattern.h
 *
 *    // Pass a pattern identifier to the get_pattern function, which will
 *    // return the corresponding pattern as an LCDColor value
 *
 *    // Pattern identifiers are defined in the pattern_t enum, which can be
 *    // found below
 *
 *    #define PATTERN_IMPLEMENTATION
 *    #include "pattern.h"
 *
 *    PlaydateAPI* pd = ...
 *    pd->graphics->clear(get_pattern(heart_1)); // or get_pattern_inverse
 */

#ifndef PATTERN_H
#define PATTERN_H

#include <pd_api.h>

typedef enum {
  white = 0,
  black,
  lightgray,
  lightgray_1,
  lightgray_2,
  gray,
  gray_1,
  gray_2,
  gray_3,
  gray_4,
  gray_5,
  darkgray,
  darkgray_1,
  darkgray_2,
  dot_1,
  dot_2,
  dot_3,
  dot_4,
  dot_5,
  dot_6,
  dot_7,
  dot_8,
  dot_9,
  dot_10,
  dot_11,
  dot_12,
  dot_13,
  dot_14,
  dot_15,
  dot_16,
  dot_17,
  dot_18,
  cross_1,
  cross_2,
  cross_3,
  cross_4,
  cross_5,
  vline_1,
  vline_2,
  vline_3,
  vline_4,
  vline_5,
  hline_1,
  hline_2,
  hline_3,
  hline_4,
  hline_5,
  hline_6,
  dline_1,
  dline_2,
  dline_3,
  dline_4,
  dline_5,
  dline_6,
  dline_7,
  dline_8,
  wave_1,
  wave_2,
  wave_3,
  grid_1,
  grid_2,
  grid_3,
  grid_4,
  grid_5,
  grid_6,
  rect_1,
  rect_2,
  rect_3,
  brick_1,
  brick_2,
  brick_3,
  brick_4,
  brick_5,
  brick_6,
  brick_7,
  brick_8,
  brick_9,
  brick_10,
  brick_11,
  flake_1,
  flake_2,
  flake_3,
  flake_4,
  flake_5,
  flake_6,
  flake_7,
  flake_8,
  flake_9,
  flake_10,
  decor_1,
  decor_2,
  decor_3,
  decor_4,
  decor_5,
  decor_6,
  decor_7,
  decor_8,
  decor_9,
  decor_10,
  decor_11,
  decor_12,
  decor_13,
  decor_14,
  decor_15,
  decor_16,
  decor_17,
  decor_18,
  decor_19,
  decor_20,
  decor_21,
  decor_22,
  decor_23,
  decor_24,
  decor_25,
  decor_26,
  noise_1,
  noise_2,
  noise_3,
  noise_4,
  noise_5,
  noise_6,
  noise_7,
  emoji,
  emoji_smile,
  emoji_fun,
  emoji_surprise,
  emoji_sad,
  emoji_scream,
  emoji_angry,
  emoji_pirate,
  emoji_skull,
  emoji_alien,
  heart_1,
  heart_2,
  pacman_1,
  tree_1
} pattern_t;

extern LCDColor get_pattern(pattern_t p);
extern LCDColor get_pattern_inverse(pattern_t p);

#ifdef PATTERN_IMPLEMENTATION

// clang-format off
static const LCDPattern _patterns[] = {
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xdd, 0xff, 0x77, 0xff, 0xdd, 0xff, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0x77, 0xdd, 0xdd, 0x77, 0x77, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0x77, 0x77, 0x77, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x33, 0x33, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0xaa, 0x55, 0x55, 0xaa, 0xaa, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xd2, 0x5a, 0x4b, 0x69, 0x2d, 0xa5, 0xb4, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x22, 0x00, 0x88, 0x00, 0x22, 0x00, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x88, 0x22, 0x22, 0x88, 0x88, 0x22, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x88, 0x88, 0x88, 0x22, 0x22, 0x22, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x3f, 0x3f, 0xff, 0xff, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x66, 0xff, 0xff, 0x66, 0x66, 0xff, 0xff, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x1f, 0x5f, 0x1f, 0xff, 0xf1, 0xf5, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x0f, 0x6f, 0x6f, 0x0f, 0xf0, 0xf6, 0xf6, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xff, 0xe7, 0xdb, 0xdb, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0xaa, 0x55, 0x55, 0xba, 0xba, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xab, 0xab, 0x55, 0x55, 0xba, 0xba, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0xaa, 0x41, 0x9c, 0x5d, 0x9c, 0x41, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x9f, 0x6f, 0x6f, 0x9f, 0xf9, 0xf6, 0xf6, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xe3, 0xdd, 0xbe, 0xbe, 0xbe, 0xdd, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xe3, 0xc1, 0x80, 0x80, 0x80, 0xc1, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xe7, 0xc3, 0x99, 0x99, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xbb, 0xf5, 0xf5, 0xf5, 0xb5, 0x5b, 0x5f, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xbd, 0x5a, 0xa5, 0xdb, 0xdb, 0xa5, 0x5a, 0xbd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x5a, 0xa5, 0x5a, 0xa5, 0xa5, 0x5a, 0xa5, 0x5a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xb6, 0x6b, 0xf7, 0xdf, 0xad, 0xda, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xff, 0xff, 0x77, 0xaf, 0xdf, 0xaf, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xbe, 0xdd, 0xeb, 0xf7, 0xeb, 0xdd, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0xaa, 0x55, 0xbe, 0x5d, 0xbe, 0x55, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xdd, 0xaa, 0xd5, 0xeb, 0xd5, 0xaa, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfe, 0x38, 0xfe, 0xee, 0xef, 0x83, 0xef, 0xee, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x6d, 0x6d, 0x6d, 0x6d, 0x6d, 0x6d, 0x6d, 0x6d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xf7, 0xf7, 0xf7, 0xf7, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x14, 0xff, 0xa2, 0xff, 0x14, 0xff, 0xa2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x0f, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0xbb, 0xdd, 0xee, 0x77, 0xbb, 0xdd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xff, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfc, 0x7e, 0x3f, 0x9f, 0xcf, 0xe7, 0xf3, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xf8, 0x7c, 0x3e, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xee, 0xdd, 0xbb, 0x77, 0xee, 0xdd, 0xbb, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0xbb, 0xdd, 0xee, 0x77, 0xbb, 0xdd, 0xee, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xbb, 0xdd, 0xee, 0x77, 0xee, 0xdd, 0xbb, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xb7, 0x7b, 0xfc, 0xcf, 0xb7, 0x7b, 0xfc, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe7, 0xdb, 0xdb, 0xdb, 0xdb, 0xbd, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0x77, 0xaa, 0xdd, 0xaa, 0x77, 0xaa, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x6d, 0x6d, 0x00, 0x6d, 0x6d, 0x00, 0x6d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe7, 0xdb, 0xbd, 0x7e, 0x7e, 0xbd, 0xdb, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xaa, 0xd5, 0xaa, 0xd5, 0xaa, 0xd5, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x80, 0xbe, 0xbe, 0xbe, 0xbe, 0xbe, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x81, 0xbd, 0xbd, 0xbd, 0xbd, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x20, 0xaf, 0xaf, 0xaf, 0xaf, 0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xdf, 0xdf, 0xdf, 0x00, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x00, 0xcf, 0xcf, 0x00, 0x00, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x77, 0x00, 0xdd, 0x00, 0x77, 0x00, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7e, 0xbd, 0xdb, 0xe7, 0xf7, 0xfb, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7e, 0xbd, 0xdb, 0xe7, 0xef, 0xdf, 0xbf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0xbb, 0xdd, 0xee, 0x55, 0xbb, 0xdd, 0xee, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0xdd, 0xbb, 0x77, 0xaa, 0xdd, 0xbb, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x5f, 0xae, 0x57, 0xab, 0xd5, 0xea, 0xf5, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfa, 0x75, 0xea, 0xd5, 0xab, 0x57, 0xaf, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x5f, 0xee, 0x77, 0xbb, 0xdd, 0xee, 0xf5, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfa, 0x77, 0xee, 0xdd, 0xbb, 0x77, 0xaf, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7e, 0xbd, 0xc3, 0xfb, 0xfb, 0xfb, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7e, 0xbd, 0xc3, 0xdf, 0xdf, 0xdf, 0xbf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfe, 0x3d, 0xc3, 0xfb, 0xfb, 0xfb, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xbc, 0xc3, 0xdf, 0xdf, 0xdf, 0xbf, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7d, 0xbb, 0xcb, 0xf7, 0xcb, 0xbb, 0x7d, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe1, 0xde, 0xbe, 0x7f, 0x7f, 0x7f, 0x9f, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7e, 0xbd, 0xbb, 0xb7, 0x8f, 0xef, 0xe1, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xf7, 0xf7, 0xeb, 0x9c, 0x7f, 0x7f, 0xbe, 0xc9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfe, 0x3d, 0xcb, 0xf7, 0xfb, 0xfb, 0xfd, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xae, 0xd5, 0xbb, 0xdf, 0xef, 0xdf, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x1f, 0x37, 0x73, 0xf1, 0xf1, 0x73, 0x37, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xf8, 0xec, 0xce, 0x8f, 0x8f, 0xce, 0xec, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xe7, 0xe7, 0x99, 0x99, 0xe7, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0xa3, 0xdd, 0xbb, 0x77, 0xf0, 0xf7, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xb6, 0x6b, 0xbd, 0x6a, 0xb7, 0x55, 0xbe, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x6d, 0xb6, 0x6b, 0xdd, 0xaa, 0x77, 0xb5, 0xda, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xad, 0xd6, 0x6b, 0xb5, 0xda, 0x56, 0xad, 0xda, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe7, 0xdb, 0xbd, 0xa5, 0xbd, 0xdb, 0xb5, 0x6e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe3, 0xdd, 0xb6, 0xa5, 0xbd, 0xdb, 0x52, 0xbd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0xad, 0xda, 0x77, 0xad, 0xda, 0x77, 0xad, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x66, 0xdb, 0xbd, 0x66, 0x66, 0xbd, 0xdb, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0xaa, 0xff, 0x20, 0xef, 0x28, 0xeb, 0x2a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x81, 0xbd, 0xa5, 0xa5, 0xbd, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xb6, 0x6d, 0xdb, 0xb6, 0x6d, 0xdb, 0xb6, 0x6d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7f, 0x40, 0x5f, 0x51, 0x55, 0x5d, 0x41, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x66, 0xbd, 0xc3, 0x7e, 0x7e, 0xc3, 0xbd, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xcf, 0x9f, 0x3f, 0x6e, 0xe7, 0xf1, 0xf8, 0xee, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x1e, 0xee, 0xc2, 0xd9, 0x9b, 0x43, 0x77, 0x78, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x9d, 0x66, 0xda, 0xbd, 0xbd, 0x5b, 0x66, 0xb9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x55, 0xff, 0xdd, 0xff, 0x57, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x99, 0x7e, 0x66, 0xdb, 0xdb, 0x66, 0x7e, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x7e, 0xbd, 0xc3, 0xdb, 0xdb, 0xc3, 0xbd, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0xba, 0x65, 0xca, 0x95, 0xaa, 0x55, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xab, 0x77, 0xfa, 0x7d, 0xbe, 0x5f, 0xee, 0xd5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xeb, 0xf7, 0xeb, 0xdd, 0xbe, 0x7f, 0x7f, 0x9c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xee, 0xd7, 0xbb, 0x6d, 0xb6, 0xdd, 0xeb, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfb, 0xdf, 0x7d, 0xef, 0xff, 0xbb, 0xef, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xf7, 0xbe, 0xff, 0xef, 0xff, 0xfd, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xfb, 0x7f, 0xdd, 0xef, 0x7e, 0xf7, 0xbe, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xbb, 0x7d, 0xef, 0xbe, 0xdf, 0xf7, 0xbe, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xeb, 0xbe, 0xf7, 0xba, 0xdf, 0xb6, 0xfb, 0x6d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x66, 0x99, 0xa5, 0x5a, 0x5a, 0xa5, 0x99, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x5c, 0x5c, 0xea, 0xea, 0x47, 0x47, 0xaa, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x7e, 0x5a, 0x7e, 0x66, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x7e, 0x5a, 0x66, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x7e, 0x42, 0x66, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x7e, 0x66, 0x66, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x7e, 0x66, 0x5a, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x7e, 0x42, 0x42, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x7e, 0x42, 0x5a, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x34, 0x4e, 0x4a, 0x3e, 0x66, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x7e, 0x5a, 0x7e, 0x24, 0x3c, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x3c, 0x5a, 0x5a, 0x7e, 0x24, 0x18, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc9, 0xb6, 0xbe, 0xdd, 0xeb, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc9, 0x80, 0x80, 0xc1, 0xe3, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xe3, 0xdd, 0xbb, 0xb7, 0xbb, 0xdd, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xf7, 0xeb, 0xf7, 0xc9, 0xf7, 0x88, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};

static const LCDPattern _inverse[] = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x22, 0x00, 0x88, 0x00, 0x22, 0x00, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x88, 0x22, 0x22, 0x88, 0x88, 0x22, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x88, 0x88, 0x88, 0x22, 0x22, 0x22, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xcc, 0xcc, 0xcc, 0xcc, 0x33, 0x33, 0x33, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x55, 0xaa, 0xaa, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x2d, 0xa5, 0xb4, 0x96, 0xd2, 0x5a, 0x4b, 0x69, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xdd, 0xff, 0x77, 0xff, 0xdd, 0xff, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0x77, 0xdd, 0xdd, 0x77, 0x77, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x77, 0x77, 0x77, 0x77, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xc0, 0xc0, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x99, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe0, 0xa0, 0xe0, 0x00, 0x0e, 0x0a, 0x0e, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xf0, 0x90, 0x90, 0xf0, 0x0f, 0x09, 0x09, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x55, 0xaa, 0xaa, 0x45, 0x45, 0xaa, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x54, 0x54, 0xaa, 0xaa, 0x45, 0x45, 0xaa, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0x55, 0xbe, 0x63, 0xa2, 0x63, 0xbe, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x60, 0x90, 0x90, 0x60, 0x06, 0x09, 0x09, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x1c, 0x22, 0x41, 0x41, 0x41, 0x22, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x1c, 0x3e, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x18, 0x3c, 0x66, 0x66, 0x3c, 0x18, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x44, 0x0a, 0x0a, 0x0a, 0x4a, 0xa4, 0xa0, 0xa0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x42, 0xa5, 0x5a, 0x24, 0x24, 0x5a, 0xa5, 0x42, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xa5, 0x5a, 0xa5, 0x5a, 0x5a, 0xa5, 0x5a, 0xa5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x49, 0x94, 0x08, 0x20, 0x52, 0x25, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0x55, 0xaa, 0x41, 0xa2, 0x41, 0xaa, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x22, 0x55, 0x2a, 0x14, 0x2a, 0x55, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x01, 0xc7, 0x01, 0x11, 0x10, 0x7c, 0x10, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x08, 0x08, 0x08, 0x08, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xeb, 0x00, 0x5d, 0x00, 0xeb, 0x00, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xf0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x44, 0x22, 0x11, 0x88, 0x44, 0x22, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x03, 0x81, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x07, 0x83, 0xc1, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x44, 0x22, 0x11, 0x88, 0x44, 0x22, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x44, 0x22, 0x11, 0x88, 0x11, 0x22, 0x44, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x48, 0x84, 0x03, 0x30, 0x48, 0x84, 0x03, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x18, 0x24, 0x24, 0x24, 0x24, 0x42, 0x81, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x88, 0x55, 0x22, 0x55, 0x88, 0x55, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x88, 0x88, 0x88, 0xff, 0x88, 0x88, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x92, 0x92, 0xff, 0x92, 0x92, 0xff, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x55, 0x2a, 0x55, 0x2a, 0x55, 0x2a, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x7f, 0x41, 0x41, 0x41, 0x41, 0x41, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xdf, 0x50, 0x50, 0x50, 0x50, 0xdf, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x20, 0x20, 0x20, 0xff, 0x02, 0x02, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xff, 0x30, 0x30, 0xff, 0xff, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0x88, 0xff, 0x22, 0xff, 0x88, 0xff, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x81, 0x42, 0x24, 0x18, 0x08, 0x04, 0x02, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x81, 0x42, 0x24, 0x18, 0x10, 0x20, 0x40, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0x44, 0x22, 0x11, 0xaa, 0x44, 0x22, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x22, 0x44, 0x88, 0x55, 0x22, 0x44, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xa0, 0x51, 0xa8, 0x54, 0x2a, 0x15, 0x0a, 0x44, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x05, 0x8a, 0x15, 0x2a, 0x54, 0xa8, 0x50, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xa0, 0x11, 0x88, 0x44, 0x22, 0x11, 0x0a, 0x44, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x05, 0x88, 0x11, 0x22, 0x44, 0x88, 0x50, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x81, 0x42, 0x3c, 0x04, 0x04, 0x04, 0x02, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x81, 0x42, 0x3c, 0x20, 0x20, 0x20, 0x40, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x01, 0xc2, 0x3c, 0x04, 0x04, 0x04, 0x02, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x43, 0x3c, 0x20, 0x20, 0x20, 0x40, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x82, 0x44, 0x34, 0x08, 0x34, 0x44, 0x82, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x1e, 0x21, 0x41, 0x80, 0x80, 0x80, 0x60, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x81, 0x42, 0x44, 0x48, 0x70, 0x10, 0x1e, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x08, 0x08, 0x14, 0x63, 0x80, 0x80, 0x41, 0x36, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x01, 0xc2, 0x34, 0x08, 0x04, 0x04, 0x02, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x51, 0x2a, 0x44, 0x20, 0x10, 0x20, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe0, 0xc8, 0x8c, 0x0e, 0x0e, 0x8c, 0xc8, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x07, 0x13, 0x31, 0x70, 0x70, 0x31, 0x13, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x18, 0x18, 0x66, 0x66, 0x18, 0x18, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0x5c, 0x22, 0x44, 0x88, 0x0f, 0x08, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x49, 0x94, 0x42, 0x95, 0x48, 0xaa, 0x41, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x92, 0x49, 0x94, 0x22, 0x55, 0x88, 0x4a, 0x25, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x52, 0x29, 0x94, 0x4a, 0x25, 0xa9, 0x52, 0x25, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x18, 0x24, 0x42, 0x5a, 0x42, 0x24, 0x4a, 0x91, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x1c, 0x22, 0x49, 0x5a, 0x42, 0x24, 0xad, 0x42, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x88, 0x52, 0x25, 0x88, 0x52, 0x25, 0x88, 0x52, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x99, 0x24, 0x42, 0x99, 0x99, 0x42, 0x24, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x55, 0x55, 0x00, 0xdf, 0x10, 0xd7, 0x14, 0xd5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x7e, 0x42, 0x5a, 0x5a, 0x42, 0x7e, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x80, 0xbf, 0xa0, 0xae, 0xaa, 0xa2, 0xbe, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x99, 0x42, 0x3c, 0x81, 0x81, 0x3c, 0x42, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x30, 0x60, 0xc0, 0x91, 0x18, 0x0e, 0x07, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xe1, 0x11, 0x3d, 0x26, 0x64, 0xbc, 0x88, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x62, 0x99, 0x25, 0x42, 0x42, 0xa4, 0x99, 0x46, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0xaa, 0x00, 0x22, 0x00, 0xa8, 0x00, 0x22, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x66, 0x81, 0x99, 0x24, 0x24, 0x99, 0x81, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x81, 0x42, 0x3c, 0x24, 0x24, 0x3c, 0x42, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xaa, 0x45, 0x9a, 0x35, 0x6a, 0x55, 0xaa, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x54, 0x88, 0x05, 0x82, 0x41, 0xa0, 0x11, 0x2a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x14, 0x08, 0x14, 0x22, 0x41, 0x80, 0x80, 0x63, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x11, 0x28, 0x44, 0x92, 0x49, 0x22, 0x14, 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x04, 0x20, 0x82, 0x10, 0x00, 0x44, 0x10, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x08, 0x41, 0x00, 0x10, 0x00, 0x02, 0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x04, 0x80, 0x22, 0x10, 0x81, 0x08, 0x41, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x44, 0x82, 0x10, 0x41, 0x20, 0x08, 0x41, 0x24, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x14, 0x41, 0x08, 0x45, 0x20, 0x49, 0x04, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x99, 0x66, 0x5a, 0xa5, 0xa5, 0x5a, 0x66, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xa3, 0xa3, 0x15, 0x15, 0xb8, 0xb8, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0x81, 0xa5, 0x81, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0x81, 0xa5, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0x81, 0xbd, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0x81, 0x99, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0x81, 0x99, 0xa5, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0x81, 0xbd, 0xbd, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0x81, 0xbd, 0xa5, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xcb, 0xb1, 0xb5, 0xc1, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0x81, 0xa5, 0x81, 0xdb, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0xff, 0xc3, 0xa5, 0xa5, 0x81, 0xdb, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x36, 0x49, 0x41, 0x22, 0x14, 0x08, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x36, 0x7f, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x1c, 0x22, 0x44, 0x48, 0x44, 0x22, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x00, 0x08, 0x14, 0x08, 0x36, 0x08, 0x77, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};
// clang-format on

LCDColor get_pattern(pattern_t p) { return (LCDColor)&_patterns[(int)p]; }
LCDColor get_pattern_inverse(pattern_t p) {
  return (LCDColor)&_inverse[(int)p];
}

#endif
#endif