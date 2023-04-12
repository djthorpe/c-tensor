#ifndef TENSOR_PRIVATE_MATH_RAND_H
#define TENSOR_PRIVATE_MATH_RAND_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Random number generator
struct tensor_math_rand_generator_instance
{
    // Current random number seed
    uint64_t seed;

    // Cached Box-Muller value
    double cached;
};

#endif
