# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -Iinclude/SDL3 -c
LDLIBS = -Llib -lSDL3 -lSDL3_image

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
EXEC = $(BUILD_DIR)/game

# Default target
all: $(BUILD_DIR) $(EXEC)
	./$(EXEC)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $@

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

.PHONY: all clean