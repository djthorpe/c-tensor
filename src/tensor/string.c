#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

#define MAX_CHARS 80

// Return a value
// TODO: We use a global buffer here, so not thread safe. Need to put a guard
// around this.
static char tensor_cstring_value_buf[MAX_CHARS];

static const char *tensor_cstring_value(tensor_dtype_t dtype, void* value) {
    int len = -1;
    assert(value != NULL);
    switch (dtype) {
        case UINT32_T:
            len = snprintf(tensor_cstring_value_buf, MAX_CHARS, "%u", *(uint32_t*)value);
            break;
        case INT32_T:
            len = snprintf(tensor_cstring_value_buf, MAX_CHARS, "%d", *(int32_t*)value);
            break;
        case UINT64_T:
            len = snprintf(tensor_cstring_value_buf, MAX_CHARS, "%lu", *(uint64_t*)value);
            break;
        case INT64_T:
            len = snprintf(tensor_cstring_value_buf, MAX_CHARS, "%ld", *(int64_t*)value);
            break;
        case FLOAT32_T:
            len = snprintf(tensor_cstring_value_buf, MAX_CHARS, "%f", *(float*)value);
            break;
        case FLOAT64_T:
            len = snprintf(tensor_cstring_value_buf, MAX_CHARS, "%lf", *(double*)value);
            break;
        default:
            return NULL;
    }
    if (len < 0) {
        return NULL;
    }
    if (len >= MAX_CHARS) {
        return NULL;
    }
    return tensor_cstring_value_buf;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

tensor_str_t *tensor_sprintf(tensor_pool_t *pool, const char *fmt, ...)
{
    assert(pool != NULL);
    assert(fmt != NULL);

    va_list args;
    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    tensor_str_t *str = tensor_pool_alloc_str(pool, len + 1);
    if (str == NULL)
    {
        return NULL;
    }

    va_start(args, fmt);
    vsnprintf(str->data, len + 1, fmt, args);
    va_end(args);

    return str;
}

const char *tensor_cstring(tensor_str_t *str)
{
    assert(str != NULL);
    return str->data;
}

// Concatenate a string representation of a value to a string. Returns the string
// again or NULL if the allocation failed.
tensor_str_t* tensor_strcat_dtype(tensor_str_t *str, tensor_dtype_t dtype, void* value) {
    assert(str != NULL);
    assert(value != NULL);
    
    // Create the value
    const char *value_str = tensor_cstring_value(dtype, value);
    if (value_str == NULL) {
        return NULL;
    }

    // Reallocate
    void* new = realloc(str->data, str->size + strlen(value_str));
    if (new == NULL) {
        return NULL;
    } else {
        str->data = new;
        str->size += strlen(value_str);
    }

    // Append
    strcat(str->data, value_str);

    // Return success
    return str;
}

// Concatenate a cstring value to a string. Returns the string
// again or NULL if the allocation failed.
tensor_str_t* tensor_strcat_cstr(tensor_str_t *str, const char* value) {
    assert(str != NULL);
    assert(value != NULL);

    // Reallocate
    void* new = realloc(str->data, str->size + strlen(value));
    if (new == NULL) {
        return NULL;
    } else {
        str->data = new;
    }

    // Append
    strcat(str->data, value);

    // Return success
    return str;
}
