
#ifndef TEST_H
#define TEST_H

#include <assert.h>
#define ASSERT(x) assert(x)
#define ASSERT_NOTNULL(x) assert(x != NULL)
#define ASSERT_NULL(x) assert(x == NULL)
#define ASSERT_EQUALS(x,y) assert(x == y)
#define ASSERT_NOTEQUALS(x,y) assert(x != y)
#endif
