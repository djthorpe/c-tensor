
#ifndef TENSOR_BASE_H
#define TENSOR_BASE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////

// Opaque pool of tensors
typedef struct tensor_pool_instance tensor_pool_t;

// Opaque hashmap
typedef struct tensor_hashmap_instance tensor_hashmap_t;

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
tensor_pool_t *tensor_pool_create(uint32_t memsize);

/**
 * Destroy a memory pool, freeing all resources
 *
 * The memory resources (including string data) is freed, and the memory is
 * returned to the system.
 *
 * @param pool        The memory pool
 */
void tensor_pool_destroy(tensor_pool_t *pool);

/**
 * Reset a memory pool, freeing all resources
 *
 * The memory resources (including string data) are invalidated, so the pool
 * can be reused
 *
 * @param pool        The memory pool
 */
void tensor_pool_zero(tensor_pool_t *pool);

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

///////////////////////////////////////////////////////////////////////////////
// HASHMAP

/**
 * Create a new hashmap with up to size elements
 *
 * @param pool               Pool to allocate hashmap from
 * @param size               Size of the hashmap in number of elements
 * @return                   Hashmap or NULL if the hashmap could not be created
 */
tensor_hashmap_t *tensor_hashmap_create(tensor_pool_t *pool, size_t size);

/**
 * Return a value from the hashmap based on a void* key
 *
 * @param hashmap            The hashmap to retrieve the value from
 * @param key                The key to retrieve the value for. The key cannot be NULL.
 * @return                   The value or NULL if not found
 */
void *tensor_hashmap_get(tensor_hashmap_t *hashmap, void *key);

/**
 * Return a value from the hashmap based on a cstring key
 *
 * @param hashmap            The hashmap to retrieve the value from
 * @param key                The NULL-terminated cstring key to retrieve the value for.
 *                           The key cannot be NULL.
 * @return                   The value or NULL if not found
 */
void *tensor_hashmap_get_cstring(tensor_hashmap_t *hashmap, const char *key);

/**
 * Put a value in the hashmap based on a void* key
 *
 * If the key already exists, the value is replaced.
 *
 * @param hashmap            The hashmap to write to
 * @param key                The key to write the value for. The key cannot be NULL.
 * @param value              The value to write. The value can be NULL.
 * @return                   Returns true if successful.
 */
bool tensor_hashmap_put(tensor_hashmap_t *hashmap, void *key, void *value);

/**
 * Put a cstring value in the hashmap
 *
 * If the key already exists, the value is replaced.
 *
 * @param hashmap            The hashmap to write to
 * @param pool               The memory pool used for key storage
 * @param key                The key to write the value for. The key cannot be NULL.
 * @param value              The value to write. The value can be NULL.
 * @return                   Returns true if successful.
 */
bool tensor_hashmap_put_cstring(tensor_hashmap_t *hashmap, tensor_pool_t *pool, const char *key, void *value);

///////////////////////////////////////////////////////////////////////////////
// DEBUG

/*
 * Print an expression and Panic
 */
void tensor_panic(const char *file, int line, const char *expr);

/*
 * Print a debug message
 */
void tensor_printf(const char *file, int line, const char *fmt, ...);

#ifdef assert
#undef assert
#endif

#ifndef NDEBUG
#define debug(...) \
    tensor_printf(__FILE__, __LINE__, __VA_ARGS__)
#define assert(e) \
    ((void)((e) ? 0 : tensor_panic(__FILE__, __LINE__, #e)))
#else
#define tensor_debug(...)
#define assert(e)
#endif

#endif
