#ifndef RAND_PRIVATE_H
#define RAND_PRIVATE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Random number generator
struct rand_struct
{
    // Current random number seed
    uint64_t seed;

    // Cached Box-Muller value
    double cached;
};

#endif
