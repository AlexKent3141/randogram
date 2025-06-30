#ifndef __PRNG_H__
#define __PRNG_H__ 

#include "stdint.h"
#include "stdlib.h"

/* We support PRNGs which have at most 32 bits of state. */
typedef uint32_t (*prng_func)(uint32_t*);

struct prng_info
{
  prng_func func;
  size_t state_size;
};

// QBasic's 24 bit prng.
extern struct prng_info qbasic;

// Modified QBasic 24 bit prng which preserves the 8 highest bits.
extern struct prng_info qbasic_high;

extern struct prng_info xorshift32;

extern struct prng_info middle_square16;

extern struct prng_info c_rand;

#endif // __PRNG_H__
