#include "prng.h"

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

struct prng_info qbasic = { &qbasic_func, 24 };
struct prng_info qbasic_high = { &qbasic_high_func, 24 };
