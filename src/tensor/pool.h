
#ifndef TENSOR_POOL_H
#define TENSOR_POOL_H

// Allocate a new string in the pool and initialize the string to an empty
// value. Return NULL if the allocation failed.
extern tensor_str_t *tensor_pool_alloc_str(tensor_pool_t *pool, size_t size);

#endif
