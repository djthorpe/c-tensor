#include <stdlib.h>
#include <assert.h>
#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static size_t tensor_dtype_sizeof(tensor_dtype_t dtype)
{
    switch (dtype)
    {
    case UINT32_T:
        return sizeof(uint32_t);
    case INT32_T:
        return sizeof(int32_t);
    case UINT64_T:
        return sizeof(uint64_t);
    case INT64_T:
        return sizeof(int64_t);
    case FLOAT32_T:
        return sizeof(float);
    case FLOAT64_T:
        return sizeof(double);
    default:
        return 0;
    }
}

static const char *tensor_dtype_str(tensor_dtype_t dtype)
{
    switch (dtype)
    {
    case UINT32_T:
        return "uint32_t";
    case INT32_T:
        return "int32_t";
    case UINT64_T:
        return "uint64_t";
    case INT64_T:
        return "int64_t";
    case FLOAT32_T:
        return "float";
    case FLOAT64_T:
        return "double";
    default:
        return NULL;
    }
}

static tensor_t *tensor_dtype_create(tensor_pool_t *pool, tensor_dtype_t dtype, uint32_t *dims)
{
    assert(pool != NULL);
    assert(dims != NULL);

    // Calculate number of elements
    size_t size = 0;
    uint8_t ndims = -1;
    while (dims[++ndims] != 0)
    {
        if (size == 0)
        {
            size = dims[ndims];
        }
        else
        {
            size *= dims[ndims];
        }
    }

    // Return NULL if no dimensions or too many dimensions
    if (ndims == 0 || ndims > TENSOR_MAX_DIMS)
    {
        return NULL;
    }

    // Allocate memory for tensor
    tensor_t *t = tensor_pool_alloc(pool, sizeof(tensor_t));
    if (t == NULL)
    {
        return NULL;
    }

    // Allocate memory for data
    t->data = tensor_pool_alloc(pool, size * tensor_dtype_sizeof(dtype));
    if (t->data == NULL)
    {
        return NULL;
    }

    // Set tensor properties
    t->dtype = dtype;
    t->ndims = ndims;
    for (uint8_t i = 0; i < ndims; i++)
    {
        t->dims[i] = dims[i];
    }

    tensor_debug(pool, "dtype=%s ndims=%d size=%d\n", tensor_dtype_str(dtype), ndims, size);

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

inline tensor_t *tensor_create_int32(tensor_pool_t *pool, uint32_t *dims)
{
    return tensor_dtype_create(pool, INT32_T, dims);
}

inline tensor_t *tensor_create_uint32(tensor_pool_t *pool, uint32_t *dims)
{
    return tensor_dtype_create(pool, UINT32_T, dims);
}

inline tensor_t *tensor_create_int64(tensor_pool_t *pool, uint32_t *dims)
{
    return tensor_dtype_create(pool, INT64_T, dims);
}

inline tensor_t *tensor_create_uint64(tensor_pool_t *pool, uint32_t *dims)
{
    return tensor_dtype_create(pool, UINT64_T, dims);
}

inline tensor_t *tensor_create_float32(tensor_pool_t *pool, uint32_t *dims)
{
    return tensor_dtype_create(pool, FLOAT32_T, dims);
}

inline tensor_t *tensor_create_float64(tensor_pool_t *pool, uint32_t *dims)
{
    return tensor_dtype_create(pool, FLOAT64_T, dims);
}

tensor_str_t *tensor_describe(tensor_pool_t *pool,tensor_t * tensor) {
    assert(pool != NULL);
    assert(tensor != NULL);

    tensor_str_t *str = tensor_sprintf(pool, "tensor<%s>", tensor_dtype_str(tensor->dtype));
    return str;
}
