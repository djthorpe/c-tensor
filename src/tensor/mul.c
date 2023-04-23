#include <stdlib.h>
#include <string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static tensor_t *tensor_mul_scalar(tensor_pool_t *pool, tensor_t *a, tensor_t *b)
{
    assert(pool != NULL);
    assert(a != NULL);
    assert(b != NULL);

    // Create a new tensor with the same dimensions
    tensor_t *t = tensor_dtype_create(pool, a->dtype, a->dims, NULL);
    if (t == NULL)
    {
        return NULL;
    }

    // Set the operation to MUL_SCALAR, and dependecies to a and b
    t->op = MUL_SCALAR;
    t->a = a;
    t->b = b;

    return t;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

tensor_t *tensor_mul(tensor_pool_t *pool, tensor_t *a, tensor_t *b)
{
    assert(pool != NULL);
    assert(a != NULL);
    assert(b != NULL);

    // If the tensors are not the same type, then return NULL
    if (a->dtype != b->dtype)
    {
        debug("tensor_mul: tensors are not the same dtype\n");
        return NULL;
    }

    // Check for scalar values
    if (tensor_is_scalar(a))
    {
        return tensor_mul_scalar(pool, b, a);
    }
    if (tensor_is_scalar(b))
    {
        return tensor_mul_scalar(pool, a, b);
    }

    // Check for same number of dimensions
    if (a->ndims != b->ndims)
    {
        debug("tensor_mul: tensors do not have same number of dimensions\n");
        return NULL;
    }

    // Check for same dimensions
    for (uint8_t i = 0; i < a->ndims; i++)
    {
        if (a->dims[i] != b->dims[i])
        {
            debug("tensor_mul: tensors do not have same shape\n");
            return NULL;
        }
    }

    // Create a new tensor with the same dimensions
    tensor_t *t = tensor_dtype_create(pool, a->dtype, a->dims, NULL);
    if (t == NULL)
    {
        return NULL;
    }

    // Set the operation to MUL_MATRIX, and dependecies to a and b
    t->op = MUL_MATRIX;
    t->a = a;
    t->b = b;

    return t;
}

static bool tensor_mul_op_scalar_int32(int32_t *data, uint32_t nvalues, int32_t b)
{
    for (uint32_t i = 0; i < nvalues; i++)
    {
        data[i] *= b;
    }
    return true;
}

static bool tensor_mul_op_scalar_uint32(uint32_t *data, uint32_t nvalues, uint32_t b)
{
    for (uint32_t i = 0; i < nvalues; i++)
    {
        data[i] *= b;
    }
    return true;
}

static bool tensor_mul_op_scalar_int64(int64_t *data, uint32_t nvalues, int64_t b)
{
    for (uint32_t i = 0; i < nvalues; i++)
    {
        data[i] *= b;
    }
    return true;
}

static bool tensor_mul_op_scalar_uint64(uint64_t *data, uint32_t nvalues, uint64_t b)
{
    for (uint32_t i = 0; i < nvalues; i++)
    {
        data[i] *= b;
    }
    return true;
}

static bool tensor_mul_op_scalar_float32(float *data, uint32_t nvalues, float b)
{
    for (uint32_t i = 0; i < nvalues; i++)
    {
        data[i] *= b;
    }
    return true;
}

static bool tensor_mul_op_scalar_float64(double *data, uint32_t nvalues, double b)
{
    for (uint32_t i = 0; i < nvalues; i++)
    {
        data[i] *= b;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - EVALUATE

bool tensor_mul_op_scalar(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);
    assert(t->a != NULL);
    assert(t->b != NULL);
    assert(t->dtype == t->a->dtype && t->a->dtype == t->b->dtype);
    assert(tensor_is_scalar(t->b));

    switch (t->dtype)
    {
    case INT32_T:
        return tensor_mul_op_scalar_int32((int32_t *)t->a->data, t->a->nvalues, tensor_int32_value(t->b));
    case UINT32_T:
        return tensor_mul_op_scalar_uint32((uint32_t *)t->a->data, t->a->nvalues, tensor_uint32_value(t->b));
    case INT64_T:
        return tensor_mul_op_scalar_int64((int64_t *)t->a->data, t->a->nvalues, tensor_int64_value(t->b));
    case UINT64_T:
        return tensor_mul_op_scalar_uint64((uint64_t *)t->a->data, t->a->nvalues, tensor_uint64_value(t->b));
    case FLOAT32_T:
        return tensor_mul_op_scalar_float32((float *)t->a->data, t->a->nvalues, tensor_float32_value(t->b));
    case FLOAT64_T:
        return tensor_mul_op_scalar_float64((double *)t->a->data, t->a->nvalues, tensor_float64_value(t->b));
    default:
        return false;
    }
}

bool tensor_mul_op_matrix(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);
    assert(t->a != NULL);
    assert(t->b != NULL);
    assert(t->dtype == t->a->dtype && t->a->dtype == t->b->dtype);
    assert(t->ndims == t->a->ndims && t->a->ndims == t->b->ndims);

    // TODO: Implement matrix multiplication

    // Success
    return false;
}
