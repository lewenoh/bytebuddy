//
// Created by js5422 on 12/06/24.
//

#include "../include/testcond.h"
#include <stdbool.h>
#include <stdio.h>

void testcond(bool ok, char *testname ) {
    printf("T %s: %s\n", testname, ok?"OK":"FAIL");
}
