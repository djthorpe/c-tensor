#include <assert.h>
#include <string.h>
#include <ctype.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE DECLARATIONS

static const char *default_delimiters = " \t\f\r\n\0x20";

static const char *tensor_str_token_type_cstring(tensor_token_type_t type)
{
    switch (type)
    {
    case START_T:
        return "START_T";
    case END_T:
        return "END_T";
    case TEXT_T:
        return "TEXT_T";
    case SPACE_T:
        return "SPACE_T";
    case QUOTE_T:
        return "QUOTE_T";
    case DELIMITER_T:
        return "DELIMITER_T";
    case IGNORE_T:
        return "IGNORE_T";
    default:
        return NULL;
    }
}

static bool is_delimiter(const char c, const char *delimiters)
{
    assert(delimiters);
    return strchr(delimiters, c) != NULL || c == '\0';
}

static bool is_whitespace(const char c)
{
    return isspace(c);
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

// Append a token to the end of the list of tokens. Returns NULL if the token
// could not be appended
tensor_str_token_t *tensor_str_token_append(tensor_pool_t *pool, tensor_str_token_t *prev, tensor_token_type_t type, void *user_data)
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

// TODO: REMOVE
#define buf_size 1024
char buf[buf_size];

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
    bool in_whitespace = false;
    for (; ptr < str->size; ptr++)
    {
        char c = str->data[ptr];
        bool whitespace = is_whitespace(c);
        if (is_delimiter(c, delimiters))
        {
            // Eject token before delimiter
            if (ptr && start != ptr)
            {
                tokens = tensor_str_token_append_ref(pool, tokens, in_whitespace ? SPACE_T : TEXT_T, str, start, ptr - start, user_data);
                if (tokens == NULL)
                {
                    return NULL;
                }
                else
                {
                    in_whitespace = false;
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
        else if (whitespace != in_whitespace)
        {
            if (ptr - start > 0)
            {
                // Eject token
                tokens = tensor_str_token_append_ref(pool, tokens, in_whitespace ? SPACE_T : TEXT_T, str, start, ptr - start, user_data);
                if (tokens == NULL)
                {
                    return NULL;
                }
            }

            // Adjust start to point to the next character after the delimiter
            start = ptr;
        }
        in_whitespace = whitespace;
    }

    // Eject any remaining tokens as text
    if (start != ptr)
    {
        tokens = tensor_str_token_append_ref(pool, tokens, in_whitespace ? SPACE_T : TEXT_T, str, start, ptr - start, user_data);
        if (tokens == NULL)
        {
            return NULL;
        }
    }

    // Return the list of tokens
    return head;
}

// Return the next token in the list, or NULL if there are no next tokens defined
tensor_str_token_t *tensor_str_token_next(tensor_str_token_t *token)
{
    assert(token != NULL);

    // Skip over any IGNORE_T tokens
    while (token->next && token->next->token_type == IGNORE_T)
    {
        token = token->next;
    }
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

/*
 * Return true if the token is one character and matches the given delimiter
 */
inline bool tensor_str_token_is_delimiter(tensor_str_token_t *token, const char delimiter)
{
    assert(token != NULL);
    return token->token_type == DELIMITER_T && token->str->size == 1 && token->str->data[0] == delimiter;
}

/*
 * Return true if the whole token consists of whitespace characters. Returns false
 * if the token is empty or contains non-whitespace characters
 */
inline bool tensor_str_token_is_whitespace(tensor_str_token_t *token)
{
    assert(token);
    size_t len = tensor_str_len(token->str);
    if (len == 0)
    {
        return false;
    }
    assert(token->str->data);
    for (size_t i = 0; i < tensor_str_len(token->str); i++)
    {
        if (!isspace(token->str->data[i]))
        {
            return false;
        }
    }
    return true;
}
