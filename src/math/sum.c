#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <tensor/math.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - SUM

/**
 * Add two int32 values, and return. If overflow then set the overflow flag.
 */
int32_t tensor_math_sum_int32(int32_t a, int32_t b, bool *overflow)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a > 0 && b > 0 && a > INT32_MAX - b)
    {
        if (overflow)
        {
            *overflow = true;
        }
    }
    else if (a < 0 && b < 0 && a < INT32_MIN - b)
    {
        if (overflow)
        {
            *overflow = true;
        }
    }

    return a + b;
}

/**
 * Add two uint32 values, and return. If overflow then set the overflow flag.
 */
uint32_t tensor_math_sum_uint32(uint32_t a, uint32_t b, bool *overflow)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a > UINT32_MAX - b)
    {
        if (overflow)
        {
            *overflow = true;
        }
    }
    return a + b;
}

/**
 * Add two int64 values, and return. If overflow then set the overflow flag.
 */
int64_t tensor_math_sum_int64(int64_t a, int64_t b, bool *overflow)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a > 0 && b > 0 && a > INT64_MAX - b)
    {
        if (overflow)
        {
            *overflow = true;
        }
    }
    else if (a < 0 && b < 0 && a < INT64_MIN - b)
    {
        if (overflow)
        {
            *overflow = true;
        }
    }
    return a + b;
}

/**
 * Add two uint64 values, and return. If overflow then set the overflow flag.
 */
uint64_t tensor_math_sum_uint64(uint64_t a, uint64_t b, bool *overflow)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    if (a > UINT64_MAX - b)
    {
        if (overflow)
        {
            *overflow = true;
        }
    }
    return a + b;
}

/**
 * Sum a series of int32 elements. If overflow then set the overflow flag.
 */
int32_t tensor_math_sum_int32_vec(uint32_t nelems, int32_t *elems, bool *overflow)
{
    assert(elems != NULL);
    assert(nelems > 0);

    int32_t sum = 0;
    for (uint32_t i = 0; i < nelems; i++)
    {
        sum = tensor_math_sum_int32(sum, elems[i], overflow);
    }
    return sum;
}

/**
 * Sum a series of uint32 elements. If overflow then set the overflow flag.
 */
uint32_t tensor_math_sum_uint32_vec(uint32_t nelems, uint32_t *elems, bool *overflow)
{
    assert(elems != NULL);
    assert(nelems > 0);

    uint32_t sum = 0;
    for (uint32_t i = 0; i < nelems; i++)
    {
        sum = tensor_math_sum_uint32(sum, elems[i], overflow);
    }
    return sum;
}

/**
 * Sum a series of int64 elements. If overflow then set the overflow flag.
 */
int64_t tensor_math_sum_int64_vec(uint32_t nelems, int64_t *elems, bool *overflow)
{
    assert(elems != NULL);
    assert(nelems > 0);

    int64_t sum = 0;
    for (uint32_t i = 0; i < nelems; i++)
    {
        sum = tensor_math_sum_int64(sum, elems[i], overflow);
    }
    return sum;
}

/**
 * Sum a series of uint64 elements. If overflow then set the overflow flag.
 */
uint64_t tensor_math_sum_uint64_vec(uint32_t nelems, uint64_t *elems, bool *overflow)
{
    assert(elems != NULL);
    assert(nelems > 0);

    uint64_t sum = 0;
    for (uint32_t i = 0; i < nelems; i++)
    {
        sum = tensor_math_sum_uint64(sum, elems[i], overflow);
    }
    return sum;
}

/**
 * Sum a series of float32 elements.
 */
float tensor_math_sum_float32_vec(uint32_t nelems, float *elems)
{
    assert(elems != NULL);
    assert(nelems > 0);

    float sum = 0;
    for (uint32_t i = 0; i < nelems; i++)
    {
        sum += elems[i];
    }
    return sum;
}

/**
 * Sum a series of float64 elements.
 */
double tensor_math_sum_float64_vec(uint32_t nelems, double *elems)
{
    assert(elems != NULL);
    assert(nelems > 0);

    double sum = 0;
    for (uint32_t i = 0; i < nelems; i++)
    {
        sum += elems[i];
    }
    return sum;
}
