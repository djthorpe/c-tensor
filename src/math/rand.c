#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <tensor/math.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

/**
 * Create a random number generator with a seed value.
 */
tensor_math_rand_generator_t *tensor_math_rand_generator_create(tensor_pool_t *pool, uint64_t seed)
{
    assert(pool != NULL);

    // Allocate the random number generator
    tensor_math_rand_generator_t *generator = tensor_pool_alloc(pool, sizeof(tensor_math_rand_generator_t), NULL);
    if (generator == NULL)
    {
        return NULL;
    }

    // Initialize the random number generator
    if (seed == 0)
    {
        time_t t = time(NULL);
        generator->seed = (uint64_t)t;
    }
    else
    {
        generator->seed = seed;
    }

    // Return success
    return generator;
}

// Generate a uint64 random number between 0 and UINT64_MAX using a generator seed
uint64_t tensor_math_rand_uint64(tensor_math_rand_generator_t *generator)
{
    assert(generator);

    generator->seed = generator->seed + 0x9E3779B97F4A7C15;
    uint64_t value = generator->seed;
    value = (value ^ (value >> 30)) * 0xBF58476D1CE4E5B9;
    value = (value ^ (value >> 27)) * 0x94D049BB133111EB;
    value = value ^ (value >> 31);
    return value;
}

// Generate a random number between 0 and INT64_MAX using a generator seed
inline int64_t tensor_math_rand_int63(tensor_math_rand_generator_t *generator)
{
    return (int64_t)(tensor_math_rand_uint64(generator) >> 1);
}

// Generate a float64 random number between 0.0 and 1.0 using a generator seed
inline double tensor_math_rand_float64(tensor_math_rand_generator_t *generator)
{
    return (double)tensor_math_rand_uint64(generator) / (double)UINT64_MAX;
}

/*
//===========================================================================
//=  Function to generate normally distributed random variable using the    =
//=  Box-Muller method                                                      =
//=    - Input: mean and standard deviation                                 =
//=    - Output: Returns with normally distributed random variable          =
//===========================================================================
double tensor_math_randn_float64(tensor_math_rand_generator_t *generator)
{
    assert(generator);

    // Generate a random number > 0.0 and <= 1.0
    double u = 0.0;
    while (u == 0.0)
    {
        u = tensor_math_rand_float64(generator);
    }

    // Compute r
    double r = sqrt(-2.0 * log(u));

    // Generate theta
    double theta = 0.0;
    while (theta == 0.0) {
        theta = 2.0 * M_PI * rand_val(0);
    }

    // Generate x value
    double x = r * cos(theta);

    // Adjust x value for specified mean and variance
    double norm_rv = (x * std_dev) + mean;

    // Return the normally distributed RV value
    return (norm_rv);
}
*/
