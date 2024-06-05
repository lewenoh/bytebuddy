#include "custom_tests.h"
#include "binary_load_test.h"
#include "binary_output_test.h"
#include "branch_test.h"
#include "decoder_test.h"
#include "dpiImm_add_test.h"
#include "dpiReg_test.h"
#include "ll_test.h"
#include "sdt_test.h"

void run_custom_tests() {
    binary_load_test();
    binary_output_test();
    test_decoder();
	testbranch();
	dpiImm_add_tests();
	dpiReg_test();
	test_ll();
	test_sdt();
}