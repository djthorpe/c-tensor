#ifndef TENSOR_PRIVATE_STRING_ARGS_H
#define TENSOR_PRIVATE_STRING_ARGS_H

#include "tensor_private.h"

struct tensor_str_args_instance
{
    // The command string
    tensor_str_t *command;

    // The list of arguments
    struct tensor_str_token_instance *args;

    // The memory pool
    tensor_pool_t *pool;

    // The hashmap of flags
    tensor_hashmap_t *flags;

    // Whether the arguments have been parsed
    bool parsed;
};

struct tensor_str_args_flag_instance
{
    // Flag is a boolean (switch) flag
    bool boolean;

    // Value
    tensor_str_t *value;

    // Description
    tensor_str_t *description;
};

#endif // TENSOR_PRIVATE_STRING_ARGS_H
