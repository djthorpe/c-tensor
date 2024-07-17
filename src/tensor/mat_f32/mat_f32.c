#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <tensor/tensor.h>

// Private functions
#include "private.h"

/*
 * Normalize the shape
 */
void mat_f32_shape_normalize(uint32_t *shape)
{
    ASSERT(shape);
    // No-op
}

/*
 * Allocate a new value
 *
 * @return: Pointer to the allocated value or NULL if allocation failed
 */
mat_f32_t *mat_f32_alloc(const uint32_t *shape)
{
    // Allocate memory for the matrix struct
    mat_f32_t *mat = (mat_f32_t *)malloc(sizeof(mat_f32_t));
    if (mat == NULL)
    {
        return NULL;
    }

    // Intialize the numebr of elements and dimension
    mat->n = 1;
    mat->d = 0;

    // Normalize the shape
    memcpy(mat->s, shape, MAX_DIMS * sizeof(uint32_t));
    mat_f32_shape_normalize(mat->s);

    // Determine number of elements and dimensions
    if (shape == NULL || shape[0] == 0)
    {
        mat->s[0] = 0;
    }
    else
    {
        for (int i = 0; i < MAX_DIMS; i++)
        {
            // Increment dimensions if size is not 1
            if (mat->s[i] != 1)
            {
                mat->d++;
            }

            // If n is larger than UINT32_MAX then return NULL
            mat->n *= shape[i];
            if (mat->n > UINT32_MAX)
            {
                free(mat);
                return NULL;
            }
        }
    }

    // Allocate memory for the values
    mat->v = (float *)calloc(mat->n, sizeof(float));
    if (mat->v == NULL)
    {
        free(mat);
        return NULL;
    }

    // Return success
    return mat;
}

/*
 * Free a value
 */
inline void mat_f32_free(mat_f32_t *mat)
{
    if (mat != NULL)
    {
        free(mat->v);
        free(mat);
    }
}

/*
 * Return true if a value is a scalar
 */
inline bool mat_f32_is_scalar(const mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d == 0 ? true : false;
}

/*
 * Return true if a value is a vector
 */
inline bool mat_f32_is_vector(const mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d == 1 ? true : false;
}

/*
 * Return true if a value is a 2D matrix
 */
inline bool mat_f32_is_2d(const mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d == 2 ? true : false;
}

/*
 * Return true if a value is a square 2D matrix
 */
inline bool mat_f32_is_square(const mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d == 2 && mat->s[0] == mat->s[1] ? true : false;
}

/*
 * Returns number of dimensions
 */
inline int mat_f32_dims(const mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d;
}

/*
 * Returns number of elements
 */
inline size_t mat_f32_elements(const mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->n;
}

/*
 * Returns true if two values have the same shape
 */
inline bool mat_f32_equal_shape(const mat_f32_t *a, const mat_f32_t *b)
{
    ASSERT(a);
    ASSERT(b);
    if (a->d != b->d)
    {
        return false;
    }
    for (int i = 0; i < MAX_DIMS; ++i)
    {
        if (a->s[i] != b->s[i])
        {
            return false;
        }
    }
    return true;
}

/*
 * Returns true if two values are equal
 */
inline bool mat_f32_equal(const mat_f32_t *a, const mat_f32_t *b)
{
    ASSERT(a);
    ASSERT(b);
    if (!mat_f32_equal_shape(a, b))
    {
        return false;
    }
    for (size_t i = 0; i < a->n; ++i)
    {
        if (a->v[i] != b->v[i])
        {
            return false;
        }
    }
    return true;
}

/*
 * Reshape a matrix without changing the data
 * Assumes the number of elements is the same
 */
void mat_f32_reshape(mat_f32_t *a, const uint32_t *shape)
{
    ASSERT(a);
    ASSERT(shape);

    // Scalars are not reshaped
    if (a->d == 0 && shape[0] == 0)
    {
        return;
    }

    // Check number of elements of new shape
    size_t n = 1;
    int d = 0;
    for (int i = 0; i < MAX_DIMS; i++)
    {
        if (shape[i] == 0)
        {
            break;
        }
        n *= shape[i];
        d++;
    }
    ASSERT(n == a->n);

    // Set new shape
    a->n = n;
    a->d = d;
    for (int i = 0; i < d; i++)
    {
        a->s[i] = shape[i];
    }
}
