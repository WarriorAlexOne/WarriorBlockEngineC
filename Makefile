# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Iinclude -Ilibraries/include
LDFLAGS = -Llibraries/lib -lSDL3 -lSDL3_image

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Output binary
TARGET = $(BIN_DIR)/main.exe

# Source and object files
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Define SDL dependencies and compatibility DLL
DEPS = $(BUILD_DIR)/bin/SDL3.dll $(BUILD_DIR)/bin/SDL3_image.dll $(BUILD_DIR)/bin/libwinpthread-1.dll

# Default target
all: $(TARGET) copy_deps

# Copy SDL dependencies and compatibility DLL to the bin folder
copy_deps: $(DEPS)

$(BUILD_DIR)/bin/SDL3.dll: libraries/SDL3.dll
	cp $< $@

$(BUILD_DIR)/bin/SDL3_image.dll: libraries/SDL3_image.dll
	cp $< $@

$(BUILD_DIR)/bin/libwinpthread-1.dll: libraries/libwinpthread-1.dll
	cp $< $@

# Create the output binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)/$(TARGET)

# Rebuild the project
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET) || echo "Program exited with an error!"

.PHONY: all clean rebuild run
