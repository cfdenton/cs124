#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "strassen.h"

#define ENTRY_LIM 3 

void print_matrix(struct matrix *matrix);


int main(int argc, char *argv[]) {
    (void) argc;
    //assert(argc == 3 || argc == 4);
    printf("hello\n");
    int mode = atoi(argv[1]);
    if (mode == 0) {
        long n = strtol(argv[2], NULL, 10);
        char *filename = argv[3];

        struct matrix *matrix1 = init_blank(n);
        struct matrix *matrix2 = init_blank(n);

        fill(filename, matrix1, matrix2, n);

        struct matrix *result = init_blank(n);
        strassen_mult(matrix1, matrix2, result);
        print_diag(result);
    } else if (mode == 1) {
        srand(time(NULL));
        long n = strtol(argv[2], NULL, 10);
        
        struct matrix *matrix1 = init_rand(n, ENTRY_LIM);
        struct matrix *matrix2 = init_rand(n, ENTRY_LIM);
        print_matrix(matrix1);
        print_matrix(matrix2);
        struct matrix *result1 = init_blank(n);
        struct matrix *result2 = init_blank(n);
        struct matrix *result3 = init_blank(n);
        regular_mult(matrix1, matrix2, result1);
        strassen_mult(matrix1, matrix2, result2);
        subtract_matrix(result1, result2, result3);
        print_matrix(result1);
        print_matrix(result2);
        print_matrix(result3);
    }
   
    return 0;
}


