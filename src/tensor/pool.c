#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <tensor/tensor.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////

// Alignment of tensor pool memory on uint64_t boundary
#define TENSOR_POOL_ALIGN 8

///////////////////////////////////////////////////////////////////////////////

// Create a new tensor pool, returns NULL on error
tensor_pool_t *tensor_pool_create(uint32_t memsize)
{
    assert(memsize > 0);

    tensor_pool_t *pool = malloc(sizeof(tensor_pool_t));
    if (pool == NULL)
    {
        return NULL;
    }

    pool->memsize = memsize;
    pool->memused = 0;
    pool->nallocs = 0;
    pool->str = NULL;
    pool->mem = malloc(memsize);
    if (pool->mem == NULL)
    {
        free(pool);
        return NULL;
    }
    return pool;
}

// Free resources from a tensor pool
void tensor_pool_destroy(tensor_pool_t *pool)
{
    if (pool)
    {
        // Free string data
        for (tensor_str_t *str = pool->str; str != NULL;)
        {
            tensor_str_t *next = str->next;
            if (!str->constant && str->data)
            {
                free(str->data);
            }
            str = next;
        }
        free(pool->mem);
        free(pool);
    }
}

// Allocate bytes on the pool, returns NULL if memory exhausted
// and set the id value if it's not NULL
void *tensor_pool_alloc(tensor_pool_t *pool, size_t size, uint32_t *id)
{
    assert(pool != NULL);
    assert(size > 0);

    // Align size on boundary
    size = (size + TENSOR_POOL_ALIGN - 1) & ~(TENSOR_POOL_ALIGN - 1);
    if (pool->memused + size > pool->memsize)
    {
        tensor_debug(pool, "tensor_pool_alloc: memory exhausted, size=%lu, used=%lu, total=%lu\n", size, pool->memused, pool->memsize);
        return NULL;
    }
    void *ptr = pool->mem + pool->memused;
    pool->memused += size;

    // Set id if not NULL, and increase the number of allocations
    if (id != NULL)
    {
        *id = ++pool->nallocs;
    }

    return ptr;
}

// Allocate a new string in the pool and initialize the string to an empty
// value. Return NULL if the allocation failed.
tensor_str_t *tensor_pool_alloc_str(tensor_pool_t *pool, size_t size)
{
    assert(pool != NULL);

    // Allocate string
    tensor_str_t *str = tensor_pool_alloc(pool, sizeof(tensor_str_t), NULL);
    if (str == NULL)
    {
        return NULL;
    }

    // Allocate string data - but not in the pool
    if (size)
    {
        str->data = malloc(size);
        if (str->data == NULL)
        {
            return NULL;
        }
        str->data = memset(str->data, 0, size);
    }
    else
    {
        str->data = NULL;
    }

    // Initialize string
    str->size = size;
    str->constant = false;
    str->hash = 0;
    str->next = pool->str;
    pool->str = str;
    return str;
}

// Return size of memory pool
inline size_t tensor_pool_size(tensor_pool_t *pool)
{
    assert(pool != NULL);
    return pool->memsize;
}

// Return used bytes of memory pool
inline size_t tensor_pool_used(tensor_pool_t *pool)
{
    assert(pool != NULL);
    return pool->memused;
}

// Return number of used bytes for string data
size_t tensor_pool_str_used(tensor_pool_t *pool)
{
    assert(pool != NULL);
    size_t size = 0;
    for (tensor_str_t *str = pool->str; str != NULL; str = str->next)
    {
        if (!str->constant && str->data != NULL)
        {
            size += str->size;
        }
    }
    return size;
}
