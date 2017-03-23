#include "strassen.h"

val_t get(val_t *matrix, long i, long j, long n) {
    long idx = i + n*j;
    return matrix[idx];
}

void put(val_t *matrix, long i, long j, long n, val_t new_val) {
    long idx = i + n*j;
    matrix[idx] = new_val;
}

int add(val_t *a, val_t *b, long n) {
    (void) a; (void) b; (void) n;
    return 0;
}
