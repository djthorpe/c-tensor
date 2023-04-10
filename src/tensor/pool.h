
#ifndef TENSOR_POOL_H
#define TENSOR_POOL_H

///////////////////////////////////////////////////////////////////////////////

struct tensor_pool_instance
{
    uint32_t memsize;
    uint32_t memused;
    void *mem;

    // The string pool is a linked list of strings
    tensor_str_t* str;

    // The number of allocations
    uint32_t nallocs;
};

///////////////////////////////////////////////////////////////////////////////

// Allocate a new string in the pool and initialize the string to an empty
// value. Return NULL if the allocation failed.
tensor_str_t *tensor_pool_alloc_str(tensor_pool_t *pool, size_t size);

#endif
