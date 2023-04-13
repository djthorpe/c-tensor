
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

    // ID and name
    uint32_t id;
};

// Create a new tensor with given data type and dimensions. If dims is NULL then
// a scalar is created. If elems is NULL then the tensor is created with zeros.
// If elems is not NULL then it is assigned as initial values.
tensor_t *tensor_dtype_create(tensor_pool_t *pool, tensor_dtype_t dtype, uint32_t *dims, void *elems);

// Evaluate the tensor, return true on success
bool tensor_evaluate(tensor_pool_t *pool, tensor_t *t);

// Return the data type size
size_t tensor_dtype_sizeof(tensor_dtype_t dtype);

#endif // TENSOR_TENSOR_H
