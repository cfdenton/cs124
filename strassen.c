#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

#define ENTRY_LIM 3 

void print_matrix(struct matrix *matrix);


int main() {
    srand(time(NULL));

    long n = 4;
    struct matrix *matrix1 = init_rand(n, ENTRY_LIM);
    print_matrix(matrix1);
    struct matrix *matrix2 = init_rand(n, ENTRY_LIM);
    print_matrix(matrix2);

    struct matrix *result1 = init_blank(n);
    struct matrix *result2 = init_blank(n);
    struct matrix *diff = init_blank(n);
    strassen_mult(matrix1, matrix2, result1);
    regular_mult(matrix1, matrix2, result2);
    subtract_matrix(result1, result2, diff);
   
    print_matrix(result1);
    print_matrix(result2);
    //print_matrix(diff);
    return 0;
}


