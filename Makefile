# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -Iinclude/SDL3 -c
LDLIBS = -Llib -lSDL3 -lSDL3_image -lSDL3_ttf -lRaylib -lopengl32 -lgdi32 -lwinmm

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Recursive wildcard function to find all .c files in SRC_DIR and subdirs
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Files
SRCS = $(call rwildcard,$(SRC_DIR)/,*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
EXEC = $(BUILD_DIR)/WarriorBlockEngine

# Default target
all: $(EXEC)
	./$(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $@

# Compile source files to object files (single rule for all, creates subdirs as needed)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

# Clean build directory
clean:
	rm -f $(OBJS) $(EXEC)
	rm -rf $(BUILD_DIR)/*/
