#include "randogram.h"
#include "stdint.h"
#include "stdio.h"

void get_randogram(
  struct prng_info prng_info,
  int* selected,
  int num_bits,
  uint32_t seed)
{
  // Plot the lowest `num_bits` against the next lowest `num_bits`.
  uint32_t next, upper, lower;
  const uint32_t word = (1 << num_bits) - 1;
  for (uint32_t i = 0; i < (word * word) >> 2; i++)
  {
    next = (*prng_info.func)(&seed);
    
    lower = next & word;
    upper = (next >> num_bits) & word;
    selected[lower*word + upper] = 1;
  }
}
