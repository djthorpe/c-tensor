#ifndef TENSOR_PRIVATE_HASHMAP_H
#define TENSOR_PRIVATE_HASHMAP_H

///////////////////////////////////////////////////////////////////////////////

struct tensor_hashmap_node
{
    // The key for the node
    void *key;

    // The string length when using a cstring key
    size_t len;

    // The value for the node
    void *value;
};

struct tensor_hashmap_instance
{
    // The number of elements in the hashmap
    int size;

    // The nodes in the hashmap
    struct tensor_hashmap_node *nodes;
};

///////////////////////////////////////////////////////////////////////////////

#endif
