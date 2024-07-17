#include <math.h>
#include <limits.h>
#include <time.h>
#include <tensor/tensor.h>

// Private functions
#include "private.h"

/**
 * Create a random number generator with a seed value.
 */
rand_t *rand_alloc(uint64_t seed)
{
    // Allocate the random number generator
    rand_t *generator = malloc(sizeof(rand_t));
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

    // Initialize the cached value
    generator->cached = NAN;

    // Return success
    return generator;
}

/**
 * Free the random number generator.
 */
void rand_free(rand_t *generator)
{
    free(generator);
}

/**
 * Generate a uint64_t random number between 0 and UINT64_MAX using a generator seed
 */
uint64_t rand_uint64(rand_t *generator)
{
    ASSERT(generator);

    generator->seed = generator->seed + 0x9E3779B97F4A7C15;
    uint64_t value = generator->seed;
    value = (value ^ (value >> 30)) * 0xBF58476D1CE4E5B9;
    value = (value ^ (value >> 27)) * 0x94D049BB133111EB;
    value = value ^ (value >> 31);
    return value;
}

/**
 * Generate a int64_t random number between 0 and INT64_MAX using a generator seed
 */
inline int64_t rand_int63(rand_t *generator)
{
    return (int64_t)(rand_uint64(generator) >> 1);
}

/**
 * Generate a double random number between 0.0 and 1.0 using a generator seed
 */
inline double rand_f64(rand_t *generator)
{
    return (double)rand_uint64(generator) / (double)UINT64_MAX;
}

/**
 * Generate a normalized random number using the box-muller method
 * https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
 */
double rand_f64_randn(rand_t *generator, double mean, double variance)
{
    double value;
    if (!isnan(generator->cached))
    {
        value = generator->cached;
        generator->cached = NAN;
    }
    else
    {
        double x = rand_f64(generator);
        double y = rand_f64(generator);
        double r = sqrt(-2.0 * log(x));
        double z1 = r * cos(2.0 * M_PI * y);
        double z2 = r * sin(2.0 * M_PI * y);
        value = z1;
        generator->cached = z2;
    }
    return value * variance + mean;
}
