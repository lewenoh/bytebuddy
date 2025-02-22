#ifndef SDT_ENCODER_H
#define SDT_ENCODER_H

#include <stdint.h>
#include "table_def.h"
#include "tokenise.h"

uint32_t sdt_encoder(uint32_t address, char instruction[MAX_ARGS][MAX_ARG_LENGTH]);

#endif
