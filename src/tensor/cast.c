#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include <tensor/tensor.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static inline bool tensor_cast_copy_int32(void *dst, tensor_dtype_t dtype, int32_t src)
{
    switch (dtype)
    {
    case UINT32_T:
        if (src < 0)
        {
            return false;
        }
        *((uint32_t *)dst) = (uint32_t)src;
        return true;
    case INT64_T:
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case UINT64_T:
        if (src < 0)
        {
            return false;
        }
        *((uint64_t *)dst) = (uint64_t)src;
        return true;
    case FLOAT32_T:
        *((float *)dst) = (float)src;
        return true;
    case FLOAT64_T:
        *((double *)dst) = (double)src;
        return true;
    default:
        return false;
    }
}

static inline bool tensor_cast_copy_uint32(void *dst, tensor_dtype_t dtype, uint32_t src)
{
    switch (dtype)
    {
    case INT32_T:
        if (src > INT32_MAX)
        {
            return false;
        }
        *((int32_t *)dst) = (int32_t)src;
        return true;
    case INT64_T:
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case UINT64_T:
        *((uint64_t *)dst) = (uint64_t)src;
        return true;
    case FLOAT32_T:
        *((float *)dst) = (float)src;
        return true;
    case FLOAT64_T:
        *((double *)dst) = (double)src;
        return true;
    default:
        return false;
    }
}

static inline bool tensor_cast_copy_int64(void *dst, tensor_dtype_t dtype, int64_t src)
{
    switch (dtype)
    {
    case INT32_T:
        if (src > INT32_MAX || src < INT32_MIN)
        {
            return false;
        }
        *((int32_t *)dst) = (int32_t)src;
        return true;
    case UINT32_T:
        if (src < 0)
        {
            return false;
        }
        *((uint32_t *)dst) = (uint32_t)src;
        return true;
    case UINT64_T:
        if (src < 0)
        {
            return false;
        }
        *((uint64_t *)dst) = (uint64_t)src;
        return true;
    case FLOAT32_T:
        *((float *)dst) = (float)src;
        return true;
    case FLOAT64_T:
        *((double *)dst) = (double)src;
        return true;
    default:
        return false;
    }
}

static inline bool tensor_cast_copy_uint64(void *dst, tensor_dtype_t dtype, uint64_t src)
{
    switch (dtype)
    {
    case INT32_T:
        if (src > INT32_MAX)
        {
            return false;
        }
        *((int32_t *)dst) = (int32_t)src;
        return true;
    case UINT32_T:
        if (src > UINT32_MAX)
        {
            return false;
        }
        *((uint32_t *)dst) = (uint32_t)src;
        return true;
    case INT64_T:
        if (src > INT64_MAX)
        {
            return false;
        }
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case FLOAT32_T:
        *((float *)dst) = (float)src;
        return true;
    case FLOAT64_T:
        *((double *)dst) = (double)src;
        return true;
    default:
        return false;
    }
}

static inline bool tensor_cast_copy_float32(void *dst, tensor_dtype_t dtype, float src)
{
    switch (dtype)
    {
    case INT32_T:
        if (isinf(src) || isnan(src) || src < INT32_MIN || src > INT32_MAX)
        {
            return false;
        }
        *((int32_t *)dst) = (int32_t)src;
        return true;
    case UINT32_T:
        if (isinf(src) || isnan(src) || src < 0 || src > UINT32_MAX)
        {
            return false;
        }
        *((uint32_t *)dst) = (uint32_t)src;
        return true;
    case INT64_T:
        if (isinf(src) || isnan(src) || src < INT64_MIN || src > INT64_MAX)
        {
            return false;
        }
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case UINT64_T:
        if (isinf(src) || isnan(src) || src < 0 || src > UINT64_MAX)
        {
            return false;
        }
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case FLOAT64_T:
        *((double *)dst) = (double)src;
        return true;
    default:
        return false;
    }
}

static inline bool tensor_cast_copy_float64(void *dst, tensor_dtype_t dtype, double src)
{
    switch (dtype)
    {
    case INT32_T:
        if (isinf(src) || isnan(src) || src < INT32_MIN || src > INT32_MAX)
        {
            return false;
        }
        *((int32_t *)dst) = (int32_t)src;
        return true;
    case UINT32_T:
        if (isinf(src) || isnan(src) || src < 0 || src > UINT32_MAX)
        {
            return false;
        }
        *((uint32_t *)dst) = (uint32_t)src;
        return true;
    case INT64_T:
        if (isinf(src) || isnan(src) || src < INT64_MIN || src > INT64_MAX)
        {
            return false;
        }
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case UINT64_T:
        if (isinf(src) || isnan(src) || src < 0 || src > UINT64_MAX)
        {
            return false;
        }
        *((int64_t *)dst) = (int64_t)src;
        return true;
    case FLOAT32_T:
        *((float *)dst) = (float)src;
        return true;
    default:
        return false;
    }
}

// Copy from source to destination, casting as necessary
// Returns true on success, or false if the cast is not supported or an overflow occurred
static inline bool tensor_cast_copy(void *dst, tensor_dtype_t dtype, void *src, tensor_dtype_t stype)
{
    assert(dst != NULL);
    assert(src != NULL);

    // Simple case where types are the same - copy the value
    if (stype == dtype)
    {
        memcpy(dst, src, tensor_dtype_sizeof(dtype));
        return true;
    }

    switch (stype)
    {
    case INT32_T:
        return tensor_cast_copy_int32(dst, dtype, *((int32_t *)src));
    case UINT32_T:
        return tensor_cast_copy_uint32(dst, dtype, *((uint32_t *)src));
    case INT64_T:
        return tensor_cast_copy_int64(dst, dtype, *((int64_t *)src));
    case UINT64_T:
        return tensor_cast_copy_uint64(dst, dtype, *((uint64_t *)src));
    case FLOAT32_T:
        return tensor_cast_copy_uint64(dst, dtype, *((float *)src));
    case FLOAT64_T:
        return tensor_cast_copy_uint64(dst, dtype, *((double *)src));
    default:
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - CREATE

tensor_t *tensor_cast(tensor_pool_t *pool, tensor_dtype_t type, tensor_t *a)
{
    assert(pool != NULL);
    assert(a != NULL);

    // Return same tensor if already same type
    if (a->dtype == type)
    {
        return a;
    }

    // Create a new tensor with the same dimensions
    tensor_t *t = tensor_dtype_create(pool, type, a->dims, NULL);
    if (t == NULL)
    {
        return NULL;
    }

    // Set the operation to CAST, and dependency to a
    t->op = CAST;
    t->a = a;

    return t;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - EVALUATE

bool tensor_cast_op(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);
    assert(t->a != NULL);
    assert(t->nvalues == t->a->nvalues);

    void *src = t->a->data;
    void *dst = t->data;
    for (uint32_t i = 0; i < t->nvalues; i++, src += tensor_dtype_sizeof(t->a->dtype), dst += tensor_dtype_sizeof(t->dtype))
    {
        if (!tensor_cast_copy(dst, t->dtype, src, t->a->dtype))
        {
            debug("tensor_cast_op: tensor<%d>: cast failed from %s to %s\n", tensor_id(t), tensor_dtype_str(t->a->dtype), tensor_dtype_str(t->dtype));
            return false;
        }
    }

    // Success
    return true;
}
