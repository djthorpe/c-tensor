#include <stdlib.h>
#include <string.h>
#include "tensor_private.h"

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static struct tensor_str_args_flag_instance* tensor_str_args_getflag(tensor_str_args_t *ctx, const char* name) {
    assert(ctx);
    assert(name);
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS

/*
 * Create an args object from a string array of arguments
 */
tensor_str_args_t *tensor_str_args_create(tensor_pool_t *pool, int argc, const char **argv)
{
    assert(pool);
    assert(argc > 0);
    assert(argv);

    // Create the context
    tensor_str_args_t *ctx = tensor_pool_alloc(pool, sizeof(tensor_str_args_t), NULL);
    if (ctx == NULL)
    {
        return NULL;
    }

    // Set the pool
    ctx->pool = pool;

    // Set the command name
    ctx->command = tensor_str_create(pool, (char *)(argv[0]));
    if (ctx->command == NULL)
    {
        return NULL;
    }

    // Create a hashmap for the flags
    ctx->flags = tensor_hashmap_create(pool,argc << 1);
    if (ctx->flags == NULL)
    {
        return NULL;
    }

    // Create the token list of arguments
    tensor_str_token_t *prev = NULL;
    for (int i = 1; i < argc; i++)
    {
        tensor_str_t *str = tensor_str_create(pool, (char *)(argv[i]));
        if (str == NULL)
        {
            return NULL;
        }

        // Append the token
        prev = tensor_str_token_append(pool, prev, TEXT_T, NULL);
        if (prev == NULL)
        {
            return NULL;
        }

        // Set the head token
        if (ctx->args == NULL)
        {
            ctx->args = prev;
        }
    }

    // Return success
    return ctx;
}

/*
 * Define a flag used to parse the arguments
 *
 * @param ctx                The context
 * @param name               The name of the flag, must be unique
 * @param description        The description of the flag, required
 * @param value              The default value of the flag, or NULL if the flag is required
 * @return                   Returns true if the flag was defined, false otherwise
 */
bool tensor_str_args_flag_str(tensor_str_args_t *ctx, const char *name, const char *description, const char *value)
{
    assert(ctx);
    assert(name);
    assert(description);

    // Not yet implemented
    return false;
}
