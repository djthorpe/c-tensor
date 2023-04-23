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
    struct tensor_hashmap *flags;
};

struct tensor_str_args_flag_instance
{
    // Name
    tensor_str_t *name;

    // Value
    tensor_str_t *value;

    // Description
    tensor_str_t *description;
};

#endif // TENSOR_PRIVATE_STRING_ARGS_H
