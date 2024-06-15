#ifndef BRANCH_ENCODER_H
#define BRANCH_ENCODER_H

#include <stdint.h>
#include "table_def.h"

uint32_t branch_encoder(uint32_t address, char instruction[6][30]);

#endif
