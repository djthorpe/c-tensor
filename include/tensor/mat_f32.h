#include <stdio.h>
#include <stdbool.h>
#include "rand.h"

/*
 * Opaque type for float32 scalar/matrix
 */
typedef struct mat_f32_struct mat_f32_t;

/*
 * @brief Allocate a new value
 *
 * The shape is an array of integers, where the number of elements
 * is the number of dimensions and the values are the size of each
 * dimension, terminated by zero.
 *
 * @param shape: Array of integers representing the shape of the matrix, terminated
 *              by zero. If shape is NULL then a constant scalar value is created.
 * @return: Pointer to the allocated scalar/matrix or NULL if allocation failed
 */
mat_f32_t *mat_f32_alloc(const uint32_t *shape);

/*
 * @brief Free a matrix
 *
 * @param v: The previously allocated valueArray of integers representing the shape of the matrix, terminated
 *              by zero. If shape is NULL then a constant scalar value is created.
 * @return: Pointer to the allocated scalar/matrix or NULL if allocation failed
 */
void mat_f32_free(mat_f32_t *v);

/*
 * @brief Test if a value is a scalar (zero-dimensional)
 *
 * @return: True if the value is a scalar
 */
bool mat_f32_is_scalar(const mat_f32_t *v);

/*
 * @brief Tests if a value is a vector (one-dimensional)
 *
 * @return: True if the value is a vector
 */
bool mat_f32_is_vector(const mat_f32_t *v);

/*
 * @brief Tests if a value is a matrix (two-dimensional)
 *
 * @return: True if the value is a matrix with two dimensions
 */
bool mat_f32_is_2d(const mat_f32_t *v);

/*
 * @brief Tests if a value is a square matrix (two-dimensional)
 *
 * @return: True if the value is a matrix with two dimensions and has the same number of rows and columns
 */
bool mat_f32_is_square(const mat_f32_t *v);

/*
 * @brief Returns number of dimensions
 *
 * @return: Number of dimensions
 */
int mat_f32_dims(const mat_f32_t *v);

/*
 * @brief Returns number of elements
 *
 * Returns number of elements for a specific dimension. If dim is -1, then
 * the total number of elements is returned.
 *
 * @param v: Value 
 * @param dim: Dimension to return elements for, or -1
 * @return: Number of elements
 */
size_t mat_f32_elements(const mat_f32_t *v, const int dim);

/*
 * @brief Tests if values a, b have the same shape
 *
 * @return: True if shapes are equal, false otherwise
 */
bool mat_f32_equal_shape(const mat_f32_t *a, const mat_f32_t *b);

/*
 * @brief Tests if values a, b are equal shape and elements
 *
 * @return: True if values are equal, false otherwise
 */
bool mat_f32_equal(const mat_f32_t *a, const mat_f32_t *b);

/*
 * @brief Pretty print value to a file handle
 *
 * Note this function currently does a poor job of formatting the output
 *
 * @param f: File handle
 * @param v: Value to print
 */
void mat_f32_write(FILE *f, const mat_f32_t *v);

/*
 * @brief Reshape a value without changing the data
 *
 * Reshape a value into a new set of dimensions. Assumes the number
 * of elements of the value and the shape are the same.
 *
 * @param a: Value to reshape
 * @param shape: New shape
 */
void mat_f32_reshape(mat_f32_t *a, const uint32_t *shape);

/*
 * @brief Resize a value
 *
 * Resize a value into a new set of dimensions. If new elements
 * are added, they are set to zero.
 *
 * @param a: Value to resize
 * @param shape: New shape
 * @return: True if resize was successful, false otherwise. If false,
 *         the value is unchanged.
 */
bool mat_f32_resize(mat_f32_t *a, const uint32_t *shape);

/*
 * @brief Set value elements to a constant
 *
 * A := B
 * Assumes the b value is a scalar or has the same shape as a.
 *
 * @param v: Value to set
 * @param b: Constant value
 */
void mat_f32_set(mat_f32_t *a, const mat_f32_t *b);

/*
 * @brief Set value as an identity matrix
 *
 * A := I
 * Assumes the value is a square matrix
 *
 * @param v: Value to set as identity matrix
 */
void mat_f32_set_identity(mat_f32_t *v);

/*
 * @brief Sum elements along a dimension
 *
 * V := SUM(A)
 *
 * Compute the sum of elements along a specific dimension and return the
 * result. If the dimension is -1, then all elements are aggregated and the
 * output is a scalar. The result is placed in the output value. The
 * aggregate operation may not be successful if the output value cannot be
 * resized.
 *
 * @param v: Pointer to output value. If *v is NULL, then a new value
 *           is allocated. If *v is not NULL, then the value may be resized
 * @param a: Value to sum
 * @param dim: Dimension to sum along, or -1
 * @return: True if sum was successful, false otherwise.
 */
bool mat_f32_sum(mat_f32_t **v, const mat_f32_t *a, const int dim);

/*
 * @brief Mean elements along a dimension
 *
 * V := MEAN(A)
 *
 * Compute the mean of elements along a specific dimension and return the
 * result. If the dimension is -1, then all elements are aggregated and the
 * output is a scalar. The result is placed in the output value. The
 * aggregate operation may not be successful if the output value cannot be
 * resized.
 *
 * @param v: Pointer to output value. If *out is NULL, then a new value
 *           is allocated. If *out is not NULL, then the value may be resized
 * @param a: Value to sum
 * @param dim: Dimension to sum along, or -1
 * @return: True if sum was successful, false otherwise.
 */
bool mat_f32_mean(mat_f32_t **v, const mat_f32_t *a, const int dim);

/*
 * @brief Set value elements to a range from 'start' with step 'step'
 *
 * The first element is set to 'start', the second to 'start + step', and so on.
 *
 * @param v: Value to set
 * @param start: Start value
 * @param step: Step value
 */
void mat_f32_range(mat_f32_t *v, const double start, const double step);

/*
 * @brief Set elements to random values between 0 and 1
 *
 * @param v: Value to set
 * @param seed: Random generator with seed
 */
void mat_f32_rand(mat_f32_t *v, rand_t *seed);

/*
 * @brief Set elements to random values with mean 0 and variance 1
 *
 * @param v: Value to set
 * @param seed: Random generator with seed
 */
void mat_f32_randn(mat_f32_t *v, rand_t *seed);

/*
 * @brief Add two values
 *
 * V := A + B
 * Assumes a and c have the same shape, and that b is either the same shape
 * or a scalar value. Naive version has no optimizations.
 *
 * @param v: Output value
 * @param a: First value
 * @param b: Second value or scalar
 */
void mat_f32_add_naive(mat_f32_t *v, const mat_f32_t *a, const mat_f32_t *b);

/*
 * @brief Subtract one value from another
 *
 * V := A - B
 * Assumes a and c have the same shape, and that b is either the same shape
 * or a scalar value. Naive version has no optimizations.
 *
 * @param v: Output value
 * @param a: First value
 * @param b: Second value or scalar
 */
void mat_f32_sub_naive(mat_f32_t *v, const mat_f32_t *a, const mat_f32_t *b);

/*
 * @brief Multiply element-wise one value with another
 *
 * V := A * B
 * Assumes a and c have the same shape, and that b is either the same shape
 * or a scalar value. Naive version has no optimizations.
 *
 * @param v: Output value
 * @param a: First value
 * @param b: Second value or scalar
 */
void mat_f32_mul_naive(mat_f32_t *v, const mat_f32_t *a, const mat_f32_t *b);

/*
 * @brief Divide element-wise one value with another
 *
 * V := A / B
 * Assumes a and c have the same shape, and that b is either the same shape
 * or a scalar value. Naive version has no optimizations.
 *
 * @param v: Output value
 * @param a: First value
 * @param b: Second value or scalar
 */
void mat_f32_div_naive(mat_f32_t *v, const mat_f32_t *a, const mat_f32_t *b);
