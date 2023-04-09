#include <assert.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static void tensor_graph_visit(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);

    // TODO: We don't visit the same node twice
    // TODO: How do we check if the graph has circular dependencies?

    tensor_debug(t->pool, "tensor_graph_visit: %s\n", tensor_cstring(tensor_describe(pool, t)));

    // Visit the dependencies
    if (t->a != NULL)
    {
        tensor_graph_visit(pool, t->a);
    }
    if (t->b != NULL)
    {
        tensor_graph_visit(pool, t->b);
    }

    // TODO: Mark the tensor as visited
    // TODO: Push it onto the stack of evaluations
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Construct the graph which allows a tensor to be evaluated, returns NULL on error
tensor_graph_t *tensor_graph_create(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);

    // Create a graph
    tensor_graph_t *graph = tensor_pool_alloc(pool, sizeof(tensor_graph_t));
    if (graph == NULL)
    {
        return NULL;
    }

    // If a has no dependencies, then return t
    if (t->op == NONE)
    {
        graph->root = t;
        return graph;
    }
    assert(t->a != NULL || t->b != NULL);

    // We go through all nodes in the graph
    tensor_graph_visit(pool, t);

    // Not yet implemented
    return NULL;
}

// Perform the evaluation and return the output node (which has now been computed),
// returns NULL on error
tensor_t *tensor_evaluate(tensor_graph_t *graph)
{
    assert(graph != NULL);
    // Not yet implemented
    return NULL;
}
