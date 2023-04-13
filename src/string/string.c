#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include <tensor/tensor.h>
#include <tensor/string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Reference some part of another string as a constant string, from a left-most
// character index and a length. Returns NULL if there was an error, for example
// if the index was out of bounds
tensor_str_t *tensor_str_ref(tensor_pool_t *pool, tensor_str_t *src, size_t left, size_t len)
{
    assert(pool != NULL);
    assert(src != NULL);

    // Check left when left or len are greater than zero
    if (src->size == 0 && (left > 0 || len > 0))
    {
        return NULL;
    }

    // Allocate an empty string (one that has no data)
    tensor_str_t *dest = tensor_pool_alloc_str(pool, 0);
    if (dest == NULL)
    {
        return NULL;
    }

    // Set string as a constant string
    dest->constant = true;

    // Return the string if the length is zero
    if (len == 0)
    {
        return dest;
    }

    // TODO: Check length

    // Set the string data
    dest->data = src->data + left;
    dest->size = len;

    // TODO: What do we do about null termination and the use of cstring methods?

    // Return the string
    return dest;
}

// Create a string from a cstring. If str is NULL then create an empty
// string
tensor_str_t *tensor_str_create(tensor_pool_t *pool, char *cstring)
{
    assert(pool != NULL);

    size_t len = 0;
    if (cstring != NULL)
    {
        len = (size_t)strlen(cstring);
    }

    // Allocate the string
    tensor_str_t *str = tensor_pool_alloc_str(pool, cstring == NULL ? 0 : len);
    if (str == NULL)
    {
        return NULL;
    }

    // If empty string, return
    if (len == 0)
    {
        return str;
    }

    // Copy the string
    if (cstring != NULL)
    {
        assert(str->size == len);
        assert(str->data != NULL);
        memcpy(str->data, cstring, len);
    }

    // Return the string
    return str;
}

// Duplicate a string and return it. Returns NULL on error
tensor_str_t *tensor_str_dup(tensor_pool_t *pool, tensor_str_t *a)
{
    assert(pool != NULL);
    assert(a != NULL);

    // Allocate the string, with an extra terminating null byte
    tensor_str_t *str = tensor_pool_alloc_str(pool, a->size);
    if (str == NULL)
    {
        return NULL;
    }

    // Copy the string
    if (a->size)
    {
        assert(str->size == a->size);
        assert(str->data);
        assert(a->data);
        memcpy(str->data, a->data, a->size);
    }

    // Return the string
    return str;
}

// Return the length of a string
inline size_t tensor_str_len(tensor_str_t *str)
{
    assert(str != NULL);
    if (str->size == 0)
    {
        assert(str->data == NULL);
        return 0;
    }
    else
    {
        assert(str->data != NULL);
        return str->size;
    }
}

// Empty a string (set length to zero)
inline void tensor_str_zero(tensor_str_t *str)
{
    assert(str != NULL);
    str->size = 0;
    free(str->data);
    str->data = NULL;
}

// Return the string as a cstring, up to size bytes, including null terminator
const char *tensor_cstring(char *dst, size_t size, tensor_str_t *src)
{
    assert(dst != NULL);
    assert(src != NULL);
    assert(size > 0);

    // Check on empty string case
    if (src->size == 0 || size == 1)
    {
        *dst = '\0';
        return dst;
    }

    // Adjust size to be minimum of size
    if (size > src->size)
    {
        size = src->size;
    }
    else
    {
        size--;
    }

    // Copy the data, add NULL terminator
    assert(src->data != NULL);
    memcpy(dst, src->data, size);
    dst[size] = '\0';

    // Return the string
    return dst;
}

// Return true if two strings are equal
inline bool tensor_str_equals(tensor_str_t *a, tensor_str_t *b)
{
    assert(a != NULL);
    assert(b != NULL);

    // If the sizes are different then the strings are different
    if (a->size != b->size)
    {
        return false;
    }

    // If the sizes are zero then the strings are equal
    if (a->size == 0)
    {
        assert(a->data == NULL);
        assert(b->data == NULL);
        return true;
    }

    // Compare the strings
    assert(a->data != NULL);
    assert(b->data != NULL);
    return memcmp(a->data, b->data, a->size) == 0;
}

// Concatenate a string to a string, return true on success
bool tensor_str_concat(tensor_str_t *dst, tensor_str_t *src)
{
    assert(dst != NULL);
    assert(src != NULL);

    // If source string is empty, it's a no-op
    if (src->size == 0)
    {
        return true;
    }

    // If destination string is constant, return false
    if (dst->constant)
    {
        return false;
    }

    // If the destination string is empty, then copy
    if (dst->size == 0)
    {
        assert(dst->data == NULL);
        dst->data = malloc(src->size);
        if (dst->data == NULL)
        {
            return false;
        }
        memcpy(dst->data, src->data, src->size);
        dst->size = src->size;
        return true;
    }

    // If the destination string is not empty, then reallocate
    assert(dst->data != NULL);
    void *data = realloc(dst->data, dst->size + src->size);
    if (data == NULL)
    {
        return false;
    }
    else
    {
        dst->data = data;
    }
    memcpy(dst->data + dst->size, src->data, src->size);
    dst->size += src->size;
    return true;
}

// Concatenate a printf statement to a string, return true on success
bool tensor_str_printf(tensor_str_t *dst, const char *fmt, ...)
{
    assert(dst != NULL);
    assert(fmt != NULL);

    // Get the additional length required for the string, not including
    // the terminating null byte
    va_list args;
    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    // An error occurred
    if ((int)len < 0)
    {
        return false;
    }

    // No length - return true
    if (len == 0)
    {
        return true;
    }

    // If destination string is constant, return false
    if (dst->constant)
    {
        return false;
    }

    // Reallocate - add an extra byte for the null terminator that vsnprintf will add
    size_t newsize = dst->size + len;
    void *data = realloc(dst->data, newsize + 1);
    if (data == NULL)
    {
        return false;
    }
    else
    {
        dst->data = data;
    }

    // Append the string to the end of the buffer
    va_start(args, fmt);
    vsnprintf(dst->data + dst->size, len + 1, fmt, args);
    va_end(args);

    // Update the size
    dst->size = newsize;

    // Return success
    return true;
}

/**
 * Return true if the string has a specific prefix
 */
bool tensor_str_has_prefix(tensor_str_t *src, const char *prefix)
{
    assert(src);
    assert(prefix);

    // Check size first
    size_t len = strlen(prefix);
    if (src->size < len)
    {
        return false;
    }

    // Compare the strings
    assert(src->data);
    return memcmp(src->data, prefix, len) == 0;
}

/**
 * Return true if the string has a specific suffix
 */
bool tensor_str_has_suffix(tensor_str_t *src, const char *suffix)
{
    assert(src);
    assert(suffix);

    // Check size first
    size_t len = strlen(suffix);
    if (src->size < len)
    {
        return false;
    }

    // Compare the strings
    assert(src->data);
    return memcmp(src->data + src->size - len, suffix, len) == 0;
}
