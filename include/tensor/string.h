
#ifndef TENSOR_STRING_H
#define TENSOR_STRING_H

#include <stdint.h>
#include <stdbool.h>
#include "tensor.h"

///////////////////////////////////////////////////////////////////////////////

/**
 * Token types
 *
 * The token types are used to describe the type of token that is returned by
 * the tokenizer.
 *
 */
typedef enum
{
    START_T,     // Start of string
    END_T,       // End of line
    TEXT_T,      // Text token
    SPACE_T,     // Whitespace token
    DELIMITER_T, // Deimiter token or CSV field separator
    IGNORE_T,    // Ignore token
} tensor_token_type_t;

// Opaque string
typedef struct tensor_str_instance tensor_str_t;

// Opaque tokens
typedef struct tensor_str_token_instance tensor_str_token_t;

// Opaque csv
typedef struct tensor_str_csv_instance tensor_str_csv_t;

///////////////////////////////////////////////////////////////////////////////
// STRINGS

/**
 * Create a string from a cstring
 *
 * Creates a string from a Null-terminated C string, or an empty string if
 * the argument is NULL. The string is copied, so it's safe to free any
 * memory associated with the passed argument.
 *
 * @param pool        The memory pool, which should contain enough memory
 *                    to store the tokens
 * @param str         The Null-terminated C string. If str is NULL then create
 *                    an empty string.
 * @return            The string value or NULL if there was an error, most
 *                    likely an out of memory error
 */
tensor_str_t *tensor_str_create(tensor_pool_t *pool, char *str);

/**
 * Duplicate a string
 *
 * Creates a copy of an existing string
 *
 * @param pool        The memory pool, which should contain enough memory
 *                    to store the tokens
 * @param str         The string to duplicate.
 * @return            The duplicated string value or NULL if there was an error,
 *                    most likely an out of memory error
 */
tensor_str_t *tensor_str_dup(tensor_pool_t *pool, tensor_str_t *str);

/**
 * Check if two strings are equal
 *
 * Returns true if the two strings are exactly equal.
 *
 * @param a           The first string argument.
 * @param b           The second string argument.
 * @return            Returns true if the two strings are exactly equal,
 *                    or are both empty.
 */
bool tensor_str_equals(tensor_str_t *a, tensor_str_t *b);

/**
 * Append a printf-formatted string with arguments to a string
 *
 *
 *
 * @param dst         The first string argument.
 * @param fmt         The format of the string to append, with the
 *                    same semantics as printf. Use further argumentd
 *                    to specify the values to insert into the formatted
 *                    string.
 * @return            Returns true on success, or false if there was an
 *                    error, maybe due to a memory allocation error.
 */
bool tensor_str_printf(tensor_str_t *dst, const char *fmt, ...);

/**
 * Concatenate a string to another string
 *
 * @param dst         The destination string, which will be appended to
 * @param src         The source string
 * @return            Returns true on success, or false if there was an
 *                    error, maybe due to a memory allocation error.
 */
bool tensor_str_concat(tensor_str_t *dst, tensor_str_t *src);

/**
 * Return the length of a string
 *
 * @param str         The string argument
 * @return            Returns the length of the string, in characters.
 */
size_t tensor_str_len(tensor_str_t *str);

/**
 * Return the hash value of a string
 *
 * The hash value can be used to compare strings quickly.
 *
 * @param str         The string argument
 * @return            Returns the hash value of the string. Returns zero if
 *                    the string is empty.
 */
uint64_t tensor_str_hash(tensor_str_t *str);

/**
 * Empty a string to set it to zero length
 *
 * @param str         The string argument
 */
void tensor_str_zero(tensor_str_t *str);

/**
 * Create a null-terminated string
 *
 * @param dst         The destination Null-terminated C string
 * @param size        The maximum number of bytes to copy to the destination
 * @param src         The source string
 * @return            Returns the destination string, or NULL if there was an
 *                   error, most likely an out of memory error
 */
const char *tensor_cstring(char *dst, size_t size, tensor_str_t *src);

/**
 * Return true if the string has a specific prefix
 *
 * @param src         The source string
 * @param prefix      The prefix value
 * @return            Returns true if the string has the prefix
 */
bool tensor_str_has_prefix(tensor_str_t *src, const char *prefix);

/**
 * Return true if the string has a specific suffix
 *
 * @param src         The source string
 * @param suffix      The suffix value
 * @return            Returns true if the string has the suffix
 */
bool tensor_str_has_suffix(tensor_str_t *src, const char *suffix);

/**
 * Describe a tensor
 *
 * Return information about the tensor, including the tensor id, data type,
 * shape and whether it's a value node or an operation node.
 *
 * @param pool        The memory pool, which should contain enough memory
 *                    to store the description sttrin
 * @param tensor      The tensor
 * @return            A string of the tensor description, or NULL if an error
 *                    occurred (usually an out of memory error)
 */
tensor_str_t *tensor_str_describe(tensor_pool_t *pool, tensor_t *tensor);

/**
 * Return a tensor value as a string
 *
 * Return the tensor in a string representation.
 *
 * @param pool        The memory pool, which should contain enough memory
 *                    to store the description sttrin
 * @param tensor      The tensor
 * @return            A string of the tensor, or NULL if an error
 *                    occurred (usually an out of memory error)
 */
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
 * Describe a token
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


/*
 * Return true if the whole token consists of whitespace characters. Returns false
 * if the token is empty or contains non-whitespace characters
 * 
 * @param token       The token to describe
 * @return            Returns true if the token is whitespace, otherwise returns false
 */
bool tensor_str_token_is_whitespace(tensor_str_token_t *token);



///////////////////////////////////////////////////////////////////////////////
// CSV

/**
 * Create a CSV parser
 *
 * You should call this method before repeatedly calling tensor_str_csv_parse() in order
 * to parse a stream of CSV data.
 *
 * @param pool   The memory pool for temporary storage
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
 * @param pool   The memory pool, which should contain enough memory to store the expected
 *               number of tokens
 * @param csv    The CSV parser object which was constructed using tensor_str_csv_create()
 * @return       A list of tokens which have been parsed, or NULL if an error occurred
 *               (usually an out of memory error)
 */
tensor_str_token_t *tensor_str_csv_parse(tensor_pool_t *pool, tensor_str_csv_t *csv, tensor_str_t *str, void *user_data);

#endif
