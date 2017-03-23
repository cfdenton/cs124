#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

#define ENTRY_LIM 2

void print_matrix(val_t *matrix, long n);

val_t *init_rand(long n) {
    val_t *matrix = (val_t *) malloc(n * sizeof(val_t));
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            val_t add = (val_t) rand() % ENTRY_LIM;
            put(matrix, i, j, n, add);
            printf("added value %d at position %ld/%ld\n", add, i, j);
        }
    }
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            val_t g = get(matrix, i, j, n);
            printf("got value %d at position %ld/%ld\n", g, i, j);
        }
    }
    return matrix;
}


int main() {
    srand(time(NULL));

    long n = 2;
    val_t *matrix1 = init_rand(n);
    val_t *matrix2 = init_rand(n);
    print_matrix(matrix1, n);
    print_matrix(matrix2, n);

    val_t *result = malloc(n * sizeof(val_t));
    regular_mult(matrix1, matrix2, result, n);
    print_matrix(result, n);
    return 0;
}

void print_matrix(val_t *matrix, long n) {
    for (long j = 0; j < n; j++) {
        for (long i = 0; i < n; i++) {
            printf("%d ", get(matrix, i, j, n));
        }
        printf("\n");
    }
    printf("\n");
}
