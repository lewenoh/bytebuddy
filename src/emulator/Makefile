CC = gcc

CFLAGS = -Wall -g -Iinclude
LDFLAGS = -Llib
LDLIBS  = -lm

SRC_DIR = src
INC_DIR = include
TEST_DIR = test
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(SRC_FILES))

BUILD = emulate

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD) $(SRC_DIR)/*.o core

# Object files rules
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(wildcard $(INC_DIR)/*.h) $(INC_DIR)/processor_def
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: all clear
