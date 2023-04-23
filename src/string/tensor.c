#include <stdlib.h>
#include <string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static bool tensor_str_print_dtype(tensor_str_t *str, tensor_dtype_t type, void *data)
{
    assert(str);
    assert(data);

    switch (type)
    {
    case UINT32_T:
        return tensor_str_printf(str, "%u", *(uint32_t *)data);
    case INT32_T:
        return tensor_str_printf(str, "%d", *(int32_t *)data);
    case UINT64_T:
        return tensor_str_printf(str, "%lu", *(uint64_t *)data);
    case INT64_T:
        return tensor_str_printf(str, "%ld", *(int64_t *)data);
    case FLOAT32_T:
        return tensor_str_printf(str, "%.4f", *(float *)data);
    case FLOAT64_T:
        return tensor_str_printf(str, "%.4lf", *(double *)data);
    default:
        return false;
    }
}

static const char *tensor_type_str(tensor_t *tensor)
{
    assert(tensor);

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

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

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
    assert(pool);
    assert(tensor);

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
    assert(pool);
    assert(tensor);
    assert(tensor->data);

    tensor_str_t *str = tensor_str_create(pool, NULL);
    if (str == NULL)
    {
        return NULL;
    }

    // If the tensor is a scalar, print it
    if (tensor_is_scalar(tensor))
    {
        return tensor_str_print_dtype(str, tensor->dtype, tensor->data) ? str : NULL;
    }
    if (!tensor_str_printf(str, "["))
    {
        return NULL;
    }

    void *data = tensor->data;
    assert(data);
    for (uint32_t i = 0; i < tensor->nvalues; i++, data += tensor_dtype_sizeof(tensor->dtype))
    {
        if (!tensor_str_print_dtype(str, tensor->dtype, data))
        {
            tensor_str_zero(str);
            return NULL;
        }
        if (i < tensor->nvalues - 1)
        {
            if (!tensor_str_printf(str, ","))
            {
                tensor_str_zero(str);
                return NULL;
            }
        }
    }

    if (!tensor_str_printf(str, "]"))
    {
        tensor_str_zero(str);
        return NULL;
    }
    return str;
}

/**
tensor_str_t *tensor_str_print(tensor_pool_t *pool, tensor_t *tensor)
{
    assert(pool);
    assert(tensor);
    assert(tensor->data);

    tensor_str_t *str = tensor_str_create(pool, NULL);
    if (str == NULL)
    {
        return NULL;
    }

    // If the tensor is a scalar, print it
    if (tensor_is_scalar(tensor))
    {
        return tensor_str_print_dtype(str, tensor->dtype, tensor->data) ? str : NULL;
    }

    void *data = tensor->data;
    uint32_t index[tensor->ndims];
    memset(index, 0, sizeof(uint32_t) * tensor->ndims);
    for (uint8_t i = 0; i < tensor->nvalues; i++)
    {
        // Print a '[' for each index which is zero
        for (uint8_t j = 0; j < tensor->ndims; j++)
        {
            if (index[j] == 0)
            {
                if (!tensor_str_printf(str, "["))
                {
                    return NULL;
                }
            }
        }

        // Print the element
        if (!tensor_str_print_dtype(str, tensor->dtype, data))
        {
            return NULL;
        }

        // Print a ']' for each index which is maximum, else print a ,
        bool printed_comma = true;
        for (uint8_t j = 0; j < tensor->ndims; j++)
        {
            if (index[j] == tensor->dims[j] - 1)
            {
                printed_comma = false;
                if (!tensor_str_printf(str, "]"))
                {
                    return NULL;
                }
            }
        }

        // Append a value separator
        if (printed_comma)
        {
            if (!tensor_str_printf(str, ","))
            {
                return NULL;
            }
        }

        // Increment the index
        for (uint8_t j = 0; j < tensor->ndims; j++)
        {
            index[j]++;
            if (index[j] < tensor->dims[j])
            {
                break;
            }
            else
            {
                index[j] = 0;
            }
        }

        // Next element
        data += tensor_dtype_sizeof(tensor->dtype);
    }

    return str;
}
*/