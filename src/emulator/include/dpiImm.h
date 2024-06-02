#ifndef DPIIMM_H
#define DPIIMM_H

#include <stdint.h>
#include "processor_def.h"

void setFlags_arithmetic(uint64_t result, int regsize, struct processor *p);
void dpiImm( struct processor *p, uint32_t ir );

#endif
