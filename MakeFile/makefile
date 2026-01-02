CC = gcc
CFLAGS = -Iinclude -Wall
SRC = $(wildcard src/*.c) $(wildcard src/builtins/*.c) $(wildcard src/filesystem/*.c)
OBJ = $(SRC:.c=.o)
TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)