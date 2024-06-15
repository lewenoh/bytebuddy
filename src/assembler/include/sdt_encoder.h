#ifndef SDT_ENCODER_H
#define SDT_ENCODER_H

#include <stdint.h>
#include "table_def.h"

uint32_t sdt_encoder(uint32_t address, char instruction[6][30]);

#endif
