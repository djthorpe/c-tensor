#ifndef TENSOR_HASHMAP_H
#define TENSOR_HASHMAP_H

///////////////////////////////////////////////////////////////////////////////

struct tensor_hashmap_node
{
    void *key;
    void *value;
};

struct tensor_hashmap
{
    int size;
    struct tensor_hashmap_node **nodes;
};

///////////////////////////////////////////////////////////////////////////////

// Create a new hashmap with up to size elements
struct tensor_hashmap *tensor_hashmap_create(tensor_pool_t *pool, size_t size);

// Return a value from the hashmap or NULL if not found
void *tensor_hashmap_get(struct tensor_hashmap *hashmap, void *key);

// Put a value into the hashmap, returns the key or NULL on error
void *tensor_hashmap_put(tensor_pool_t *pool, struct tensor_hashmap *hashmap, void *key, void *value);

///////////////////////////////////////////////////////////////////////////////

#endif