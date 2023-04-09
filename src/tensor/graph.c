#include <assert.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Construct the graph which allows a tensor to be evaluated, returns NULL on error
tensor_graph_t *tensor_graph_create(tensor_pool_t *pool, tensor_t *a) {
    assert(pool != NULL);
    assert(a != NULL);
    // Not yet implemented
    return NULL;
}

// Perform the evaluation and return the output node (which has now been computed),
// returns NULL on error 
tensor_t* tensor_evaluate(tensor_graph_t* graph) {
    assert(graph != NULL);
    // Not yet implemented
    return NULL;
}

