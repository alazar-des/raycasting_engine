# Source files
OBJS = src/handle_input.c src/initSDL.c src/main.c src/parse.c src/rc.c src/render.c src/map.c

# Compiler
CC = gcc

# Compiler flags
COMPILER_FLAGS = -Wall -Werror -Wextra -pedantic

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lm

# Name of executable
OBJ_NAME = main

# Target
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
