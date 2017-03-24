#include <stdlib.h>
#include <assert.h>
#include "strassen.h"
#include "stdio.h"
#include "stdlib.h"

struct matrix *init(long n, long off_i, long off_j, val_t *m) {
    struct matrix *matrix = (struct matrix *) malloc(sizeof(struct matrix));
    
    matrix->n = n;
    matrix->off_i = off_i;
    matrix->off_j = off_j;
    matrix->m = m;
    return matrix;
}

struct matrix *init_blank(long n) {
    struct matrix *m = init(n, 0, 0, NULL);
    m->m = (val_t *) malloc(n * n * sizeof(val_t));
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

struct matrix *create(long n) {
	
	FILE* file = fopen("file.csv", "r");
	struct matrix *matrix = init_blank(n);
	long counter = 0;
	val_t x;

	while(counter < n*n) {
		if (fscanf(file, "%d", &x) == EOF) {
			printf("Too few numbers in file.\n");
			break;
		}
		long i = counter / n;
		long j = counter % n;
		put(matrix, i, j, x);
		counter++;
	}
	return matrix;
}

