#include <tensor/tensor.h>

// Private functions
#include "private.h"

/*
 * Set all elements to a constant value
 */
inline void mat_f32_set(mat_f32_t *mat, float v)
{
    ASSERT(mat);
    for (size_t i = 0; i < mat->n; ++i)
    {
        mat->v[i] = v;
    }
}

/*
 * Range all elements from 0 to N
 */
inline void mat_f32_arange(mat_f32_t *mat)
{
    ASSERT(mat);
    for (size_t i = 0; i < mat->n; ++i)
    {
        mat->v[i] = i;
    }
}

/*
 * Set elements of a scalar/matrix to random values with mean 0 and variance 1
 */
void mat_f32_randn(rand_t *seed, mat_f32_t *mat)
{
    ASSERT(seed);
    ASSERT(mat);
    for (size_t i = 0; i < mat->n; ++i)
    {
        mat->v[i] = (float)rand_f64_randn(seed, 0, 1);
    }
}

/*
 * A + B => C
 * Naive version of addition
 * Assumes all values have the same shape
 */
void mat_f32_add_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c)
{
    ASSERT(a);
    ASSERT(b);
    ASSERT(c);
    ASSERT(mat_f32_equal_shape(a, b));
    ASSERT(mat_f32_equal_shape(a, c));

    for (int i = 0; i < a->n; i++)
    {
        c->v[i] = a->v[i] + b->v[i];
    }
}

/*
 * A + B[d=0] => C
 * Naive version of addition of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_add_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c)
{
    ASSERT(a);
    ASSERT(b);
    ASSERT(c);
    ASSERT(mat_f32_equal_shape(a, c));
    ASSERT(mat_f32_is_scalar(b));

    for (int i = 0; i < a->n; i++)
    {
        c->v[i] = a->v[i] + b->v[0];
    }
}

/*
 * A - B => C
 * Naive version of subtraction
 * Assumes all values have the same shape
 */
void mat_f32_sub_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c)
{
    ASSERT(a);
    ASSERT(b);
    ASSERT(c);
    ASSERT(mat_f32_equal_shape(a, b));
    ASSERT(mat_f32_equal_shape(a, c));

    for (int i = 0; i < a->n; i++)
    {
        c->v[i] = a->v[i] - b->v[i];
    }
}

/*
 * A - B[d=0] => C
 * Naive version of subtraction of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_sub_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c)
{
    ASSERT(a);
    ASSERT(b);
    ASSERT(c);
    ASSERT(mat_f32_equal_shape(a, c));
    ASSERT(mat_f32_is_scalar(b));

    for (int i = 0; i < a->n; i++)
    {
        c->v[i] = a->v[i] - b->v[0];
    }
}

/*
 * A * B[d=0] => C
 * Naive version of multiplication of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_mul_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c)
{
    ASSERT(a);
    ASSERT(b);
    ASSERT(c);
    ASSERT(mat_f32_equal_shape(a, c));
    ASSERT(mat_f32_is_scalar(b));

    for (int i = 0; i < a->n; i++)
    {
        c->v[i] = a->v[i] * b->v[0];
    }
}

/*
 * A / B[d=0] => C
 * Naive version of division of a scalar
 * Assumes B is a scalar value
 */
void mat_f32_div_scalar_naive(mat_f32_t *a, mat_f32_t *b, mat_f32_t *c)
{
    ASSERT(a);
    ASSERT(b);
    ASSERT(c);
    ASSERT(mat_f32_equal_shape(a, c));
    ASSERT(mat_f32_is_scalar(b));

    for (int i = 0; i < a->n; i++)
    {
        c->v[i] = a->v[i] / b->v[0];
    }
}
