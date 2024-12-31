# Variables
CC := g++
CFLAGS := -Wall -Wextra -Iinclude
BIN_DIR := bin
SRC_DIR := src
DEBUG_TARGET := $(BIN_DIR)/psa_debug
RELEASE_TARGET := $(BIN_DIR)/psa
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Targets
.PHONY: all build build-debug debug valgrind clean

# Default target
all: build

mkbin:
	@mkdir -p $(BIN_DIR)

build: mkbin
	@$(CC) $(CFLAGS) -o $(RELEASE_TARGET) $(SRC_FILES)

build-debug: mkbin
	@$(CC) $(CFLAGS) -g -o $(DEBUG_TARGET) $(SRC_FILES)

debug: build-debug
	@gdb --args $(DEBUG_TARGET) $(ARGS)

valgrind: build-debug
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(DEBUG_TARGET) $(ARGS)

run: build
	@$(RELEASE_TARGET) $(ARGS)

clean:
	@rm -rf $(BIN_DIR)
