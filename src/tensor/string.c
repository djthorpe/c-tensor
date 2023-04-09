#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <tensor/tensor.h>
#include "private.h"

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
