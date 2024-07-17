#ifndef TENSOR_PRIVATE_MATH_SUM_H
#define TENSOR_PRIVATE_MATH_SUM_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Sum a series of int32 elements. If overflow then set the overflow flag.
 */
int32_t tensor_math_sum_int32_vec(uint32_t nelems, int32_t *elems, bool *overflow);

/**
 * Sum a series of uint32 elements. If overflow then set the overflow flag.
 */
uint32_t tensor_math_sum_uint32_vec(uint32_t nelems, uint32_t *elems, bool *overflow);

/**
 * Sum a series of int64 elements. If overflow then set the overflow flag.
 */
int64_t tensor_math_sum_int64_vec(uint32_t nelems, int64_t *elems, bool *overflow);

/**
 * Sum a series of uint64 elements. If overflow then set the overflow flag.
 */
uint64_t tensor_math_sum_uint64_vec(uint32_t nelems, uint64_t *elems, bool *overflow);

/**
 * Sum a series of float32 elements.
 */
float tensor_math_sum_float32_vec(uint32_t nelems, float *elems);

/**
 * Sum a series of float64 elements.
 */
double tensor_math_sum_float64_vec(uint32_t nelems, double *elems);

#endif

