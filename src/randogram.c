#include "randogram.h"
#include "time.h"
#include "stdint.h"
#include "stdio.h"

void get_randogram(
  struct prng_info prng_info,
  float* intensities,
  int width,
  int height)
{
  const uint32_t prng_max =
    ~(uint32_t)0 >> (8*sizeof(uint32_t) - prng_info.state_size);

  uint32_t state = time(NULL) & prng_max;

  // We probably don't have enough pixels to plot the whole state space so
  // just do the "upper-left" part.
  for (int i = 0; i < width*height; i++)
  {
    intensities[i] = 1.0f;
  }

  // Execute the PRNG for half of its state.
  int half_state = prng_info.state_size / 2;
  const int prng_half = prng_max >> half_state;
  uint32_t next, upper, lower;
  for (uint32_t i = 0; i < (1 << prng_info.state_size - 1); i++)
  {
    next = (*prng_info.func)(&state);
    
    lower = next & prng_half;
    upper = (next >> half_state) & prng_half;
    if (lower < height && upper < width)
    {
      intensities[lower*width + upper] = 0;
    }
  }
}
