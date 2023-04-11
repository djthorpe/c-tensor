#ifndef TENSOR_PRIVATE_STRING_H
#define TENSOR_PRIVATE_STRING_H

#include "tensor_private.h"

// String data structure
struct tensor_str_instance
{
    // Character data is allocted separately from the rest of the pool data
    char *data;

    // Size of string, including null terminator
    size_t size;

    // Next string in the pool
    tensor_str_t *next;
};

// Concatenate a string representation of a value to a string. Returns the string
// again or NULL if the allocation failed.
tensor_str_t* tensor_strcat_dtype(tensor_str_t *str, tensor_dtype_t dtype, void* value);

// Concatenate a cstring value to a string. Returns the string
// again or NULL if the allocation failed.
tensor_str_t* tensor_strcat_cstr(tensor_str_t *str, const char* value);

// Concatenate a printf value to a string. Returns the string
// again or NULL if the allocation failed.
tensor_str_t* tensor_strcat_printf(tensor_str_t *str, const char* fmt, ...);

#endif
