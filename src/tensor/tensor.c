#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tensor_private.h"

#define buf_size 80
static char buf[buf_size];

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Unique identifier for a tensor
inline uint32_t tensor_id(tensor_t *t)
{
    assert(t != NULL);
    return t->id;
}

size_t tensor_dtype_sizeof(tensor_dtype_t dtype)
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

tensor_t *tensor_dtype_create(tensor_pool_t *pool, tensor_dtype_t dtype, uint32_t *dims, void *elems)
{
    assert(pool != NULL);
    assert(tensor_dtype_sizeof(dtype) > 0);

    // Check for scalar
    size_t size = 0;
    uint8_t ndims = -1;
    if (dims == NULL || dims[0] == 0)
    {
        size = 1;
        ndims = 0;
    }
    else
    {
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
    }

    // Check for limits
    assert(size <= UINT32_MAX);

    // If no size, then return NULL
    if (size == 0)
    {
        tensor_debug(pool, "tensor_dtype_create failed, zero size\n");
        return NULL;
    }

    // Return NULL if no dimensions or too many dimensions
    if (ndims > TENSOR_MAX_DIMS)
    {
        tensor_debug(pool, "tensor_dtype_create failed, ndims=%d\n", ndims);
        return NULL;
    }

    // Allocate memory for tensor
    uint32_t id;
    tensor_t *t = tensor_pool_alloc(pool, sizeof(tensor_t), &id);
    if (t == NULL)
    {
        tensor_debug(pool, "tensor_dtype_create failed, out of memory allocating %ld bytes\n", sizeof(tensor_t));
        return NULL;
    }

    // Allocate memory for data and set it
    t->data = tensor_pool_alloc(pool, size * tensor_dtype_sizeof(dtype), NULL);
    if (t->data == NULL)
    {
        tensor_debug(pool, "tensor_dtype_create failed, out of memory allocating %ld bytes\n", size * tensor_dtype_sizeof(dtype));
        return NULL;
    }
    else if (elems != NULL)
    {
        memcpy(t->data, elems, size * tensor_dtype_sizeof(dtype));
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
    t->id = id;

    // Return success
    return t;
}

/**
 * Create a int32 tensor
 */
inline tensor_t *tensor_create_int32(tensor_pool_t *pool, uint32_t *dims, int32_t *elems) {
    return tensor_dtype_create(pool, INT32_T, dims, elems);
}

/**
 * Create a uint32 tensor
 */
inline tensor_t *tensor_create_uint32(tensor_pool_t *pool, uint32_t *dims, uint32_t *elems) {
    return tensor_dtype_create(pool, INT32_T, dims, elems);
}

/**
 * Create a int64 tensor
 */
inline tensor_t *tensor_create_int64(tensor_pool_t *pool, uint32_t *dims, int64_t *elems) {
    return tensor_dtype_create(pool, INT64_T, dims, elems);
}

/**
 * Create a uint64 tensor
 */
inline tensor_t *tensor_create_uint64(tensor_pool_t *pool, uint32_t *dims, uint64_t *elems) {
    return tensor_dtype_create(pool, UINT64_T, dims, elems);
}

/**
 * Create a float32 tensor
 */
inline tensor_t *tensor_create_float32(tensor_pool_t *pool, uint32_t *dims, float *elems) {
    return tensor_dtype_create(pool, FLOAT32_T, dims, elems);
}

/**
 * Create a float64 tensor
 */
inline tensor_t *tensor_create_float64(tensor_pool_t *pool, uint32_t *dims, double *elems) {
    return tensor_dtype_create(pool, FLOAT64_T, dims, elems);
}

// Return true if the tensor is a scalar
inline bool tensor_is_scalar(tensor_t *t)
{
    assert(t != NULL);
    return t->ndims == 0;
}

// Return true if the tensor is a vector
inline bool tensor_is_vector(tensor_t *t)
{
    assert(t != NULL);
    return t->ndims == 1;
}

/**
 * Return number of tensor dimensions
 */
inline uint8_t tensor_ndims(tensor_t *t) {
    assert(t);
    return t->ndims;
}

/**
 * Return number of tensor elements
 */
inline uint32_t tensor_nelems(tensor_t *t) {
    assert(t);
    return t->nvalues;
}

// Evaluate the tensor values from the input tensors and the
// operation. The tensor values are stored in the tensor data
// return true on successful evaluation
bool tensor_evaluate(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);
    bool success = false;

    switch (t->op)
    {
    case NONE:
        success = true;
        break;
    case CAST:
        assert(t->a != NULL);
        success = tensor_cast_op(pool, t);
        break;
    case MUL_MATRIX:
        assert(t->a != NULL);
        assert(t->b != NULL);
        assert(t->a->dtype == t->b->dtype);
        success = tensor_mul_op_matrix(pool, t);
        break;
    case MUL_SCALAR:
        assert(t->a != NULL);
        assert(t->b != NULL);
        assert(t->a->dtype == t->b->dtype);
        assert(tensor_is_scalar(t->b));
        success = tensor_mul_op_scalar(pool, t);
        break;
    default:
        assert(false);
    }
    if (success)
    {
        tensor_debug(pool, "  tensor_evaluate: %s\n", tensor_cstring(buf, buf_size, tensor_str_describe(pool, t)));
    }
    else
    {
        tensor_debug(pool, "  tensor_evaluate: failed for %s\n", tensor_cstring(buf, buf_size, tensor_str_describe(pool, t)));
    }
    return success;
}
