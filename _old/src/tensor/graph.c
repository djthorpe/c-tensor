#include "tensor_private.h"

#define buf_size 80
static char buf[buf_size];

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

// Push a new tensor onto the right hand side
static struct tensor_graph_node *tensor_graph_push(tensor_graph_t *graph, tensor_t *t)
{
    assert(graph);
    assert(t);

    struct tensor_graph_node *node = tensor_pool_alloc(graph->pool, sizeof(struct tensor_graph_node), NULL);
    if (node == NULL)
    {
        return NULL;
    }
    node->tensor = t;
    node->prev = NULL;
    node->next = NULL;

    // Set up linked nodes
    if (graph->left == NULL)
    {
        assert(graph->right == NULL);
        graph->left = node;
        graph->right = node;
    }
    else
    {
        assert(graph->right != NULL);
        node->prev = graph->right;
        graph->right->next = node;
        graph->right = node;
    }

    return node;
}

static struct tensor_graph_node *tensor_graph_visit(tensor_graph_t *graph, tensor_hashmap_t *visited, tensor_t *t)
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
    if (!tensor_hashmap_put(visited, t, node))
    {
        return NULL;
    }

    // Push it onto the stack of evaluations
    return tensor_graph_push(graph, t);
}

// Evaluate a node and return the next node to evaluate
static struct tensor_graph_node *tensor_graph_node_evaluate(tensor_graph_t *graph, struct tensor_graph_node *node)
{
    assert(graph != NULL);
    assert(node != NULL);
    assert(node->tensor != NULL);
    debug("Evaluating node %s\n", tensor_cstring(buf, buf_size, tensor_str_describe(graph->pool, node->tensor)));
    if(!tensor_evaluate(graph->pool, node->tensor)) {
        debug("  failed, stopping evaluation process\n");
        graph->success = false;
        return NULL;
    };
    return node->next;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

// Construct the graph which allows a tensor to be evaluated, returns NULL on error
tensor_graph_t *tensor_graph_create(tensor_pool_t *pool, tensor_t *t)
{
    assert(pool);
    assert(t);

    // Create a graph
    tensor_graph_t *graph = tensor_pool_alloc(pool, sizeof(tensor_graph_t), NULL);
    if (graph == NULL)
    {
        return NULL;
    }
    graph->pool = pool;
    graph->left = NULL;
    graph->right = NULL;

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
    tensor_hashmap_t *visited = tensor_hashmap_create(pool, pool->nallocs);

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
    assert(graph->left != NULL);
    assert(graph->right != NULL);

    // We evaluate from left to right
    graph->success = true;
    struct tensor_graph_node *node = graph->left;
    while (node != NULL)
    {
        // Evaluate the node and move to the next one
        node = tensor_graph_node_evaluate(graph, node);
    }

    // Return the output node
    return graph->success ? graph->right->tensor : false;
}
