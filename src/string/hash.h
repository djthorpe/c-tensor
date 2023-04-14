#ifndef TENSOR_PRIVATE_STRING_HASH_H
#define TENSOR_PRIVATE_STRING_HASH_H

#include "tensor_private.h"

/* 
 * Hash function for strings returns a uint64_t hash value for a string.
 *
 * @param str   string to hash
 * @return      hash value
 */
uint64_t tensor_str_hash_uint64(tensor_str_t *str);

#endif
