CC=gcc
files=$(wildcard *.c)
flags=-lm -lraylib -Wall
devflags=-g -fsanitize=address
bin=chess

default: clean
	$(CC) $(files) $(flags) -o $(bin)
dev: clean
	$(CC) $(files) $(flags) $(devflags) -o $(bin)
clean:
	rm -rf $(bin)

run: clean default
	./$(bin)

