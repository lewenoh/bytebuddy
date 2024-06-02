#ifndef DPIIMM_ADD_TEST_H
#define DPIIMM_ADD_TEST_H


#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "processor_def.h"
#include "dpiImm.h"
#include "dpiImm_add_test.h"
#include "testcond.h"

void init_processor(struct processor *p);
void test1(struct processor *p);

void dpiImm_add_tests();

#endif
