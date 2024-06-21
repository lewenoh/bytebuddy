#ifndef DPI_ENCODER_H
#define DPI_ENCODER_H

#include <stdint.h>
#include "table_def.h"
#include "tokenise.h"

uint32_t dpi_encoder(char instruction[MAX_ARGS][MAX_ARG_LENGTH]);

#endif
