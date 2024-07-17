#include <stdlib.h>
#include <string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - CREATE

// Create scalar with value
inline tensor_t *tensor_int32(tensor_pool_t *pool, int32_t value)
{
    return tensor_dtype_create(pool, INT32_T, NULL, &value);
}

inline tensor_t *tensor_uint32(tensor_pool_t *pool, uint32_t value)
{
    return tensor_dtype_create(pool, UINT32_T, NULL, &value);
}

tensor_t *tensor_int64(tensor_pool_t *pool, int64_t value)
{
    return tensor_dtype_create(pool, INT64_T, NULL, &value);
}

tensor_t *tensor_uint64(tensor_pool_t *pool, uint64_t value)
{
    return tensor_dtype_create(pool, UINT64_T, NULL, &value);
}

tensor_t *tensor_float32(tensor_pool_t *pool, float value)
{
    return tensor_dtype_create(pool, FLOAT32_T, NULL, &value);
}

tensor_t *tensor_float64(tensor_pool_t *pool, double value)
{
    return tensor_dtype_create(pool, FLOAT64_T, NULL, &value);
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS - GET VALUE

// Return a scalar tensor with the value of the tensor
inline int32_t tensor_int32_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == INT32_T);
    assert(tensor_is_scalar(t));
    return *((int32_t *)t->data);
}

inline uint32_t tensor_uint32_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == UINT32_T);
    assert(tensor_is_scalar(t));
    return *((uint32_t *)t->data);
}

inline int64_t tensor_int64_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == INT64_T);
    assert(tensor_is_scalar(t));
    return *((int64_t *)t->data);
}
inline uint64_t tensor_uint64_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == UINT64_T);
    assert(tensor_is_scalar(t));
    return *((uint64_t *)t->data);
}
inline float tensor_float32_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == FLOAT32_T);
    assert(tensor_is_scalar(t));
    return *((float *)t->data);
}

inline double tensor_float64_value(tensor_t *t)
{
    assert(t != NULL);
    assert(t->dtype == FLOAT64_T);
    assert(tensor_is_scalar(t));
    return *((double *)t->data);
}
