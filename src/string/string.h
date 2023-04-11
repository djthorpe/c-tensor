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

    // Constant strings cannot be manipulated or free'd (they are tokens)
    bool constant;

    // Next string in the pool
    tensor_str_t *next;
};

// Reference some part of another string as a constant string, from a left-most
// character index and a length. Returns NULL if there was an error, for example
// if the index was out of bounds
tensor_str_t *tensor_str_ref(tensor_pool_t *pool, tensor_str_t *src, size_t left, size_t len);

#endif
