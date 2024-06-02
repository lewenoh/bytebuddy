#include <stdbool.h>
#include <stdio.h>
#include "testcond.h"
void testCond(bool ok, char *testname ) {
        printf("T %s: %s\n", testname, ok?"OK":"FAIL");
}
