#include "decoder.h"
#include <stdio.h>
#include <stdbool.h>
#define IMMEDIATE1 0x1000000
#define IMMEDIATE2 0x1200000
#define REGISTER1 0xA000000
#define REGISTER2 0x1A000000
//Test 1011 1000 ...
//Test 1011 1001 0100...
#define SDT1 0xB9000000
#define SDT2 0xBA400000
#define LL 0xC000000
#define BRANCH 0x14000000

void testcond(bool ok, char *testname ) {
	printf("T %s: %s\n", testname, ok?"OK":"FAIL");
}

void test_decoder() {
        testcond(decode(IMMEDIATE1)==0, "Decode Immediates");
        testcond(decode(IMMEDIATE2)==0, "Decode Immediates");
	testcond(decode(REGISTER1)==1, "Decode Reg");
	testcond(decode(REGISTER2)==1, "Decode Reg");
        testcond(decode(SDT1)==2, "Decode SDT");
	testcond(decode(SDT1)==2, "Decode SDT");
        testcond(decode(LL)==3, "Decode LL");
        testcond(decode(BRANCH)==4, "Decode Branch");
}
