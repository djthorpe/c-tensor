
#ifndef TENSOR_STRING_H
#define TENSOR_STRING_H

///////////////////////////////////////////////////////////////////////////////

// Token types
typedef enum
{
    START_T,     // Start of string
    TEXT_T,      // Text token
    DELIMITER_T, // Deimiter token or CSV field separator
    EOL_T,       // Newline or CSV end of record
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

/**
 * Create a list of tokens from a string
 * 
 * Create a list of tokens from a string, separated by the given set of
 * delimiters. The first token is always of type START_T. Use 
 * tensor_str_token_next() to iterate through the list of tokens.
 *
 * @param pool        The memory pool, which should contain enough memory 
 *                    to store the tokens
 * @param str         The string to tokenize
 * @param delimiters  A string containing the delimiters to use to separate the
 *                    string into tokens. The string should be null terminated.
 * @param keep_delimiters  If true, then the delimiters will be included in the
 *                    list of tokens. If false, then the delimiters will be
 *                    skipped.
 * @param user_data   User data to pass to the tokenizer, which can be retrieved
 *                    using the tensor_str_token_user_data() method.
 * @return            The first token in the list, or NULL if there are no tokens.
 *                    The first token is always of type START_T. Returns NULL if
 *                    there was an error, for example if the string was empty
 *                    or if the pool was too small to store the tokens.
 */
tensor_str_token_t *tensor_str_tokenize(tensor_pool_t *pool, tensor_str_t *str, char *delimiters, bool keep_delimiters, void *user_data);

/**
 * Return the next token in the list, or NULL if there are no next tokens defined
 *
 * @param token  The token
 * @return       The next token in the list, or NULL if there are no further tokens.
 */
tensor_str_token_t *tensor_str_token_next(tensor_str_token_t *token);

/**
 * Return a token's type
 *
 * @param token  The token
 * @return       The token's type. See tensor_token_type_t for a list of possible types
 */
tensor_token_type_t tensor_str_token_type(tensor_str_token_t *token);

/**
 * Return a token's user data value
 *
 * @param token  The token
 * @return       The user data value which was passed to tensor_str_csv_parse() or
 *               tensor_str_tokenize() method
 */
void *tensor_str_token_user_data(tensor_str_token_t *token);

/**
 * Return a token's string value
 *
 * @param token  The token
 * @return       The string value of the token
 */
tensor_str_t *tensor_str_token_str(tensor_str_token_t *token);

/**
 * Describe a single token
 *
 * Return a textual description of a token, including the token type, the token string
 *
 * @param pool   The memory pool, which should contain enough memory to store the string
 * @param token  The token to describe
 * @return       A string describing the token, or NULL if an error occurred (usually an
 *               out of memory error)
 */
tensor_str_t *tensor_str_token_describe(tensor_pool_t *pool, tensor_str_token_t *token);


/**
 * Return true if token is a delimiter
 *
 *
 * @param token      The token to describe
 * @param delimiter  The delimiter to check
 * @return           Returns true if a token is a delimiter
 */
bool tensor_str_token_is_delimiter(tensor_str_token_t *token, const char delimiter);

///////////////////////////////////////////////////////////////////////////////
// CSV

/**
 * Create a CSV parser
 *
 * You should call this method before repeatedly calling tensor_str_csv_parse() in order
 * to parse a stream of CSV data.
 *
 * @param pool   The memory pool, which should contain enough memory to store the expected
 *               number of tokens
 * @param sep    The CSV field separator, usually ',', ';' or '\t'. If you pass 0 then
 *               the default separator ',' will be used.
 * @return       A CSV parser object, or NULL if an error occurred (usually an out of
 *               memory error)
 */
tensor_str_csv_t *tensor_str_csv_create(tensor_pool_t *pool, const char sep);

/**
 * Consume a string of CSV data and return the fields as a list of tokens.
 *
 * You can call this method repeatedly to append more data. 
 *
 * @param csv    The CSV parser object which was constructed using tensor_str_csv_create()
 * @return       A list of tokens which have been parsed, or NULL if an error occurred
 *               (usually an out of memory error)
 */
tensor_str_token_t *tensor_str_csv_parse(tensor_str_csv_t *csv, tensor_str_t *str, void *user_data);

#endif
