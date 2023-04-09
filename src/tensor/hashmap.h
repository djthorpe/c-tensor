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
    tensor_pool_t *pool;
    int size;
    struct tensor_hashmap_node **nodes;
};

///////////////////////////////////////////////////////////////////////////////

// Create a new hashmap with up to size elements
extern struct tensor_hashmap *tensor_hashmap_create(tensor_pool_t *pool, size_t size);

// Return a value from the hashmap or NULL if not found
extern void *tensor_hashmap_get(struct tensor_hashmap *hashmap, void *key);

// Put a value into the hashmap, returns the key or NULL on error
extern void *tensor_hashmap_put(struct tensor_hashmap *hashmap, void *key, void *value);

///////////////////////////////////////////////////////////////////////////////

#endif
