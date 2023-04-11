#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE DECLARATIONS

const char *default_delimiters = " \t\f\r\0x20";

static const char *tensor_str_token_type_cstring(tensor_token_type_t type)
{
    switch (type)
    {
    case START_T:
        return "START_T";
    case TEXT_T:
        return "TEXT_T";
    case DELIMITER_T:
        return "DELIMITER_T";
    default:
        return NULL;
    }
}

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

// Create a string reference and append a token to the end of the list of tokens. Returns NILL
// if the token could not be appended
static tensor_str_token_t *tensor_str_token_append_ref(tensor_pool_t *pool, tensor_str_token_t *prev, tensor_token_type_t type, tensor_str_t *str, size_t left, size_t size, void *user_data)
{
    assert(pool != NULL);
    assert(str != NULL);

    // Create token reference
    tensor_str_t *ref = tensor_str_ref(pool, str, left, size);
    if (ref == NULL)
    {
        return NULL;
    }

    // Append token
    tensor_str_token_t *next = tensor_str_token_append(pool, prev, type, user_data);
    if (next == NULL)
    {
        return NULL;
    }

    // Set the string reference
    next->str = ref;

    // Return the new token
    return next;
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

    const size_t buf_size = 1024;
    char buf[buf_size];

    // Create a START_T token
    tensor_str_token_t *head = tensor_str_token_append(pool, NULL, START_T, user_data);
    if (head == NULL)
    {
        return NULL;
    }

    // Iterate through the string, looking for text tokens and delimiters
    tensor_str_token_t *tokens = head;
    size_t start = 0;
    size_t ptr = 0;
    for (; ptr < str->size; ptr++)
    {
        char c = str->data[ptr];
        if (strchr(delimiters, c) || c == '\0')
        {
            // Eject token before delimiter
            if (ptr && start != ptr)
            {
                tokens = tensor_str_token_append_ref(pool, tokens, TEXT_T, str, start, ptr - start, user_data);
                if (tokens == NULL)
                {
                    return NULL;
                }
            }

            // Eject delimiter
            if (keep_delimiters)
            {
                tokens = tensor_str_token_append_ref(pool, tokens, DELIMITER_T, str, ptr, 1, user_data);
                if (tokens == NULL)
                {
                    return NULL;
                }
            }

            // Adjust start to point to the next character after the delimiter
            start = ptr + 1;
        }
    }

    // Eject any remaining tokens
    if (start != ptr)
    {
        tokens = tensor_str_token_append_ref(pool, tokens, TEXT_T, str, start, ptr - start, user_data);
        if (tokens == NULL)
        {
            return NULL;
        }
    }

    // Return the list of tokens
    return head;
}

// Return the next token in the list, or NULL if there are no next tokens defined
inline tensor_str_token_t *tensor_str_token_next(tensor_str_token_t *token)
{
    assert(token != NULL);
    return token->next;
}

// Return a token's type
inline tensor_token_type_t tensor_str_token_type(tensor_str_token_t *token)
{
    assert(token != NULL);
    return token->token_type;
}

// Return a token's user data
inline void *tensor_str_token_user_data(tensor_str_token_t *token)
{
    assert(token != NULL);
    return token->user_data;
}

// Return a token's string
inline tensor_str_t *tensor_str_token_str(tensor_str_token_t *token)
{
    assert(token != NULL);
    return token->str;
}

// Describe a single token
tensor_str_t *tensor_str_token_describe(tensor_pool_t *pool, tensor_str_token_t *token)
{
    assert(pool != NULL);
    assert(token != NULL);

    // Create a string to describe the token
    tensor_str_t *str = tensor_str_create(pool, 0);
    if (str == NULL)
    {
        return NULL;
    }

    tensor_str_printf(str, "%s<", tensor_str_token_type_cstring(token->token_type));
    if (token->str && token->str->size)
    {
        tensor_str_printf(str, "'");
        tensor_str_concat(str, token->str);
        tensor_str_printf(str, "'");
    }
    tensor_str_printf(str, ">");

    // Return the string
    return str;
}
