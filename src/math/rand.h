#ifndef TENSOR_PRIVATE_MATH_RAND_H
#define TENSOR_PRIVATE_MATH_RAND_H

#include <inttypes.h>
#include "tensor_private.h"

// Random number generator
struct tensor_math_rand_generator_instance
{
    int64_t seed;
};

#endif
