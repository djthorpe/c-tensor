

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

///////////////////////////////////////////////////////////////////////////////
// TENSORS

// Unique identifier for a tensor
extern uint32_t tensor_id(tensor_t *t);

// Return dimension propoerties
extern bool tensor_is_scalar(tensor_t *t);
extern bool tensor_is_vector(tensor_t *t);

// Create a tensor, returns NULL on error
extern tensor_t *tensor_create(tensor_pool_t *pool, tensor_dtype_t type, uint32_t *dims);

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

/**
 * Cast a tensor to a different data type
 * 
 * @param pool        The memory pool to use for creating the tensor operation
 * @param type        The data type to cast to
 * @param a           The tensor argument
 * @return            The tensor which is the output node of the operation.
 *                    Returns NULL on error. Typically the error will be due
 *                    to insufficient memory in the pool. If the data type
 *                    of the tensor is already the same as the requested type,
 *                    then the tensor is returned unchanged.
 */
extern tensor_t *tensor_cast(tensor_pool_t *pool, tensor_dtype_t type, tensor_t *a);

/**
 * Create a multiplication tensor operation on two tensors
 * 
 * Multiplication can occur on two tensors of the same shape, or if
 * one tensor is a scalar. In the latter case, the scalar is broadcast
 * to the shape of the other tensor.
 * 
 * @param pool        The memory pool to use for creating the tensor operation
 * @param a           The first tensor argument
 * @param b           The second tensor argument
 * @return            The tensor which is the output node of the operation,
 *                    or NULL on error. Typically the error will be due to
 *                    insufficient memory in the pool, or the data types of
 *                    the tensors are not not same.
 */
extern tensor_t *tensor_mul(tensor_pool_t *pool, tensor_t *a, tensor_t *b);

///////////////////////////////////////////////////////////////////////////////
// GRAPHS

/**
 * Construct a graph which allows a tensor calculation to be evaluated
 * 
 * @param pool        The memory pool to use for creating the graph
 * @param a           The tensor to evaluate
 * @return            The tensor graph, or NULL on error.
 *                    Typically the error will be due to insufficient memory
 *                    in the pool or because the graph could not be
 *                    constructed, due to circular dependencies.
 */
extern tensor_graph_t *tensor_graph_create(tensor_pool_t *pool, tensor_t *a);

/**
 * Perform the evaluation and return the output node
 * 
 * @param graph       The graph to evaluate
 * @return            The tensor which is the output node of the graph, or NULL
 *                    if the graph could not be evaluated, usually due to a
 *                    failing tensor operation.
 */
extern tensor_t *tensor_graph_evaluate(tensor_graph_t *graph);

///////////////////////////////////////////////////////////////////////////////
// POOL

/**
 * Create a new memory pool
 * 
 * The memory pool is used to a fixed allocation of memory for tensors and graphs.
 * Ensure you allocate enough memory for the pool. The pool is also used to allocate
 * memory for strings and tokens, but as strings can be of arbitrary length, the
 * string data is not stored in the pool.
 *
 * @param memsize     The size of the memory pool in bytes
 * @return            The memory pool, or NULL if it could not be created due to
 *                    insufficient memory.
 */
extern tensor_pool_t *tensor_pool_create(uint32_t memsize);

/**
 * Destroy a memory pool, freeing all resources
 * 
 * The memory resources (including string data) is freed, and the memory is 
 * returned to the system.
 *
 * @param pool        The memory pool
 */
extern void tensor_pool_destroy(tensor_pool_t *pool);

/**
 * Allocate memory from the memory pool and set a unique id for the memory
 * allocation.
 * 
 * @param pool        The memory pool
 * @param size        The size of the memory allocation in bytes
 * @param id          A pointer reference to a unique identifier to be set 
 *                    for the memory allocation. Pass NULL if this is not
 *                    required.
 * @return            A pointer to the memory allocation, or NULL if the
 *                    allocation failed due to insufficient memory. In this
 *                    case, increase the size of the memory pool when creating
 *                    the pool.
 */
extern void *tensor_pool_alloc(tensor_pool_t *pool, size_t size, uint32_t *id);

/**
 * Return the total size of the memory pool in bytes
 * 
 * @param pool        The memory pool
 * @return            The size of the memory pool in bytes, not including
 *                    string data.
 */
extern size_t tensor_pool_size(tensor_pool_t *pool);

/**
 * Return the used size of the memory pool in bytes
 * 
 * @param pool        The memory pool
 * @return            The size of the used memory pool in bytes, not including
 *                    string data.
 */
extern size_t tensor_pool_used(tensor_pool_t *pool);

/**
 * Return the used size for string data in bytes
 * 
 * @param pool        The memory pool
 * @return            The size of the string data in bytes, not including
 *                    the memory pool size.
 */
extern size_t tensor_pool_str_used(tensor_pool_t *pool);

#endif
