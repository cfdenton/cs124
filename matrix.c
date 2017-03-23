#include <assert.h>
#include "strassen.h"

void init(long off_i, long off_j, val_t *m);

/* 
 * get the value at row i, column j, in matrix of size n
 * performs automatic padding 
 */
val_t get(struct matrix *matrix, long i, long j) {
    if (i < matrix->n && j < matrix->n) {
        long idx = i + matrix->off_i + matrix->n * (j + matrix->off_i);
        return matrix->m[idx];
    }
    else
        return 0;
}

void put(struct matrix *matrix, long i, long j, val_t new_val) {
    long idx = matrix->off_i + i + matrix->n * (j + matrix->off_j);
    matrix->m[idx] = new_val;
}

void add(struct matrix *matrix, long i, long j, val_t new_val) {
    if (i < matrix->n && j < matrix->n) {
        long idx = i + matrix->off_i + matrix->n * (j + matrix->off_j);
        matrix->m[idx] += new_val;
    } else
        assert(0);
}

void add_matrix(struct matrix *a, struct matrix *b, struct matrix *res) {
    long idx1, idx2, idx3;
    for (long i = 0; i < a->n; i++) {
        for (long j = 0; j < a->n; j++) {
            idx1 = i + a->off_i + a->n * (j + a->off_j);
            idx2 = i + b->off_i + b->n * (j + b->off_j);
            idx3 = i + res->off_i + res->n * (j + res->off_j);
            res->m[idx3] = a->m[idx1] + b->m[idx2];
        }
    }
}
