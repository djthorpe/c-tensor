#include <string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static inline size_t tensor_hashmap_key(tensor_hashmap_t *hashmap, void *ptr)
{
    size_t key = (size_t)ptr;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key;
}

static inline size_t tensor_hashmap_cstring_key(tensor_hashmap_t *hashmap, const char *ptr, size_t *lenp)
{
    size_t hash = 0;
    size_t len = 0;
    while (*ptr)
    {
        len++;
        hash = (hash * 31) + (*ptr++);
    }
    if (lenp)
    {
        *lenp = len;
    }
    return hash;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

/*
 * Create a new hashmap with up to size elements
 */
tensor_hashmap_t *tensor_hashmap_create(tensor_pool_t *pool, size_t size)
{
    assert(pool);
    assert(size);

    tensor_hashmap_t *hashmap = tensor_pool_alloc(pool, sizeof(tensor_hashmap_t), NULL);
    if (hashmap == NULL)
    {
        return NULL;
    }

    // Initialize the nodes in the hashmap
    hashmap->size = size;
    hashmap->nodes = tensor_pool_alloc(pool, sizeof(struct tensor_hashmap_node) * size, NULL);
    if (hashmap->nodes == NULL)
    {
        return NULL;
    }

    // Empty the nodes
    memset(hashmap->nodes, 0, sizeof(struct tensor_hashmap_node) * size);

    // Return success
    return hashmap;
}

/*
 * Return a value from the hashmap, or NULL if not found
 */
void *tensor_hashmap_get(tensor_hashmap_t *hashmap, void *key)
{
    assert(hashmap);
    assert(key);

    size_t hash = tensor_hashmap_key(hashmap, key);
    size_t index = hash % hashmap->size;
    size_t start = index;
    while (hashmap->nodes[index].key != NULL)
    {
        if (hashmap->nodes[index].key == key)
        {
            return hashmap->nodes[index].value;
        }

        // Increment the index and check for wrap-around
        index = (index + 1) % hashmap->size;
        if (index == start)
        {
            return NULL;
        }
    }

    // Key not found
    return NULL;
}

/*
 * Return a value from the hashmap, or NULL if not found
 */
void *tensor_hashmap_get_cstring(tensor_hashmap_t *hashmap, const char *key)
{
    assert(hashmap);
    assert(key);

    size_t len;
    size_t hash = tensor_hashmap_cstring_key(hashmap, key, &len);
    size_t index = hash % hashmap->size;
    size_t start = index;
    while (hashmap->nodes[index].key != NULL)
    {
        if (hashmap->nodes[index].len == len)
        {
            if (strcmp(hashmap->nodes[index].key, key) == 0)
            {
                return hashmap->nodes[index].value;
            }
        }
        
        // Increment the index and check for wrap-around
        index = (index + 1) % hashmap->size;
        if (index == start)
        {
            return NULL;
        }
    }

    // Key not found
    return NULL;
}

/*
 * Put a value into the hashmap, replacing any existing value. Returns false
 * if the hashmap is full
 */
bool tensor_hashmap_put(tensor_hashmap_t *hashmap, void *key, void *value)
{
    assert(hashmap);
    assert(key);

    // Find a spot for the key
    size_t hash = tensor_hashmap_key(hashmap, key);
    size_t index = hash % hashmap->size;
    size_t start = index;
    while (hashmap->nodes[index].key != NULL)
    {
        if (hashmap->nodes[index].key == key)
        {
            // Replace current value
            hashmap->nodes[index].value = value;
            return key;
        }

        // Increment the index and check for wrap-around
        index = (index + 1) % hashmap->size;
        if (index == start)
        {
            return false;
        }
    }

    // Insert the key
    hashmap->nodes[index].key = key;
    hashmap->nodes[index].value = value;

    // Return success
    return true;
}

/**
 * Put a cstring value in the hashmap, replacing any existing value. Returns false
 * if the hashmap is full or a memory allocation error occurred. The key is
 * copied into the hashmap.
 */
bool tensor_hashmap_put_cstring(tensor_hashmap_t *hashmap, tensor_pool_t *pool, const char *key, void *value)
{
    assert(hashmap);
    assert(pool);
    assert(key);

    // Compute the key and the length of the key
    size_t len;
    size_t hash = tensor_hashmap_cstring_key(hashmap, key, &len);
    size_t index = hash % hashmap->size;
    size_t start = index;
    while (hashmap->nodes[index].key != NULL)
    {
        if (hashmap->nodes[index].len == len)
        {
            if (strcmp(hashmap->nodes[index].key, key) == 0)
            {
                // Replace current value
                hashmap->nodes[index].value = value;
                return key;
            }
        }

        // Increment the index and check for wrap-around
        index = (index + 1) % hashmap->size;
        if (index == start)
        {
            return false;
        }
    }

    // The key was not found, so insert it ny making a copy of the key
    hashmap->nodes[index].key = tensor_pool_alloc(pool, len + 1, NULL);
    if (hashmap->nodes[index].key == NULL)
    {
        return false;
    }
    else
    {
        memcpy(hashmap->nodes[index].key, key, len + 1);
    }
    hashmap->nodes[index].len = len;
    hashmap->nodes[index].value = value;

    // Return success
    return true;
}
