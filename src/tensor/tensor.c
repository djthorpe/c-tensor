#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

static tensor_t *tensor_dtype_vec(tensor_pool_t *pool, tensor_dtype_t type,void* values, uint32_t nelems) {
    assert(pool != NULL);
    assert(values != NULL);
    assert(nelems > 0);
    assert(tensor_dtype_sizeof(type) > 0);

    tensor_t *t = tensor_dtype_create(pool, type, (uint32_t[]){nelems,0});
    if (t == NULL)
    {
        return NULL;
    }
    memcpy(t->data, values, tensor_dtype_sizeof(type) * (size_t)nelems);
    return t;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

tensor_t *tensor_dtype_create(tensor_pool_t *pool, tensor_dtype_t dtype, uint32_t *dims)
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

    // Check for limits
    assert(size <= UINT32_MAX);

    // Return NULL if no dimensions or too many dimensions
    if (ndims == 0 || ndims > TENSOR_MAX_DIMS)
    {
        tensor_debug(pool, "tensor_dtype_create failed, ndims=%d\n", ndims);
        return NULL;
    }

    // Allocate memory for tensor
    tensor_t *t = tensor_pool_alloc(pool, sizeof(tensor_t));
    if (t == NULL)
    {
        tensor_debug(pool, "tensor_dtype_create failed, out of memory allocating %ld bytes\n", sizeof(tensor_t));
        return NULL;
    }

    // Allocate memory for data
    t->data = tensor_pool_alloc(pool, size * tensor_dtype_sizeof(dtype));
    if (t->data == NULL)
    {
        tensor_debug(pool, "tensor_dtype_create failed, out of memory allocating %ld bytes\n", size * tensor_dtype_sizeof(dtype));
        return NULL;
    }
    else
    {
        memset(t->data, 0, size * tensor_dtype_sizeof(dtype));
    }

    // Set tensor properties
    t->dtype = dtype;
    t->ndims = ndims;
    t->nvalues = size;
    for (uint8_t i = 0; i < ndims; i++)
    {
        t->dims[i] = dims[i];
    }
    t->dims[ndims] = 0;
    t->op = NONE;
    
    // Return success
    return t;
}

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

tensor_t *tensor_int32(tensor_pool_t *pool, int32_t value)
{
    assert(pool != NULL);
    tensor_t *t = tensor_dtype_create(pool, INT32_T, (uint32_t[]){1, 0});
    if (t == NULL)
    {
        return NULL;
    }
    *((int32_t *)t->data) = value;
    return t;
}

tensor_t *tensor_uint32(tensor_pool_t *pool, uint32_t value)
{
    assert(pool != NULL);
    tensor_t *t = tensor_dtype_create(pool, UINT32_T, (uint32_t[]){1, 0});
    if (t == NULL)
    {
        return NULL;
    }
    *((uint32_t *)t->data) = value;
    return t;
}

tensor_t *tensor_int64(tensor_pool_t *pool, int64_t value)
{
    assert(pool != NULL);
    tensor_t *t = tensor_dtype_create(pool, INT64_T, (uint32_t[]){1, 0});
    if (t == NULL)
    {
        return NULL;
    }
    *((int64_t *)t->data) = value;
    return t;
}

tensor_t *tensor_uint64(tensor_pool_t *pool, uint64_t value)
{
    assert(pool != NULL);
    tensor_t *t = tensor_dtype_create(pool, UINT64_T, (uint32_t[]){1, 0});
    if (t == NULL)
    {
        return NULL;
    }
    *((uint64_t *)t->data) = value;
    return t;
}

tensor_t *tensor_float32(tensor_pool_t *pool, float value)
{
    assert(pool != NULL);
    tensor_t *t = tensor_dtype_create(pool, FLOAT32_T, (uint32_t[]){1, 0});
    if (t == NULL)
    {
        return NULL;
    }
    *((float *)t->data) = value;
    return t;
}

tensor_t *tensor_float64(tensor_pool_t *pool, double value)
{
    assert(pool != NULL);
    tensor_t *t = tensor_dtype_create(pool, FLOAT64_T, (uint32_t[]){1, 0});
    if (t == NULL)
    {
        return NULL;
    }
    *((double *)t->data) = value;
    return t;
}

inline tensor_t *tensor_int32_vec(tensor_pool_t *pool, int32_t* values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, INT32_T, values, nelems);
}

inline tensor_t *tensor_uint32_vec(tensor_pool_t *pool, uint32_t* values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, UINT32_T, values, nelems);
}

inline tensor_t *tensor_int64_vec(tensor_pool_t *pool, int64_t* values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, INT64_T, values, nelems);
}

inline tensor_t *tensor_uint64_vec(tensor_pool_t *pool, uint64_t* values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, UINT64_T, values, nelems);
}

inline tensor_t *tensor_float32_vec(tensor_pool_t *pool, float* values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, FLOAT32_T, values, nelems);
}

inline tensor_t *tensor_float64_vec(tensor_pool_t *pool, double* values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, FLOAT64_T, values, nelems);
}

tensor_str_t *tensor_describe(tensor_pool_t *pool, tensor_t *tensor)
{
    assert(pool != NULL);
    assert(tensor != NULL);

    tensor_str_t *str = tensor_sprintf(pool, "tensor<%s>", tensor_dtype_str(tensor->dtype));
    if (str == NULL)
    {
        return NULL;
    }

    void *data = tensor->data;
    for (uint8_t i = 0; i < tensor->nvalues; i++)
    {
        if (!tensor_strcat_dtype(str, tensor->dtype, data))
        {
            return NULL;
        }
        if (!tensor_strcat_cstr(str, ","))
        {
            return NULL;
        }
        data += tensor_dtype_sizeof(tensor->dtype);
    }

    return str;
}

// Return true if the tensor is a scalar
inline bool tensor_is_scalar(tensor_t *t) {
    assert(t != NULL);
    return t->ndims == 1 && t->dims[0] == 1;
}

// Return true if the tensor is a vector
inline bool tensor_is_vector(tensor_t *t) {
    assert(t != NULL);
    return t->ndims == 1 && t->dims[0] > 1;
}
