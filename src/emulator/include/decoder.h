#include <stdint.h>
#include <stdbool.h>

typedef enum {DPIMM, DPREG, SDT, LL, BRANCH} i_type;
i_type decode(uint64_t ir);
void test_decoder();
