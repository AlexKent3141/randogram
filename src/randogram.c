#include "randogram.h"
#include "time.h"
#include "stdint.h"
#include "stdio.h"

void get_randogram(
  struct prng_info prng_info,
  int* selected,
  int num_bits)
{
  const uint32_t prng_max =
    ~(uint32_t)0 >> (8*sizeof(uint32_t) - prng_info.state_size);

  uint32_t state = time(NULL) & prng_max;

  // Plot the lowest `num_bits` against the next lowest `num_bits`.
  uint32_t next, upper, lower;
  const uint32_t word = (1 << num_bits) - 1;
  for (uint32_t i = 0; i < (word * word) >> 2; i++)
  {
    next = (*prng_info.func)(&state);
    
    lower = next & word;
    upper = (next >> num_bits) & word;
    selected[lower*word + upper] = 1;
  }
}
