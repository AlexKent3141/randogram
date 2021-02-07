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

#endif // __PRNG_H__
