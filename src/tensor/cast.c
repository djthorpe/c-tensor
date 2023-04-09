#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static tensor_t *tensor_cast(tensor_pool_t *pool, tensor_dtype_t type, tensor_t *a)
{
    assert(pool != NULL);
    assert(a != NULL);

    // Return same tensor if already same type
    if (a->dtype == type)
    {
        return a;
    }

    // Create a new tensor with the same dimensions
    tensor_t *t = tensor_dtype_create(pool, type, a->dims);
    if (t == NULL)
    {
        return NULL;
    }

    // Set the operation to CAST, and dependecy to a
    t->op = CAST;
    t->a = a;

    return t;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

inline tensor_t *tensor_cast_int32(tensor_pool_t *pool, tensor_t *a)
{
    return tensor_cast(pool, INT32_T, a);
}

inline tensor_t *tensor_cast_uint32(tensor_pool_t *pool, tensor_t *a)
{
    return tensor_cast(pool, UINT32_T, a);
}

inline tensor_t *tensor_cast_int64(tensor_pool_t *pool, tensor_t *a)
{
    return tensor_cast(pool, INT64_T, a);
}

inline tensor_t *tensor_cast_uint64(tensor_pool_t *pool, tensor_t *a)
{
    return tensor_cast(pool, UINT64_T, a);
}

inline tensor_t *tensor_cast_float32(tensor_pool_t *pool, tensor_t *a)
{
    return tensor_cast(pool, FLOAT32_T, a);
}

inline tensor_t *tensor_cast_float64(tensor_pool_t *pool, tensor_t *a)
{
    return tensor_cast(pool, FLOAT64_T, a);
}
