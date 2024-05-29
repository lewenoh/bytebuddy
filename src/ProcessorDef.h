#include <stdlib.h>
#include <stdbool.h>

//processor struct
struct processor{
          int genregs[31];
          int pc;
          bool pstate[4];
          int memory[524288];
  };
