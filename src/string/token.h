#ifndef TENSOR_PRIVATE_TOKEN_H
#define TENSOR_PRIVATE_TOKEN_H

#include "tensor_private.h"

// String data structure
struct tensor_str_token_instance
{
    // Unique token id
    uint32_t id;

    // User data
    void *user_data;

    // Token type - text or delimiter
    tensor_token_type_t token_type;

    // Token reference
    tensor_str_t *str;

    // Next token in the list, or NULL if this is the last token
    tensor_str_token_t *next;
};


/*
 * Append a token to the end of the list of tokens.
 * 
 * Will create a new token and append it to the end of the list of tokens.
 * The token will still need to be initialized with any string data.
 * 
 * @param pool      pool to allocate token from
 * @param prev      previous token in the list, or NULL if this is the first token
 * @param type      token type
 * @param user_data user data to attach to the token
 * @return          token or NULL if the token could not be appended
 */
tensor_str_token_t *tensor_str_token_append(tensor_pool_t *pool, tensor_str_token_t *prev, tensor_token_type_t type, void *user_data);

#endif
