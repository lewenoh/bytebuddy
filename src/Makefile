CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

sdt.o: sdt.c sdt.h processor_def.h
dpiReg.o: dpiReg.c dpiReg.h processor_def.h
dpiImm.o: dpiImm.c dpiImm.h processor_def.h
decoder.o: decoder.c decoder.h processor_def.h
branch.o: branch.c branch.h processor_def.h
emulate.o: processor_def.h emulate.c

assemble: assemble.o
emulate: emulate.o



clean:
	$(RM) *.o assemble emulate
	
