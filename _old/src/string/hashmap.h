#ifndef TENSOR_PRIVATE_HASHMAP_H
#define TENSOR_PRIVATE_HASHMAP_H

#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// STRING HASHMAP

/**
 * Create a new hashmap with up to size elements
 *
 * @param pool               Pool to allocate hashmap from
 * @param size               Maximum size of the hashmap in number of elements
 * @return                   Hashmap or NULL if the hashmap could not be created
 */
tensor_str_hashmap_t *tensor_str_hashmap_create(tensor_pool_t *pool, size_t size);

/**
 * Return a value from the hashmap
 *
 * @param hashmap            The hashmap to retrieve the value from
 * @param key                The key to retrieve the value for. The key cannot be NULL.
 * @return                   The value or NULL if not found
 */
void *tensor_str_hashmap_get(tensor_str_hashmap_t *hashmap, tensor_str_t *key);

/**
 * Put a value in the hashmap
 *
 * If the key already exists, the value is replaced.
 *
 * @param hashmap            The hashmap to write to
 * @param key                The key to write the value for. The key cannot be NULL.
 * @param value              The value to write. The value can be NULL.
 * @return                   Returns true if successful.
 */
bool tensor_str_hashmap_put(tensor_str_hashmap_t *hashmap, tensor_str_t *key, void *value);

/**
 * Return all keys in the hashmap as a list of tokens
 *
 * @param hashmap            The hashmap to write to
 * @return                   Returns the list of keys or NULL if the hashmap is empty,
 *                           or if the token list could not be created.
 */
tensor_str_token_t *tensor_str_hashmap_keys(tensor_str_hashmap_t *hashmap);

#endif
