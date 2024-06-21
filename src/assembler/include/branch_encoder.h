#ifndef BRANCH_ENCODER_H
#define BRANCH_ENCODER_H

#include <stdint.h>
#include "table_def.h"
#include "tokenise.h"

uint32_t branch_encoder(uint32_t address, char instruction[MAX_ARGS][MAX_ARG_LENGTH]);

#endif
