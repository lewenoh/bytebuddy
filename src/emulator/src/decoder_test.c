#include "decoder.h"
#include <stdio.h>
#include <stdbool.h>
#define IMMEDIATE 0x1000000
#define REGISTER 0xA000000
#define SDT 0xB9000000
#define LL 0xC000000
#define BRANCH_INSTRUCTION 0x14000000

i_type imm, reg, sdt, ll, branch;


void testcond(bool ok, char *testname ) {
	printf("T %s: %s\n", testname, ok?"OK":"FAIL");
}

void test_decoder() {
	imm = DPIMM;
        reg = DPREG;
        sdt = SDT;
        ll = LL;
        branch = BRANCH;
        testcond(decode(IMMEDIATE) == imm, "Decode Immediates");
        testcond(decode(REGISTER) == reg, "Decode Reg");
        testcond(decode(SDT) == sdt, "Decode SDT");
        testcond(decode(LL) == ll, "Decode LL");
        testcond(decode(branch) == branch, "Decode Branch");
}
