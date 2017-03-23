#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "strassen.h"

int regular_mult(struct matrix *a, struct matrix *b, struct matrix *res) {
    assert(a->n == b->n && b->n == res->n);
    val_t r = 0;
    for (long j = 0; j < a->n; j++) {
        for (long i = 0; i < a->n; i++) {
            for (long k = 0; k < a->n; k++) {
                r += get(a, i, k) * get(b, k, j);
            }
            put(res, i, j, r);
            r = 0;
        }
    }
    return 0;
}

int strassen_mult(struct matrix *a, struct matrix *b, struct matrix *res) {
    //(void) a; (void) b; (void) res; 
    assert(a->n == b->n && b->n == res->n);
    long n = a->n;

    /* set size of subarrays */
    long subn;
    if (n % 2)
        subn = n/2 + 1;
    else 
        subn = n/2;
   
    /* allocate space for submultiplication buffer */
    val_t *buffer = (val_t *) calloc(n * n, sizeof(val_t));

    /* initialize submatrices */
    struct matrix *a11 = init(subn, a->off_i, a->off_j, a->m);
    struct matrix *a12 = init(subn, a->off_i, a->off_j + subn, a->m);
    struct matrix *a21 = init(subn, a->off_i + subn, a->off_j, a->m);
    struct matrix *a22 = init(subn, a->off_i + subn, a->off_j + subn, a->m);
    struct matrix *b11 = init(subn, b->off_i, b->off_j, b->m);
    struct matrix *b12 = init(subn, b->off_i, b->off_j + subn, b->m);
    struct matrix *b21 = init(subn, b->off_i + subn, b->off_j, b->m);
    struct matrix *b22 = init(subn, b->off_i + subn, b->off_j + subn, b->m);
    (void) a11; (void) a12; (void) a21; (void) a22; 
    (void) b11; (void) b12; (void) b21; (void) b22; 
    (void) buffer;
    return 0;
}

