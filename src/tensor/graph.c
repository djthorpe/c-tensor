#include <assert.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static void* tensor_graph_visit(struct tensor_hashmap* visited, tensor_t *t)
{
    assert(visited != NULL);
    assert(t != NULL);

    // We don't visit the same node twice
    if (tensor_hashmap_get(visited, t) != NULL)
    {
        return t;
    }

    // TODO: How do we check if the graph has circular dependencies?

    // Visit the dependencies
    if (t->a != NULL)
    {
        if(!tensor_graph_visit(visited, t->a)) {
            return NULL;
        }
    }
    if (t->b != NULL)
    {
        if(!tensor_graph_visit(visited, t->b)) {
            return NULL;
        }
    }

    // Mark the tensor as visited
    if(!tensor_hashmap_put(visited, t, t)) {
        return NULL;
    }

    // TODO: Push it onto the stack of evaluations
    tensor_debug(visited->pool, "tensor_graph_visit: %s\n", tensor_cstring(tensor_describe(visited->pool, t)));

    return t;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Construct the graph which allows a tensor to be evaluated, returns NULL on error
tensor_graph_t *tensor_graph_create(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool != NULL);
    assert(t != NULL);

    // Create a graph
    tensor_graph_t *graph = tensor_pool_alloc(pool, sizeof(tensor_graph_t), NULL);
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

    // Create a hashmap so we can keep track of what's been visited
    struct tensor_hashmap* visited = tensor_hashmap_create(pool, pool->nallocs);

    // We go through all nodes in the graph
    if(!tensor_graph_visit(visited, t)) {
        return NULL;
    }

    // Return the graph
    return graph;
}

// Perform the evaluation and return the output node (which has now been computed),
// returns NULL on error
tensor_t *tensor_evaluate(tensor_graph_t *graph)
{
    assert(graph != NULL);
    // Not yet implemented
    return NULL;
}
