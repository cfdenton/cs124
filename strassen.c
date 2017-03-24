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

    struct matrix *result = init_blank(n);
    regular_mult(matrix1, matrix2, result);
    print_matrix(result);

    struct matrix *test = create(n);
    print_matrix(test);
    return 0;

}

void print_matrix(struct matrix *matrix) {
    for (long i = 0; i < matrix->n; i++) {
        for (long j = 0; j < matrix->n; j++) {
            printf("%d ", get(matrix, i, j));
        }
        printf("\n");
    }
    printf("\n");
}
