#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

#define ENTRY_LIM 3

void print_matrix(struct matrix *matrix);

struct matrix *init_rand(long n) {
    struct matrix *matrix = (struct matrix *) malloc(sizeof(struct matrix));
    matrix->off_i = 0;
    matrix->off_j = 0;
    matrix->n = n;
    matrix->m = (val_t *) malloc(n * n * sizeof(val_t));
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            val_t add = (val_t) rand() % ENTRY_LIM;
            put(matrix, i, j, add);
        }
    }
    return matrix;
}

struct matrix *init_blank(long n) {
    struct matrix *matrix = (struct matrix *) malloc(sizeof(struct matrix));
    matrix->off_i = 0;
    matrix->off_j = 0;
    matrix->n = n;
    matrix->m = (val_t *) calloc(n * n, sizeof(val_t));
    return matrix;
}

int main() {
    srand(time(NULL));

    long n = 3;
    struct matrix *matrix1 = init_rand(n);
    print_matrix(matrix1);
    struct matrix *matrix2 = init_rand(n);
    print_matrix(matrix2);

    struct matrix *result = init_blank(n);
    regular_mult(matrix1, matrix2, result);
    print_matrix(result);
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
