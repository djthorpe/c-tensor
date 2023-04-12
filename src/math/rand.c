#include <assert.h>
#include <math.h>
#include <limits.h>

#include <tensor/math.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Generate a float64 random number between 0.0 and 1.0 using a generator seed
double tensor_math_rand_float64(tensor_math_rand_generator_t *generator)
{
    assert(generator);

    const int64_t a = 16807; // Multiplier, fifth power of seven
    const int64_t m = INT64_MAX;
    const int64_t q = INT64_MAX / a; // m div a
    const int64_t r = INT64_MAX % a; // m mod a

    // seed divided by q and modulo q
    int64_t seed_div_q = generator->seed / q;
    int64_t seed_mod_q = generator->seed % q;

    // new seed value
    int64_t seed_new = (a * seed_mod_q) - (r * seed_div_q);
    if (seed_new > 0)
    {
        generator->seed = seed_new;
    }
    else
    {
        generator->seed = seed_new + m;
    }

    // Return a random value between 0.0 and 1.0
    return ((double)generator->seed / m);
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
