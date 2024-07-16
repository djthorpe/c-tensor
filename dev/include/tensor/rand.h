#include <stdint.h>

/*
 * Opaque type for randon number generator
 */
typedef struct rand_struct rand_t;

/**
 * Create a random number generator with a seed value. If the seed
 * value is zero, the current time is used as the seed value.
 */
rand_t *rand_alloc(uint64_t seed);

/**
 * Free the random number generator.
 */
void rand_free(rand_t *generator);

/**
 * Generate a uint64_t random number between 0 and UINT64_MAX using a generator seed
 */
uint64_t rand_uint64(rand_t *generator);

/**
 * Generate a int64_t random number between 0 and INT64_MAX using a generator seed
 */
int64_t rand_int63(rand_t *generator);

/**
 * Generate a double random number between 0.0 and 1.0 using a generator seed
 */
double rand_f64(rand_t *generator);

/**
 * Generate a normalized random number using the box-muller method
 */
double rand_f64_randn(rand_t *generator, double mean, double variance);
