CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3
all: maze
test: maze
maze: maze.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	$(RM) strategy *.o
