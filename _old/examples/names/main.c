
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <tensor/tensor.h>
#include <tensor/string.h>

/*
 * Read a line from the input, which is separated by the linefeed.
 * Returns NULL on error, or pointer to an allocated line otherwise.
 * The caller is responsible for freeing the line.
 */
char *readline(FILE *fh)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t bytes = getline(&line, &len, fh);
    if (bytes == -1)
    {
        return NULL;
    }
    assert(bytes > 0);
    assert(line);
    return line;
}

bool readfile(FILE *fh, tensor_str_csv_t *csv)
{
    // Create a pool for the line tokens
    tensor_pool_t *pool = tensor_pool_create(2 * 1024);
    assert(pool);

    // Read lines until exit
    bool success = true;
    size_t lineno = 0;
    while (success)
    {
        // Read the line
        char *line = readline(fh);
        if (line == NULL)
        {
            break;
        }
        else
        {
            lineno++;
        }

        // Create the line in the pool
        tensor_str_t *str = tensor_str_create(pool, line);
        free(line);
        if (str == NULL)
        {
            success = false;
            continue;
        }

        // Parse into tokens
        tensor_str_token_t *token = tensor_str_csv_parse(pool, csv, str, (void *)lineno);
        if (token == NULL)
        {
            success = false;
            continue;
        }

        // Empty the pool
        tensor_pool_zero(pool);
    }

    // Return success condition
    return success;
}

int main(int argc, char **argv)
{
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool != NULL);

    if (argc != 2)
    {
        printf("Usage: %s filename.csv\n", argv[0]);
        return -1;
    }

    // Test the simple case
    tensor_str_csv_t *csv = tensor_str_csv_create(pool, 0);
    assert(csv);

    // Open file
    FILE *fh = fopen(argv[1], "r");
    if (fh == NULL)
    {
        printf("error opening file: %s\n", argv[1]);
        return -2;
    }

    // Read the file
    bool success = readfile(fh, csv);
    if (!success)
    {
        printf("error reading file: %s\n", argv[1]);
        return -3;
    }

    fclose(fh);
    tensor_pool_destroy(pool);
    return 0;
}
