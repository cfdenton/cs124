#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "strassen.h"

struct matrix *init(struct matrix *matrix, long n, long subn, long off_i, long off_j, val_t *m) {
    if (!matrix)
        matrix = (struct matrix *) malloc(sizeof(struct matrix));
    matrix->n = n;
    matrix->subn = subn;
    matrix->off_i = off_i;
    matrix->off_j = off_j;
    matrix->m = m;
    return matrix;
}

struct matrix *init_blank(long n) {
    struct matrix *m = (struct matrix *) malloc(sizeof(struct matrix));
    init(m, n, n, 0, 0, NULL);
    m->m = (val_t *) calloc(n * n, sizeof(val_t));
    return m;
}


struct matrix *init_rand(long n, long entry_lim) {
    val_t add;
    struct matrix *m = init_blank(n);
    for (long i = 0; i < m->n; i++) {
        for (long j = 0; j < m->n; j++) {
            add = (val_t) rand() % entry_lim;
            put(m, i, j, add);
        }
    }
    return m;
}

struct matrix *init_blank_padded(long n) {
    long new_size = (long) pow(2, ceil(log(n) / log(2)));
    struct matrix *new = init_blank(new_size);
    return new;
}

struct matrix *pad_matrix(struct matrix *matrix) {
    long new_size = (long) pow(2, ceil(log(matrix->n) / log(2)));    
    struct matrix *new = init_blank(new_size);
    for (long i = 0; i < matrix->n; i++) {
        for (long j = 0; j < matrix->n; j++) {
            put(new, i, j, get(matrix, i, j));
        }
    }
    return new;
}

void destroy_matrix(struct matrix *m) {
    free(m->m);
    free(m);
}


/* 
 * get the value at row i, column j, in matrix of size n
 * performs automatic padding 
 */
val_t get(struct matrix *matrix, long i, long j) {
    if (i < matrix->n && j < matrix->n) {
        long idx = i + matrix->off_i + matrix->n * (j + matrix->off_j);
        return matrix->m[idx];
    }
    else
        return 0;
}

void put(struct matrix *matrix, long i, long j, val_t new_val) {
    if (matrix->off_i + i < matrix->n && matrix->off_j + j < matrix->n) {
        long idx = matrix->off_i + i + matrix->n * (j + matrix->off_j);
        matrix->m[idx] = new_val;
    } 
}

void add(struct matrix *matrix, long i, long j, val_t new_val) {
    if (i < matrix->n && j < matrix->n) {
        long idx = i + matrix->off_i + matrix->n * (j + matrix->off_j);
        matrix->m[idx] += new_val;
    } else
        assert(0);
}

void add_matrix(struct matrix *a, struct matrix *b, struct matrix *res) {
    for (long i = 0; i < a->subn; i++) {
        for (long j = 0; j < a->subn; j++) {
            put(res, i, j, get(a, i, j) + get(b, i, j));
        }
    }
}

void copy_matrix(struct matrix *a, struct matrix *b) {
    for (long i = 0; i < a->subn; i++) {
        for (long j = 0; j < a->subn; j++) {
            put(b, i, j, get(a, i, j));
        }
    }
}

void subtract_matrix(struct matrix *a, struct matrix *b, struct matrix *res) {
    for (long i = 0; i < a->n; i++) {
        for (long j = 0; j < a->n; j++) {
            put(res, i, j, get(a, i, j) - get(b, i, j));
        }
    }

}

void print_matrix(struct matrix *matrix) {
    for (long i = 0; i < matrix->subn; i++) {
        for (long j = 0; j < matrix->subn; j++) {
            printf("%d ", get(matrix, i, j));
        }
        printf("\n");
    }
    printf("\n");
}
