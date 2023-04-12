
#ifndef TENSOR_MATH_H
#define TENSOR_MATH_H

#include <stdint.h>
#include <stdbool.h>
#include "tensor.h"

///////////////////////////////////////////////////////////////////////////////

// Opaque random number generator
typedef struct tensor_math_rand_generator_instance tensor_math_rand_generator_t;

///////////////////////////////////////////////////////////////////////////////

/**
 * Create a random number generator with a seed value.
 * 
 * @param pool         Memory pool
 * @param seed         Starting value, or zero to seed with the current time
 * @return             Returns a random number generator or NULL if there
 *                     was an error
 */
tensor_math_rand_generator_t *tensor_math_rand_generator_create(tensor_pool_t *pool, uint64_t seed);

/**
 * Generate a random number between 0.0 and 1.0 using a generator seed
 * 
 * The random number generator is a linear congruential generator (LCG) and
 * over infinite time evenly distribute across all possible values.
 * 
 * @param generator    Random number generator
 * @return             Random number between 0.0 and 1.0
 */
double tensor_math_rand_float64(tensor_math_rand_generator_t *generator);

/**
 * Generate a random number between 0 and UINT64_MAX using a generator seed
 * 
 * The random number generator is a linear congruential generator (LCG) and
 * over infinite time evenly distribute across all possible values.
 * 
 * @param generator    Random number generator
 * @return             Random number between 0 and UINT64_MAX
 */
uint64_t tensor_math_rand_uint64(tensor_math_rand_generator_t *generator);


/**
 * Generate a random number between 0 and INT64_MAX using a generator seed
 * 
 * The random number generator is a linear congruential generator (LCG) and
 * over infinite time evenly distribute across all possible values. Note that
 * this returns positive value only.
 * 
 * @param generator    Random number generator
 * @return             Random number between 0 and INT64_MAX
 */
int64_t tensor_math_rand_int63(tensor_math_rand_generator_t *generator);

#endif
