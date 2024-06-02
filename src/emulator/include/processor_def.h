#ifndef PROCESSOR_DEF_H
#define PROCESSOR_DEF_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//processor struct
struct processor{
          uint64_t genregs[31];
          uint64_t pc;
          bool pstate[4];
          uint32_t memory[524288];
  };
#endif
