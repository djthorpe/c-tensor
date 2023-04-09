#ifndef TENSOR_STRING_H
#define TENSOR_STRING_H

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

#endif
