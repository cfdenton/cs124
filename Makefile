CC=gcc -std=c99
CFLAGS = -ggdb3 -W -Wall -Wextra -Werror -O3
LDFLAGS =
LIBS =

default: main

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

main: matrix.o matrixmult.o strassen.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)
