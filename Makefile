CC=gcc -std=c99
CFLAGS = -ggdb3 -W -Wall -Wextra -Werror -O3
LDFLAGS =
LIBS =

default: strassen

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

strassen: matrix.o matrixmult.o strassen.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)
