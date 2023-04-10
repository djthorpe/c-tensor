

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

// Opaque graph
typedef struct tensor_graph_instance tensor_graph_t;

// Opaque string
typedef struct tensor_str_instance tensor_str_t;

///////////////////////////////////////////////////////////////////////////////
// TENSORS

// Unique identifier for a tensor
extern uint32_t tensor_id(tensor_t *t);

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

// Return scalar value
extern int32_t tensor_int32_value(tensor_t *t);
extern uint32_t tensor_uint32_value(tensor_t *t);
extern int64_t tensor_int64_value(tensor_t *t);
extern uint64_t tensor_uint64_value(tensor_t *t);
extern float tensor_float32_value(tensor_t *t);
extern double tensor_float64_value(tensor_t *t);

// Create a vector with given values, returns NULL on error
extern tensor_t *tensor_int32_vec(tensor_pool_t *pool, int32_t *values, uint32_t nelems);
extern tensor_t *tensor_uint32_vec(tensor_pool_t *pool, uint32_t *values, uint32_t nelems);
extern tensor_t *tensor_int64_vec(tensor_pool_t *pool, int64_t *values, uint32_t nelems);
extern tensor_t *tensor_uint64_vec(tensor_pool_t *pool, uint64_t *values, uint32_t nelems);
extern tensor_t *tensor_float32_vec(tensor_pool_t *pool, float *values, uint32_t nelems);
extern tensor_t *tensor_float64_vec(tensor_pool_t *pool, double *values, uint32_t nelems);

///////////////////////////////////////////////////////////////////////////////
// OPERATIONS

// Create an operation node to cast to a specific type
extern tensor_t *tensor_cast(tensor_pool_t *pool, tensor_dtype_t type, tensor_t *a);

// Perform multiplication on two tensors, or one tensor and a scalar
extern tensor_t *tensor_mul(tensor_pool_t *pool, tensor_t *a, tensor_t *b);

///////////////////////////////////////////////////////////////////////////////
// GRAPHS

// Construct the graph which allows a to be evaluated, returns NULL on error
extern tensor_graph_t *tensor_graph_create(tensor_pool_t *pool, tensor_t *a);

// Perform the evaluation and return the output node, returns NULL on error
extern tensor_t *tensor_graph_evaluate(tensor_graph_t *graph);

///////////////////////////////////////////////////////////////////////////////
// POOL

// Create a new tensor pool, returns NULL on error
extern tensor_pool_t *tensor_pool_create(uint32_t memsize);

// Destroy tensor pool
extern void tensor_pool_destroy(tensor_pool_t *pool);

// Allocate N bytes from the pool, returns NULL on error
// and set a unique id for the allocation if id is not NULL
extern void *tensor_pool_alloc(tensor_pool_t *pool, size_t size, uint32_t *id);

// Return size of memory pool
extern size_t tensor_pool_size(tensor_pool_t *pool);

// Return used bytes of memory pool
extern size_t tensor_pool_used(tensor_pool_t *pool);

///////////////////////////////////////////////////////////////////////////////
// STRINGS

// Return the string as a cstring
extern const char *tensor_cstring(tensor_str_t *str);

// Return a string from a printf-like format
extern tensor_str_t *tensor_str_printf(tensor_pool_t *pool, const char *fmt, ...);

// Describe the tensor (id, type, op, dimensions)
extern tensor_str_t *tensor_str_describe(tensor_pool_t *pool, tensor_t *tensor);

// Print the tensor
extern tensor_str_t *tensor_str_print(tensor_pool_t *pool, tensor_t *tensor);

// Return the length of a string
extern size_t tensor_str_len(tensor_str_t *str);

#endif
