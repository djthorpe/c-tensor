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
 * Append a token to the end of the list of tokens, or create a new token list.
 *
 * A new token list is created if the prev field is set to NULL. This doesn't append
 * any string data and that needs to be added for certain tokens by setting the token->str
 * field.
 * 
 * @param pool              The memory pool
 * @param prev              The token to attach this one to, or NULL if this is the first token
 *                          in the token list
 * @param type              The token type
 * @param user_data         User data to attach to the token
 * @return                  The new token, or NULL if the token could not be appended
 */
tensor_str_token_t *tensor_str_token_append(tensor_pool_t *pool, tensor_str_token_t *prev, tensor_token_type_t type, void *user_data);

#endif
