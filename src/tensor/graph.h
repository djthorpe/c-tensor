#ifndef TENSOR_GRAPH_H
#define TENSOR_GRAPH_H

///////////////////////////////////////////////////////////////////////////////

struct tensor_graph_node
{
    // The current evaluation tensor
    tensor_t *tensor;

    // The previous evaluation node
    struct tensor_graph_node *prev;

    // The next evaluation node
    struct tensor_graph_node *next;
};

struct tensor_graph_instance
{
    tensor_pool_t *pool;

    // The leftmost node for evaluation
    struct tensor_graph_node *left;

    // The rightmost node for evaluation
    struct tensor_graph_node *right;
};

///////////////////////////////////////////////////////////////////////////////

#endif
