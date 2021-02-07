#ifndef __RANDOGRAM_H__
#define __RANDOGRAM_H__

#include "prng.h"

void get_randogram(
  struct prng_info prng_info,
  float* intensities,
  int width,
  int height);

#endif // __RANDOGRAM_H__
