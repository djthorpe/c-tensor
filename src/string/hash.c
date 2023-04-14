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

/*
 * Compute a uint64_t hash of a string
 */
uint64_t tensor_str_hash_uint64(tensor_str_t *str)
{
    assert(str != NULL);
    if (str->size == 0)
    {
        return 0;
    }
    const uint64_t p = 31;
    const uint64_t mod = 1e9 + 9;
    uint64_t hash = 0;
    uint64_t pow = 1;
    for(size_t i = 0; i < str->size; i++)
    {
        hash = (hash + (str->data[i] - 'a' + 1) * pow) % mod;
        pow = (pow * p) % mod;
    }
    return hash;
}


/**
 * Return the hash value of a string
 */
inline uint64_t tensor_str_hash(tensor_str_t *str) {
    assert(str != NULL);
    if (str->hash == 0)
    {
        str->hash = tensor_str_hash_uint64(str);
    }
    return str->hash;
}

