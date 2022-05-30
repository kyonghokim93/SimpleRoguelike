all:
	gcc -Wall -std=c99 src/main.c src/ass3.c -Iinclude -o bin/runMe -lncurses