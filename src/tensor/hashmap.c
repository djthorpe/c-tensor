#include <assert.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static inline size_t tensor_hashmap_key(struct tensor_hashmap* hashmap, void* ptr)
{
    size_t key = (size_t)ptr;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Create a new hashmap with up to size elements
struct tensor_hashmap *tensor_hashmap_create(tensor_pool_t *pool, size_t size)
{
    assert(pool != NULL);
    assert(size > 0);

    struct tensor_hashmap *hashmap = tensor_pool_alloc(pool, sizeof(struct tensor_hashmap),NULL);
    if (hashmap == NULL)
    {
        return NULL;
    }

    hashmap->size = size;
    hashmap->nodes = tensor_pool_alloc(pool, sizeof(struct tensor_hashmap_node) * size, NULL);
    if (hashmap->nodes == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        hashmap->nodes[i] = NULL;
    }
    hashmap->pool = pool;

    // Return success
    return hashmap;
}

// Return a value from the hashmap or NULL if not found
void *tensor_hashmap_get(struct tensor_hashmap *hashmap, void* key)
{
    assert(hashmap != NULL);
    assert(key != NULL);

    size_t hash = tensor_hashmap_key(hashmap,key);
    size_t index = hash % hashmap->size;
    while (hashmap->nodes[index] != NULL)
    {
        if (hashmap->nodes[index]->key == key)
        {
            return hashmap->nodes[index]->value;
        }
        index = (index + 1) % hashmap->size;
    }

    // Key not found
    return NULL;
}

// Put a value into the hashmap, returns the key or NULL on error
void* tensor_hashmap_put(struct tensor_hashmap *hashmap, void* key, void *value)
{
    assert(hashmap != NULL);
    assert(key != NULL);

    // Find a spot for the key
    size_t hash = tensor_hashmap_key(hashmap,key);
    size_t index = hash % hashmap->size;
    while (hashmap->nodes[index] != NULL)
    {
        if (hashmap->nodes[index]->key == key)
        {
            // Replace current value
            hashmap->nodes[index]->value = value;
            return key;
        }
        index = (index + 1) % hashmap->size;
    }

    // Insert a new node
    hashmap->nodes[index] = tensor_pool_alloc(hashmap->pool, sizeof(struct tensor_hashmap_node), NULL);
    if (hashmap->nodes[index] == NULL)
    {
        return NULL;
    }
    hashmap->nodes[index]->key = key;
    hashmap->nodes[index]->value = value;

    // Return success
    return key;
}