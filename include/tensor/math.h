
#ifndef TENSOR_MATH_H
#define TENSOR_MATH_H

///////////////////////////////////////////////////////////////////////////////

// Opaque random number generator
typedef struct tensor_math_rand_generator_instance tensor_math_rand_generator_t;


///////////////////////////////////////////////////////////////////////////////

/*
 * Generate a random number between 0.0 and 1.0 using a generator seed
 *
 * @param generator Random number generator
 * @return Random number between 0.0 and 1.0
*/
double tensor_math_rand_float64(tensor_math_rand_generator_t *generator)

#endif
