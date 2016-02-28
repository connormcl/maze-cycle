# Maze Cycle Finder
C program for finding a cycle in a maze.

## Description
For this problem, you are given a rectangular maze consisting of wall squares (represented by 0) and path squares (represented by 1). Two path squares are considered to be adjacent if they are at most one square away orthogonally or diagonally; in chess terms, two path squares are adjacent if a king can move from one to the other in one turn. The input to your program is a maze in which the graph consisting of all path squares is connected and contains at most one cycle, where a cycle is a sequence of distinct squares s1, s2, …, sk where each si is adjacent to si + 1 and sn is adjacent to s1. Your job is to write a program maze that finds this cycle if it exists, and marks all of its squares as cycle squares (represented by 2).

## Usage
Clone the repository
```
$ git clone git@github.com:connormcl/maze-cycle.git
```
Switch to the project directory
```
$ cd maze-cycle
```
Run the Makefile
```
$ make
```
Run the executable with one of the ```testFiles/*.in.pgm``` files as input
```
$ ./maze < testFiles/5-5-1.in.pgm
```

## Input and output format

The input to your program should be taken from stdin, in a restricted version of raw PGM format, an old image format designed to be particularly easy to parse. The input file header will be a line that looks like it was generated by the printf conversion string "P5 %d %d 255\n", where the first int value is the width of the image in columns and the second is the height of the image in rows; the same conversion string can be given to scanf to parse this line. Following the newline will be a long sequence of bytes, each representing one pixel of the image, with each row following immediately after the previous one. These bytes will be either 0 or 1 depending on whether that position in the maze is a wall or a path.

The output to your program should be in the same format, with the difference that now some of the bytes in the image data may be 2, indicating the cycle. If there is no cycle, the output should be identical to the input. Your program is not required to detect or respond in any particular way to input mazes that violate the format or do not contain a connected graph of path squares, although you are encouraged to put in reasonable error checking for your own benefit during testing.

## Other information
Completed as an assignment during **CPSC 223: Data Structures and Programming Techniques** taught by James Aspnes during Spring 2015
