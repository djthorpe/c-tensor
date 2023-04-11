#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE DECLARATIONS

const char *default_delimiters = " \t\f\r\0x20";

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

// Append a token to the end of the list of tokens. Returns NULL if the token
// could not be appended
static tensor_str_token_t *tensor_str_token_append(tensor_pool_t *pool, tensor_str_token_t *prev, tensor_token_type_t type, void *user_data)
{
    assert(pool != NULL);

    // Allocate the token
    uint32_t id;
    tensor_str_token_t *token = tensor_pool_alloc(pool, sizeof(tensor_str_token_t), &id);
    if (token == NULL)
    {
        return NULL;
    }

    // Initialize the token
    token->id = id;
    token->token_type = type;
    token->user_data = user_data;
    token->next = NULL;

    // Chain
    if (prev != NULL)
    {
        assert(prev->next == NULL);
        prev->next = token;
    }

    return token;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Create a list of tokens from a string, separated by the given set of delimiters and
// optionally including the delimiters in the list of tokens. Returns NULL on
// memory allocation error or zero-valued string. If delimiters is NULL then
// use the default set of delimiters, which is the set if whitespace characters
// and NULL
tensor_str_token_t *tensor_str_tokenize(tensor_pool_t *pool, tensor_str_t *str, char *delimiters, bool keep_delimiters, void *user_data)
{
    assert(pool != NULL);
    assert(str != NULL);

    // Empty string returns NULL
    if (str->size == 0)
    {
        return NULL;
    }
    assert(str->data);

    // Set delimiters to default if not specified
    if (delimiters == NULL)
    {
        delimiters = (char *)default_delimiters;
    }

    // Iterate through the string, looking for delimiters
    void *start = str->data;
    tensor_str_token_t* tokens = NULL;
    for (void *ptr = str->data; ptr < (void *)(str->data + str->size); ptr++)
    {
        // Check if this is a delimiter or a null terminator
        if (strchr(delimiters, *(char *)ptr) || *(char *)ptr == '\0')
        {
            if (ptr > start)
            {
                // TODO: Eject the previous token
                printf("Eject %lu text chars\n", ptr - start);
            }
            if (keep_delimiters)
            {
                tokens = tensor_str_token_append(pool, tokens, DELIMITER_T, user_data);
            }
            // Adjust start to point to the next character after the delimiter
            start = ptr + 1;
        }
        else
        {
            printf("Not delimiter %c\n", *(char *)ptr);
        }
    }
    // TODO: Eject any remaining tokens

    return tokens;
}
