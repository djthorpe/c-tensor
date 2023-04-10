#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static tensor_t *tensor_mul_scalar(tensor_pool_t *pool, tensor_t *a, tensor_t *b)
{
    assert(pool != NULL);
    assert(a != NULL);
    assert(b != NULL);

    // Create a new tensor with the same dimensions
    tensor_t *t = tensor_dtype_create(pool, a->dtype, a->dims);
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
        tensor_debug(pool, "tensor_mul: tensors are not the same dtype");
        return NULL;
    }

    // Check for scalar values
    if (tensor_is_scalar(a)) {
        return tensor_mul_scalar(pool, b, a);
    }
    if (tensor_is_scalar(b)) {
        return tensor_mul_scalar(pool, a, b);
    }

    // Check for same number of dimensions
    if (a->ndims != b->ndims)
    {
        tensor_debug(pool, "tensor_mul: tensors do not have same number of dimensions");
        return NULL;
    }

    // Check for same dimensions
    for (uint8_t i = 0; i < a->ndims; i++) {
        if (a->dims[i] != b->dims[i]) {
            tensor_debug(pool, "tensor_mul: tensors do not have same shape");
            return NULL;
        }
    }

    // Create a new tensor with the same dimensions
    tensor_t *t = tensor_dtype_create(pool, a->dtype, a->dims);
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

    // Success
    return false;
}

bool tensor_mul_op_matrix(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);
    assert(t->a != NULL);
    assert(t->b != NULL);
    assert(t->dtype == t->a->dtype &&  t->a->dtype == t->b->dtype);
    assert(t->ndims == t->a->ndims && t->a->ndims == t->b->ndims);

    // Success
    return false;
}
