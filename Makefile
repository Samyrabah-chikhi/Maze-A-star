# Compiler
CC = gcc

# Output
TARGET = main.exe

# All source files
SRCS = $(wildcard *.c)

# Object files
OBJS = $(SRCS:.c=.o)

# SDL path
SDL_PATH = C:/Users/samy/Desktop/Web/SDL/x86_64-w64-mingw32

# Flags
CFLAGS = -I $(SDL_PATH)/include -I $(SDL_PATH)/include/SDL3
LDFLAGS = -L $(SDL_PATH)/lib -lSDL3

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -f *.o $(TARGET)