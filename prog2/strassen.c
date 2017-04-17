#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

#define ENTRY_LIM 3 

void print_matrix(struct matrix *matrix);


int main(int argc, char *argv[]) {
    srand(time(NULL));

    int mode;
    long n;
    if (argc > 1)
        mode = atoi(argv[1]);
    else 
        mode = 0;
    if (argc > 2)
        n = strtol(argv[2], NULL, 0);
    else
        n = 256;

    struct matrix *matrix1 = init_rand(n, ENTRY_LIM);
    struct matrix *matrix2 = init_rand(n, ENTRY_LIM);
    struct matrix *result1 = init_blank(n);
    struct matrix *result2 = init_blank(n);
    struct matrix *diff = init_blank(n);
    strassen_mult(matrix1, matrix2, result1);
    regular_mult(matrix1, matrix2, result2);
    subtract_matrix(result1, result2, diff);
   
    if (mode == 1) {
        print_matrix(result1);
        print_matrix(result2);
        print_matrix(diff);
    }
    return 0;
}


