# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Target executable
TARGET = example

# Source files
SRC = example.c olive.c
# Object files
OBJ = $(SRC:.c=.o)

# Build target
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Rule to compile source files into object files
%.o: %.c olive.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJ)
