#include <assert.h>

#include <tensor/tensor.h>
#include "private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

// Push a new tensor onto the stack and return the node
static struct tensor_graph_node *tensor_graph_push(tensor_graph_t *graph, tensor_t *t)
{
    assert(graph != NULL);
    assert(t != NULL);

    struct tensor_graph_node *node = tensor_pool_alloc(graph->pool, sizeof(struct tensor_graph_node), NULL);
    if (node == NULL)
    {
        return NULL;
    }
    node->tensor = t;
    node->next = NULL;
    if (graph->root != NULL)
    {
        node->next = graph->root;
    }
    graph->root = node;
    return node;
}

static struct tensor_graph_node *tensor_graph_visit(tensor_graph_t *graph, struct tensor_hashmap *visited, tensor_t *t)
{
    assert(visited != NULL);
    assert(t != NULL);

    // We don't visit the same node twice
    struct tensor_graph_node *node = tensor_hashmap_get(visited, t);
    if (node != NULL)
    {
        return node;
    }

    // TODO: How do we check if the graph has circular dependencies?

    // Visit the dependencies
    if (t->a != NULL)
    {
        if (!tensor_graph_visit(graph, visited, t->a))
        {
            return NULL;
        }
    }
    if (t->b != NULL)
    {
        if (!tensor_graph_visit(graph, visited, t->b))
        {
            return NULL;
        }
    }

    // Mark the tensor as visited
    if (!tensor_hashmap_put(graph->pool, visited, t, node))
    {
        return NULL;
    }

    // Push it onto the stack of evaluations
    return tensor_graph_push(graph, t);
}

static struct tensor_graph_node *tensor_graph_node_evaluate(tensor_graph_t *graph, struct tensor_graph_node *node)
{
    assert(graph != NULL);
    assert(node != NULL);
    assert(node->tensor != NULL);
    tensor_debug(graph->pool, "Evaluating node %s\n", tensor_cstring(tensor_describe(graph->pool, node->tensor)));
    tensor_evaluate(graph->pool, node->tensor);
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
    graph->pool = pool;

    // If a has no dependencies, then return graph with single node
    if (t->op == NONE)
    {
        if (!tensor_graph_push(graph, t))
        {
            return NULL;
        }
        else
        {
            return graph;
        }
    }
    assert(t->a != NULL || t->b != NULL);

    // Create a hashmap so we can keep track of what's been visited
    struct tensor_hashmap *visited = tensor_hashmap_create(pool, pool->nallocs);

    // We go through all nodes in the graph
    if (!tensor_graph_visit(graph, visited, t))
    {
        return NULL;
    }

    // Return the graph
    return graph;
}

// Perform the evaluation and return the output node
// returns NULL on error
tensor_t *tensor_graph_evaluate(tensor_graph_t *graph)
{
    assert(graph != NULL);
    assert(graph->root != NULL);

    // TODO: We evaluate in the wrong order - should be reversed
    struct tensor_graph_node *node = graph->root;
    while (node != NULL)
    {
        // Evaluate the node and move to the next one
        tensor_graph_node_evaluate(graph, node);
        node = node->next;
    }
    return graph->root->tensor;
}
