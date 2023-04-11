

#ifndef TENSOR_STRING_H
#define TENSOR_STRING_H

///////////////////////////////////////////////////////////////////////////////

// Token types
typedef enum
{
    START_T,     // Start of string
    TEXT_T,      // Text token
    DELIMITER_T, // Deimiter token
} tensor_token_type_t;

// Opaque string
typedef struct tensor_str_instance tensor_str_t;

// Opaque tokens
typedef struct tensor_str_token_instance tensor_str_token_t;

// Opaque csv
typedef struct tensor_str_csv_instance tensor_str_csv_t;


///////////////////////////////////////////////////////////////////////////////
// STRINGS

// Create a string from a cstring. If str is NULL then create an empty
// string
tensor_str_t *tensor_str_create(tensor_pool_t *pool, char *str);

// Duplicate a string and return it
tensor_str_t *tensor_str_dup(tensor_pool_t *pool, tensor_str_t *str);

// Return true if two strings are equal
bool tensor_str_equals(tensor_str_t *a, tensor_str_t *b);

// Concatenate a printf statement to a string, return true on success
bool tensor_str_printf(tensor_str_t *dst, const char *fmt, ...);

// Concatenate a string to a string, return true on success
bool tensor_str_concat(tensor_str_t *dst, tensor_str_t *src);

// Return the length of a string
size_t tensor_str_len(tensor_str_t *str);

// Empty a string (set length to zero)
void tensor_str_zero(tensor_str_t *str);

// Return the string as a cstring, up to size bytes, including null terminator
const char *tensor_cstring(char *dst, size_t size, tensor_str_t *src);

// Describe the tensor (id, type, op, dimensions, etc.)
tensor_str_t *tensor_str_describe(tensor_pool_t *pool, tensor_t *tensor);

// Create a string representation of a tensor
tensor_str_t *tensor_str_print(tensor_pool_t *pool, tensor_t *tensor);

///////////////////////////////////////////////////////////////////////////////
// TOKENS

// Create a list of tokens from a string, separated by the given set of delimiters and
// optionally including the delimiters in the list of tokens. Returns NULL on
// memory allocation error or zero-valued string
tensor_str_token_t *tensor_str_tokenize(tensor_pool_t *pool, tensor_str_t *str, char *delimiters, bool keep_delimiters, void *user_data);

// Return the next token in the list, or NULL if there are no next tokens defined
tensor_str_token_t *tensor_str_token_next(tensor_str_token_t *token);

// Return a token's type
tensor_token_type_t tensor_str_token_type(tensor_str_token_t *token);

// Return a token's user data
void *tensor_str_token_user_data(tensor_str_token_t *token);

// Return a token's string
tensor_str_t *tensor_str_token_str(tensor_str_token_t *token);

// Describe a single token
tensor_str_t *tensor_str_token_describe(tensor_pool_t *pool, tensor_str_token_t *token);

///////////////////////////////////////////////////////////////////////////////
// CSV

// Create a CSV parser, with the given separator (usually ',', ';' or '\t')
tensor_str_csv_t *tensor_str_csv_create(tensor_pool_t *pool, const char sep);

// Consume a string of CSV data and return the fields as a list of tokens.
// Returns NULL on error.
tensor_str_token_t *tensor_str_csv_parseline(tensor_str_csv_t *csv, tensor_str_t *str, void *user_data);

#endif
