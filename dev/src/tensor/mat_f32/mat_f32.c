#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <tensor/tensor.h>

// Private functions
#include "private.h"

/*
 * Allocate a new value
 *
 * @return: Pointer to the allocated value or NULL if allocation failed
 */
mat_f32_t *mat_f32_alloc(int *shape)
{
    // Allocate memory for the matrix struct
    mat_f32_t *mat = (mat_f32_t *)malloc(sizeof(mat_f32_t));
    if (mat == NULL)
    {
        return NULL;
    }

    // Intialize the matrix struct
    mat->n = 1;
    mat->d = 0;

    // Determine number of values and dimensions
    if (shape == NULL || shape[0] == 0)
    {
        mat->s[0] = 0;
    }
    else
    {
        for (int i = 0; i < MAX_DIMS; i++)
        {
            mat->s[i] = shape[i];
            if (shape[i] == 0)
            {
                break;
            }
            mat->d++;
            mat->n *= shape[i];
        }
    }

    // If n is larger than INT_MAX then return NULL
    // A square matrix can have 46340 elements in each dimension
    if (mat->n > INT_MAX)
    {
        free(mat);
        return NULL;
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
inline bool mat_f32_is_scalar(mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d == 0 ? true : false;
}

/*
 * Return true if a value is a vector
 */
inline bool mat_f32_is_vector(mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d == 1 ? true : false;
}

/*
 * Returns number of dimensions
 */
inline int mat_f32_dims(mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->d;
}

/*
 * Returns number of elements
 */
inline int mat_f32_elements(mat_f32_t *mat)
{
    ASSERT(mat);
    return mat->n;
}

/*
 * Returns true if two values have the same shape
 */
inline bool mat_f32_equal_shape(mat_f32_t *a, mat_f32_t *b)
{
    ASSERT(a);
    ASSERT(b);
    if (a->d != b->d)
    {
        return false;
    }
    for (int i = 0; i < a->d; ++i)
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
inline bool mat_f32_equal(mat_f32_t *a, mat_f32_t *b)
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
void mat_f32_reshape(mat_f32_t *a, int *shape)
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
