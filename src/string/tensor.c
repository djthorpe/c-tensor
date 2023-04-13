#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

static const char *tensor_type_str(tensor_t *tensor)
{
    assert(tensor != NULL);

    if (tensor->op == NONE)
    {
        if (tensor_is_scalar(tensor))
        {
            return "scalar";
        }
        else if (tensor_is_vector(tensor))
        {
            return "vector";
        }
        else
        {
            return "tensor";
        }
    }
    return tensor_op_str(tensor->op);
}

const char *tensor_dtype_str(tensor_dtype_t dtype)
{
    switch (dtype)
    {
    case UINT32_T:
        return "uint32";
    case INT32_T:
        return "int32";
    case UINT64_T:
        return "uint64";
    case INT64_T:
        return "int64";
    case FLOAT32_T:
        return "float32";
    case FLOAT64_T:
        return "float64";
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
        return "mulscalar";
    case MUL_MATRIX:
        return "mulmatrix";
    default:
        return "input";
    }
}

/**
 * Describe a tensor
 */
tensor_str_t *tensor_str_describe(tensor_pool_t *pool, tensor_t *tensor)
{
    assert(pool != NULL);
    assert(tensor != NULL);

    tensor_str_t *str = tensor_str_create(pool, NULL);
    if (str == NULL)
    {
        return NULL;
    }

    if (!tensor_str_printf(str, "%s[id=%u dtype=%s", tensor_type_str(tensor), tensor->id, tensor_dtype_str(tensor->dtype)))
    {
        return NULL;
    }
    if (!tensor_str_printf(str, "]"))
    {
        return NULL;
    }

    // Return success
    return str;
}

/**
 * Return a tensor value as a string
 */
tensor_str_t *tensor_str_print(tensor_pool_t *pool, tensor_t *tensor)
{
    return NULL;
}
