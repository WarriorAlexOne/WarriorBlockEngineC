# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -Iinclude/SDL3 -c
LDLIBS = -Llib -lSDL3 -lSDL3_image -lopengl32 -lgdi32 -lwinmm

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ENTITY_DIR = $(SRC_DIR)/Entity
ERROR_DIR = $(SRC_DIR)/Error
INPUT_DIR = $(SRC_DIR)/Input
SETUP_DIR = $(SRC_DIR)/Setup
TEST_DIR = $(SRC_DIR)/Test
UTIL_DIR = $(SRC_DIR)/Util
WORLD_DIR = $(SRC_DIR)/World

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
	   $(wildcard $(ENTITY_DIR)/*.c) \
	   $(wildcard $(ERROR_DIR)/*.c) \
	   $(wildcard $(INPUT_DIR)/*.c) \
	   $(wildcard $(SETUP_DIR)/*.c) \
	   $(wildcard $(TEST_DIR)/*.c) \
	   $(wildcard $(UTIL_DIR)/*.c) \
	   $(wildcard $(WORLD_DIR)/*.c)
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

$(BUILD_DIR)/%.o: $(ENTITY_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(ERROR_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(INPUT_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SETUP_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(UTIL_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(WORLD_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

.PHONY: all clean