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
    (void) a; (void) b; (void) res; 
//    assert(a->n == b->n && b->n == res->n);
//    long n = a->n;
//
//    /* set size of subarrays */
//    long subn;
//    if (n % 2)
//        subn = n/2 + 1;
//    else 
//        subn = n/2;
//   
//    /* allocate space for submultiplication buffer */
//    val_t *buffer = (val_t *) calloc(n * n, sizeof(val_t));
//
//    /* initialize submatrices */
//    struct matrix *a11 = (struct matrix *) malloc(sizeof(struct matrix));
//    a11->n = subn;
//    a11->off_i = a->off_i;
//    a11->off_j = a->off_j;
//    a11->m = a->m;
//
//    struct matrix *a12 = (struct matrix *) malloc(sizeof(struct matrix));
//    a12->n = subn;
//    a12->off_i = a->off_i;
//    a12->off_j = a->off_j + subn;
//    a11->m = a->m;
//
//    struct matrix *a21 = (struct matrix *) malloc(sizeof(struct matrix));
//    a21->n = subn;
//    a21->off_i = a->off_i + subn;
//    a21->off_j = a->off_j;
//    a21->m = a->m;
//
//    struct matrix *a22 = (struct matrix *) malloc(sizeof(struct matrix));
//    a22->n = subn;
//    a22->off_i = a->off_i + subn;
//    a22->off_j = a->off_j + subn;
//    a22->m = a->m;
//
//    struct matrix *b11 = (struct matrix *) malloc(sizeof(struct matrix));
//    b11->n = subn;
//    b11->off_i = b->off_i;
//    b11->off_j = b->off_j;
//    b11->m = b->m;
//
//    struct matrix *b12 = (struct matrix *) malloc(sizeof(struct matrix));
//    b12->n = subn;
//    b12->off_i = b->off_i;
//    b12->off_j = b->off_j + subn;
//    b11->m = b->m;
//
//    struct matrix *b21 = (struct matrix *) malloc(sizeof(struct matrix));
//    b21->n = subn;
//    b21->off_i = b->off_i + subn;
//    b21->off_j = b->off_j;
//    b21->m = b->m;
//
//    struct matrix *b22 = (struct matrix *) malloc(sizeof(struct matrix));
//    b22->n = subn;
//    b22->off_i = b->off_i + subn;
//    b22->off_j = b->off_j + subn;
//    b22->m = b->m;
   
    return 0;
}

