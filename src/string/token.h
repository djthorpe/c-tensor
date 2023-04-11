#ifndef TENSOR_PRIVATE_TOKEN_H
#define TENSOR_PRIVATE_TOKEN_H

#include "tensor_private.h"

// String data structure
struct tensor_str_token_instance
{
    // User data
    void *user_data;

    // Token type - text or delimiter
    tensor_token_type_t token_type;

    // Next token in the list, or NULL if this is the last token
    tensor_str_token_t *next;
};

#endif
