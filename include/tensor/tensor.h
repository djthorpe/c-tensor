

#ifndef TENSOR_H
#define TENSOR_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////

// Maximum number of supported dimensions
#define TENSOR_MAX_DIMS 8

///////////////////////////////////////////////////////////////////////////////

// Data types
typedef enum
{
    UINT32_T,
    INT32_T,
    UINT64_T,
    INT64_T,
    FLOAT32_T,
    FLOAT64_T,
} tensor_dtype_t;

// Opaque tensor
typedef struct tensor_instance tensor_t;

// Opaque pool of tensors
typedef struct tensor_pool_instance tensor_pool_t;

// Opaque string
typedef struct tensor_str_instance tensor_str_t;

///////////////////////////////////////////////////////////////////////////////
// MEMORY POOL

// Create a new tensor pool, returns NULL on error
extern tensor_pool_t *tensor_pool_create(uint32_t memsize);

// Destroy tensor pool
extern void tensor_pool_destroy(tensor_pool_t *pool);

// Allocate N bytes from the pool, returns NULL on error
extern void *tensor_pool_alloc(tensor_pool_t *pool, size_t size);

///////////////////////////////////////////////////////////////////////////////
// TENSORS

// Create a value node, returns NULL on error
extern tensor_t *tensor_create_int32(tensor_pool_t *pool, uint32_t *dims);
extern tensor_t *tensor_create_uint32(tensor_pool_t *pool, uint32_t *dims);
extern tensor_t *tensor_create_int64(tensor_pool_t *pool, uint32_t *dims);
extern tensor_t *tensor_create_uint64(tensor_pool_t *pool, uint32_t *dims);
extern tensor_t *tensor_create_float32(tensor_pool_t *pool, uint32_t *dims);
extern tensor_t *tensor_create_float64(tensor_pool_t *pool, uint32_t *dims);

// Create a scalar with given value, returns NULL on error
extern tensor_t *tensor_int32(tensor_pool_t *pool, int32_t value);
extern tensor_t *tensor_uint32(tensor_pool_t *pool, uint32_t value);
extern tensor_t *tensor_int64(tensor_pool_t *pool, int64_t value);
extern tensor_t *tensor_uint64(tensor_pool_t *pool, uint64_t value);
extern tensor_t *tensor_float32(tensor_pool_t *pool, float value);
extern tensor_t *tensor_float64(tensor_pool_t *pool, double value);

// Create a vector with given values, returns NULL on error
extern tensor_t *tensor_int32_vec(tensor_pool_t *pool, int32_t *values, uint32_t nelems);
extern tensor_t *tensor_uint32_vec(tensor_pool_t *pool, uint32_t* values, uint32_t nelems);
extern tensor_t *tensor_int64_vec(tensor_pool_t *pool, int64_t* values, uint32_t nelems);
extern tensor_t *tensor_uint64_vec(tensor_pool_t *pool, uint64_t* values, uint32_t nelems);
extern tensor_t *tensor_float32_vec(tensor_pool_t *pool, float* values, uint32_t nelems);
extern tensor_t *tensor_float64_vec(tensor_pool_t *pool, double* values, uint32_t nelems);

///////////////////////////////////////////////////////////////////////////////
// OPERATIONS

// Create an operation node, returns NULL on error
extern tensor_t *tensor_add(tensor_t *a, tensor_t *b);

///////////////////////////////////////////////////////////////////////////////
// STRINGS

extern const char *tensor_cstring(tensor_str_t *str);
extern tensor_str_t *tensor_sprintf(tensor_pool_t *pool, const char *fmt, ...);
extern tensor_str_t *tensor_describe(tensor_pool_t *pool, tensor_t *tensor);
#endif
