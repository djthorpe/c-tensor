#include <stdio.h>
#include <stdbool.h>
#include "rand.h"

/*
 * Opaque type for float32 scalar/matrix
 */
typedef struct mat_f32_struct mat_f32_t;

/*
 * Allocate a new matrix
 * @return: Pointer to the allocated scalar/matrix or NULL if allocation failed
 */
mat_f32_t *mat_f32_alloc(int *shape);

/*
 * Free a scalar/matrix
 */
void mat_f32_free(mat_f32_t *mat);

/*
 * Tests if a scalar/matrix is scalar value
 *
 * @return: True if zero-dimensional, false otherwise
 */
bool mat_f32_is_scalar(mat_f32_t *mat);

/*
 * Tests if a matrix is a vector
 *
 * @return: True if one-dimensional, false otherwise
 */
bool mat_f32_is_vector(mat_f32_t *mat);

/*
 * Returns number of dimensions
 *
 * @return: Number of dimensions
 */
int mat_f32_dims(mat_f32_t *mat);

/*
 * Returns number of elements
 *
 * @return: Number of elements
 */
int mat_f32_elements(mat_f32_t *mat);

/*
 * Tests if values a, b have the same shape
 *
 * @return: True if shapes are equal, false otherwise
 */
bool mat_f32_equal_shape(mat_f32_t *a, mat_f32_t *b);

/*
 * Pretty print value to a file handle
 */
void mat_f32_write(FILE *f, const mat_f32_t *mat);

/*
 * Reshape without changing the data
 * Assumes the number of elements of the value and the shape are the same
 */
void mat_f32_reshape(mat_f32_t *a, int *shape);

/*
 * Set element values to a constant
 */
void mat_f32_set(mat_f32_t *mat, float v);

/*
 * Range elements from 0 to N-1
 */
void mat_f32_arange(mat_f32_t *mat);

/*
 * Set elements to random values with mean 0 and variance 1
 */
void mat_f32_randn(rand_t* seed, mat_f32_t *mat);

/*
 * A + B => C
 * Naive version of addition
 * Assumes all values have the same shape
 */
void mat_f32_add_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c);

/*
 * A + B[d=0] => C
 * Naive version of addition of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_add_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c);

/*
 * A - B => C
 * Naive version of subtraction
 * Assumes all values have the same shape
 */
void mat_f32_sub_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c);

/*
 * A - B[d=0] => C
 * Naive version of subtraction of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_sub_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c);

/*
 * A * B[d=0] => C
 * Naive version of multiplication of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_mul_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c);

/*
 * A / B[d=0] => C
 * Naive version of division of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_div_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c);
