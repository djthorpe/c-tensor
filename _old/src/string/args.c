#include <stdlib.h>
#include <string.h>
#include "tensor_private.h"

// TODO
#define buf_size 80
static char buf[buf_size];

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS

static struct tensor_str_args_flag_instance *tensor_str_args_getflag(tensor_str_args_t *ctx, const char *name)
{
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
    else
    {
        ctx->pool = pool;
        ctx->parsed = false;
    }

    // Set the command name
    ctx->command = tensor_str_create(pool, (char *)(argv[0]));
    if (ctx->command == NULL)
    {
        return NULL;
    }

    // Create a hashmap for the flags - allocate twice the number of arguments
    // to make it sparse
    ctx->flags = tensor_hashmap_create(pool, argc << 1);
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
        else
        {
            prev->str = str;
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
 */
bool tensor_str_args_flag(tensor_str_args_t *ctx, const char *name, const char *description, const char *value)
{
    assert(ctx);
    assert(name);
    assert(strlen(name));
    assert(description);

    // Check for existing flag - return NULL if it exists
    if (tensor_hashmap_get_cstring(ctx->flags, name) != NULL)
    {
        debug("tensor_str_args_flag: flag '%s' already exists\n", name);
        return false;
    }

    // Create a structure for the flag
    struct tensor_str_args_flag_instance *flag = tensor_pool_alloc(ctx->pool, sizeof(struct tensor_str_args_flag_instance), NULL);
    if (flag == NULL)
    {
        return false;
    }
    flag->boolean = false;
    flag->description = tensor_str_create(ctx->pool, (char *)description);
    flag->value = tensor_str_create(ctx->pool, (char *)value);
    if (flag->description == NULL || flag->value == NULL)
    {
        return false;
    }

    // Create flag, return success condition
    return tensor_hashmap_put_cstring(ctx->flags, ctx->pool, name, flag);
}


/*
 * Define a boolean flag used to parse the arguments
 */
bool tensor_str_args_switch(tensor_str_args_t *ctx, const char *name, const char *description)
{
    assert(ctx);
    assert(name);
    assert(strlen(name));
    assert(description);

    // Check for existing flag - return NULL if it exists
    if (tensor_hashmap_get_cstring(ctx->flags, name) != NULL)
    {
        debug("tensor_str_args_switch: flag '%s' already exists\n", name);
        return false;
    }

    // Create a structure for the flag
    struct tensor_str_args_flag_instance *flag = tensor_pool_alloc(ctx->pool, sizeof(struct tensor_str_args_flag_instance), NULL);
    if (flag == NULL)
    {
        return false;
    }
    flag->boolean = true;
    flag->description = tensor_str_create(ctx->pool, (char *)description);
    flag->value = NULL;
    if (flag->description == NULL)
    {
        return false;
    }

    // Create flag, return success condition
    return tensor_hashmap_put_cstring(ctx->flags, ctx->pool, name, flag);
}

/*
 * Parse the command line arguments given the defined flags
 */
bool tensor_str_args_parse(tensor_str_args_t *ctx)
{
    assert(ctx);

    // Only run parse once
    if (ctx->parsed)
    {
        return true;
    }

    // Iterate through the arguments
    tensor_str_token_t *token = ctx->args;
    tensor_str_t *flag = NULL;
    while (token)
    {
        debug("tensor_str_args_parse: %s\n", tensor_cstring(buf, buf_size, tensor_str_token_describe(ctx->pool, token)));

        // If token has a '-' or '--' prefix, then it is a flag
        if (tensor_str_token_has_prefix(token, "--") && flag == NULL)
        {
            flag = tensor_str_ref(ctx->pool, token->str, 2, tensor_str_len(token->str) - 2);
        }
        else if (tensor_str_token_has_prefix(token, "-") && flag == NULL)
        {
            flag = tensor_str_ref(ctx->pool, token->str, 1, tensor_str_len(token->str) - 1);
        }
        else
        {
            if (flag)
            {
                // TODO: Get the flag from the hashmap and set the value
                debug("  flag: %s\n", tensor_cstring(buf, buf_size, flag));
                debug("  value: %s\n", tensor_cstring(buf, buf_size, token->str));
                flag = NULL;
            }
            else
            {
                debug("  arg: %s\n", tensor_cstring(buf, buf_size, token->str));
            }
        }

        // Move to the next token
        token = token->next;
    }

    return ctx->parsed;
}
