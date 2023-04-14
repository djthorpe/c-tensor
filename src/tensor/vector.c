#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - CREATE VECTOR

/**
 * Create a vector of data type int32
 */
inline tensor_t *tensor_int32_vec(tensor_pool_t *pool, uint32_t nelems, int32_t *elems) {
    assert(pool != NULL);
    assert(nelems > 0);
    return tensor_dtype_create(pool, INT32_T, (uint32_t[]){nelems, 0}, elems);
}

/**
 * Create a vector of data type uint32
 */
inline tensor_t *tensor_uint32_vec(tensor_pool_t *pool, uint32_t nelems, uint32_t *elems) {
    assert(pool != NULL);
    assert(nelems > 0);
    return tensor_dtype_create(pool, UINT32_T, (uint32_t[]){nelems, 0}, elems);
}

/**
 * Create a vector of data type int64
 */
inline tensor_t *tensor_int64_vec(tensor_pool_t *pool, uint32_t nelems, int64_t *elems) {
    assert(pool != NULL);
    assert(nelems > 0);
    return tensor_dtype_create(pool, INT64_T, (uint32_t[]){nelems, 0}, elems);
}

/**
 * Create a vector of data type uint64
 */
inline tensor_t *tensor_uint64_vec(tensor_pool_t *pool, uint32_t nelems, uint64_t *elems) {
    assert(pool != NULL);
    assert(nelems > 0);
    return tensor_dtype_create(pool, UINT64_T, (uint32_t[]){nelems, 0}, elems);
}

/**
 * Create a vector of data type float32
 */
inline tensor_t *tensor_float32_vec(tensor_pool_t *pool, uint32_t nelems, float *elems) {
    assert(pool != NULL);
    assert(nelems > 0);
    return tensor_dtype_create(pool, FLOAT32_T, (uint32_t[]){nelems, 0}, elems);
}

/**
 * Create a vector of data type float64
 */
inline tensor_t *tensor_float64_vec(tensor_pool_t *pool, uint32_t nelems, double *elems) {
    assert(pool != NULL);
    assert(nelems > 0);
    return tensor_dtype_create(pool, FLOAT64_T, (uint32_t[]){nelems, 0}, elems);
}
