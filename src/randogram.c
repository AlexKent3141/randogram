#include "randogram.h"
#include "time.h"
#include "stdint.h"

// QBasic 24-bit PRNG
uint32_t rnd24(uint32_t* s)
{
    *s = (*s*0xfd43fd + 0xc39ec3) & 0xffffff;
    return *s;
}

void get_randogram(float* intensities, int width, int height)
{
  uint32_t state = time(NULL) & 0xffffff;

  // We are dealing with a 24 bit PRNG at the moment, so overall we have
  // 12 bits to plot on each axis.
  // The width and height probably aren't sufficient so just plot the upper-left
  // rectangle.
  for (int i = 0; i < width*height; i++)
  {
    intensities[i] = 1.0f;
  }

  // Execute the PRNG for half of its state.
  uint32_t next, upper, lower;
  for (uint32_t i = 0; i < (1 << 23); i++)
  {
    next = rnd24(&state);
    
    lower = next & 0xfff;
    upper = (next >> 12) & 0xfff;
    if (lower < height && upper < width)
    {
      intensities[lower*width + upper] = 0;
    }
  }
}
