
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <tensor/tensor.h>
#include <tensor/string.h>

#define buf_size 80
static char buf[buf_size];

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

    // Create a pool for the line tokens
    tensor_pool_t *linepool = tensor_pool_create(2 * 1024);
    assert(linepool != NULL);

    // Read lines until exit
    bool success = true;
    while (success)
    {
        // Read the line
        char *line = NULL;
        size_t len = 0;
        ssize_t bytes = getline(&line, &len, fh);
        if (bytes == -1)
        {
            break;
        }
        assert(line);

        // Parse the line into tokens
        tensor_str_t *str = tensor_str_create(linepool, line);
        assert(str);
        free(line);
        tensor_str_token_t *token = tensor_str_csv_parse(linepool, csv, str, NULL);
        if (token == NULL)
        {
            printf("error parsing line: %s\n", tensor_cstring(buf, buf_size, str));
            success = false;
            continue;
        }
        else
        {
            fputs("  ",stdout);
            while (token)
            {
                fputs(tensor_cstring(buf, buf_size, tensor_str_token_describe(linepool, token)),stdout);
                token = tensor_str_token_next(token);
            }
            fputs("\n",stdout);            
        }

        // Empty the pool
        tensor_pool_zero(linepool);
    }

    // Close filehandle, destroy pool
    fclose(fh);
    tensor_pool_destroy(pool);
    return 0;
}
