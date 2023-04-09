
#ifndef TENSOR_TENSOR_H
#define TENSOR_TENSOR_H

typedef enum
{
    NONE = 0,
    CAST,       // Cast to a new dtype
    MUL_SCALAR, // Multiply a by scalar b
    MUL_MATRIX, // Multiply a by b
} tensor_op_t;

struct tensor_instance
{
    // Data type
    tensor_dtype_t dtype;

    // Number of dimensions and values
    uint8_t ndims;
    uint32_t nvalues;

    // Number of elements in each dimension
    uint32_t dims[TENSOR_MAX_DIMS + 1];

    // Data
    void *data;

    // Operation and arguments
    tensor_op_t op;
    tensor_t *a;
    tensor_t *b;
};

// Create a new tensor with given data type and dimensions, returns NULL on error
tensor_t *tensor_dtype_create(tensor_pool_t *pool, tensor_dtype_t dtype, uint32_t *dims);

// Return true if the tensor is a scalar
bool tensor_is_scalar(tensor_t *t);

// Return true if the tensor is a vector
bool tensor_is_vector(tensor_t *t);

#endif // TENSOR_TENSOR_H
