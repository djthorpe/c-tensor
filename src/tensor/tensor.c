#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static tensor_t *tensor_dtype_vec(tensor_pool_t *pool, tensor_dtype_t type, void *values, uint32_t nelems)
{
    assert(pool != NULL);
    assert(values != NULL);
    assert(nelems > 0);
    assert(tensor_dtype_sizeof(type) > 0);

    tensor_t *t = tensor_dtype_create(pool, type, (uint32_t[]){nelems, 0});
    if (t == NULL)
    {
        return NULL;
    }
    memcpy(t->data, values, tensor_dtype_sizeof(type) * (size_t)nelems);
    return t;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS


const char *tensor_dtype_str(tensor_dtype_t dtype)
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
        return "float32_t";
    case FLOAT64_T:
        return "float64_t";
    default:
        return NULL;
    }
}

const char *tensor_op_str(tensor_op_t op)
{
    switch (op)
    {
    case CAST:
        return "cast";
    case MUL_SCALAR:
        return "mul_scalar";
    case MUL_MATRIX:
        return "mul_matrix";
    default:
        return "input";
    }
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
    uint32_t id;
    tensor_t *t = tensor_pool_alloc(pool, sizeof(tensor_t), &id);
    if (t == NULL)
    {
        tensor_debug(pool, "tensor_dtype_create failed, out of memory allocating %ld bytes\n", sizeof(tensor_t));
        return NULL;
    }

    // Allocate memory for data
    t->data = tensor_pool_alloc(pool, size * tensor_dtype_sizeof(dtype), NULL);
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
    t->id = id;

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

inline tensor_t *tensor_int32_vec(tensor_pool_t *pool, int32_t *values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, INT32_T, values, nelems);
}

inline tensor_t *tensor_uint32_vec(tensor_pool_t *pool, uint32_t *values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, UINT32_T, values, nelems);
}

inline tensor_t *tensor_int64_vec(tensor_pool_t *pool, int64_t *values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, INT64_T, values, nelems);
}

inline tensor_t *tensor_uint64_vec(tensor_pool_t *pool, uint64_t *values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, UINT64_T, values, nelems);
}

inline tensor_t *tensor_float32_vec(tensor_pool_t *pool, float *values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, FLOAT32_T, values, nelems);
}

inline tensor_t *tensor_float64_vec(tensor_pool_t *pool, double *values, uint32_t nelems)
{
    return tensor_dtype_vec(pool, FLOAT64_T, values, nelems);
}

// Return true if the tensor is a scalar
inline bool tensor_is_scalar(tensor_t *t)
{
    assert(t != NULL);
    return t->ndims == 1 && t->dims[0] == 1;
}

// Return true if the tensor is a vector
inline bool tensor_is_vector(tensor_t *t)
{
    assert(t != NULL);
    return t->ndims == 1 && t->dims[0] > 1;
}

// Evaluate the tensor values from the input tensors and the
// operation. The tensor values are stored in the tensor data
void tensor_evaluate(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);
    switch (t->op)
    {
    case NONE:
        // This is an input node
        break;
    case CAST:
        assert(t->a != NULL);
        tensor_cast_op(pool, t);
        break;
    case MUL_MATRIX:
        assert(t->a != NULL);
        assert(t->b != NULL);
        assert(t->a->dtype == t->b->dtype);
        // TODO: Multiply two matrices with the same dimensions
        tensor_debug(pool, "  tensor[%u] multiply tensor[%u] with tensor[%u]\n", t->id, t->a->id, t->b->id);
        break;
    case MUL_SCALAR:
        assert(t->a != NULL);
        assert(t->b != NULL);
        assert(t->a->dtype == t->b->dtype);
        assert(tensor_is_scalar(t->b));
        // TODO: Multiply a matrix a with scalar values in b
        tensor_debug(pool, "  tensor[%u] multiply tensor[%u] with scalar[%u]\n", t->id, t->a->id, t->b->id);
        break;
    default:
        assert(false);
    }
    tensor_debug(pool, "  tensor_evaluate: %s\n", tensor_cstring(tensor_str_print(pool, t)));
}

// Return a scalar tensor with the value of the tensor
inline int32_t tensor_int32_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == INT32_T);
    assert(tensor_is_scalar(t));
    return *((int32_t *)t->data);
}

inline uint32_t tensor_uint32_value(tensor_t *t) {
    assert(t != NULL);
    assert(t->dtype == UINT32_T);
    assert(tensor_is_scalar(t));
    return *((uint32_t *)t->data);
}

inline int64_t tensor_int64_value(tensor_t *t) {
    assert(t != NULL);
    assert(t->dtype == INT64_T);
    assert(tensor_is_scalar(t));
    return *((int64_t *)t->data);
}
inline uint64_t tensor_uint64_value(tensor_t *t) {
    assert(t != NULL);
    assert(t->dtype == UINT64_T);
    assert(tensor_is_scalar(t));
    return *((uint64_t *)t->data);
}
inline float tensor_float32_value(tensor_t *t) {
    assert(t != NULL);
    assert(t->dtype == FLOAT32_T);
    assert(tensor_is_scalar(t));
    return *((float *)t->data);
}

inline double tensor_float64_value(tensor_t *t) {
    assert(t != NULL);
    assert(t->dtype == FLOAT64_T);
    assert(tensor_is_scalar(t));
    return *((double *)t->data);
}
