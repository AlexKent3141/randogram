#ifndef __RANDOGRAM_H__
#define __RANDOGRAM_H__

#include "prng.h"

#include "stdint.h"

void get_randogram(
  struct prng_info prng_info,
  int* selected,
  int num_bits,
  uint32_t seed);

#endif // __RANDOGRAM_H__
