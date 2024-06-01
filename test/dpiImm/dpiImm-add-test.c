#include <stdio.h>
#include <stdbool.h>

void testcond( bool ok, char *testname)
{
	printf( "T %s: %s\n", testname, ok?"OK":"FAIL");
}

// here should create a sample processor and have regs empty except for two
// and do uint_64 addition and test that the answer is correct
// like
// set ir to be the fixed instruction for this type of addition
// set registers to be certain numbers and then test it.
// testcond ( dpiImm( .. , p) == 1, "addition of 4 and 5 is 9")
