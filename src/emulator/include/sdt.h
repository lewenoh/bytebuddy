#ifndef SDT_H
#define SDT_H
#include <stdint.h>
#include "processor_def.h"

void sdt(struct processor *p, uint32_t ir);

#endif
