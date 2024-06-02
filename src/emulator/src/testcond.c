#include <stdbool.h>
#include "testcond.h"

void testcond( bool ok, char *testname)
{
        printf( "T %s: %s\n", testname, ok?"OK":"FAIL");
};
