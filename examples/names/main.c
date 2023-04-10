
#include <tensor/tensor.h>
#include <tensor/csv.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    tensor_pool_t *pool = tensor_pool_create(1024);
    assert(pool != NULL);

    if (argc != 2)
    {
        printf("Usage: %s filename.csv\n", argv[0]);
        return -1;
    }

    // Create CSV parser
    tensor_csv_t *csv = tensor_csv_create(pool, ',');
    assert(csv != NULL);

    // Open file
    FILE *fh = fopen(argv[1], "r");
    if (fh == NULL)
    {
        printf("error opening file: %s\n", argv[1]);
        return -2;
    }

    // Read lines until exit
    while (true)
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t bytes = getline(&line, &len, fh);
        if (bytes == -1)
        {
            break;
        }
        assert(line);
        if(!tensor_csv_parseline(csv, line)) {
            printf("error parsing line: %s\n", line);
        } else {
            printf("parsed: %s", line);
        }
        free(line);
    }

    // Close filehandle, destroy pool
    fclose(fh);
    tensor_pool_destroy(pool);
    return 0;
}
