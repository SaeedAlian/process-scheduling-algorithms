SRCS = src/main.c src/util.c src/args.c src/proc.c src/queue.c src/algorithms.c
BIN_DIR = ./bin
TARGET = $(BIN_DIR)/psa
DEBUG_TARGET = $(BIN_DIR)/psa_debug

OUTPUTS_DIR = ./outputs

CFLAGS = -Wall -Wextra
SILENT_FLAGS = -w
DEBUG_FLAGS = -g

all: build

build: mkbin
	@g++ $(CFLAGS) -o $(TARGET) $(SRCS)

sbuild: mkbin
	@g++ $(SILENT_FLAGS) -o $(TARGET) $(SRCS)

run: build
	@$(TARGET)

srun: sbuild
	@$(TARGET)

build-debug: mkbin
	@g++ $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET) $(SRCS)

debug: build-debug
	@gdb $(DEBUG_TARGET)

valgrind: build-debug
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(DEBUG_TARGET)

mkbin:
	@mkdir -p $(BIN_DIR)

clean:
	@rm $(BIN_DIR)

clean-all:
	@rm -rf $(BIN_DIR) $(OUTPUTS_DIR)
