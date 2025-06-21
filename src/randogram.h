#ifndef __RANDOGRAM_H__
#define __RANDOGRAM_H__

#include "prng.h"

void get_randogram(
  struct prng_info prng_info,
  int* selected,
  int num_bits);

#endif // __RANDOGRAM_H__
