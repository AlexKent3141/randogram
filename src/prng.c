#include "prng.h"
#include "math.h"

uint32_t qbasic_func(uint32_t* s)
{
    *s = (*s*0xfd43fd + 0xc39ec3) & 0xffffff;
    return *s;
}

uint32_t qbasic_high_func(uint32_t* s)
{
    *s = *s*0xfd43fd + 0xc39ec3;
    return *s >> 8;
}

uint32_t xorshift32_func(uint32_t* s)
{
  *s ^= *s << 13;
  *s ^= *s >> 17;
  *s ^= *s << 5;
  return *s;
}

uint32_t middle_square16_func(uint32_t* s)
{
  uint32_t x = pow(*s, 2);
  *s = (x >> 8) & 0xffff;
  return *s;
}

struct prng_info qbasic = { &qbasic_func, 24 };
struct prng_info qbasic_high = { &qbasic_high_func, 24 };
struct prng_info xorshift32 = { &xorshift32_func, 32 };
struct prng_info middle_square16 = { &middle_square16_func, 16 };
