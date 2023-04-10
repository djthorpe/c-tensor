#include <stdio.h>

#include <tensor/tensor.h>
#include <tensor/csv.h>
#include "test.h"

void test_csv_000()
{
    printf("Running test_csv_000\n");
    tensor_pool_t *pool = tensor_pool_create(1024);
    ASSERT_NOTNULL(pool);

    tensor_csv_t *csv = tensor_csv_create(pool, ',');
    ASSERT_NOTNULL(csv);
    bool success = tensor_csv_parseline(csv, "Hello,World");
    ASSERT(success);
    ASSERT(tensor_csv_eor(csv));
    ASSERT_EQUALS(1, tensor_csv_nlines(csv));

    tensor_pool_destroy(pool);
}

void test_csv()
{
    test_csv_000();
}
