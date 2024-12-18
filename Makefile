# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -Ilibraries/include -g
LDFLAGS = -Llibraries -lSDL2 -lSDL2_image

# Output executable name
TARGET = WarriorBlockEngine.exe

# Source directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC_FILES = \
    $(SRC_DIR)/error/e_default.c $(SRC_DIR)/error/e_window.c \
    $(SRC_DIR)/input/inputs.c $(SRC_DIR)/input/key_input.c \
    $(SRC_DIR)/main/garbage_collector.c $(SRC_DIR)/main/main.c $(SRC_DIR)/main/rendering.c $(SRC_DIR)/main/window.c \
    $(SRC_DIR)/util/clocks.c $(SRC_DIR)/util/debug_tools.c $(SRC_DIR)/util/drawing_tools.c \
    $(SRC_DIR)/util/string_tools.c $(SRC_DIR)/util/tools.c $(SRC_DIR)/util/vector_2D.c \
    $(SRC_DIR)/util/vector_3D.c

# Create a list of object files by replacing .c with .o and src with obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target to build the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)  # Create the obj directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
