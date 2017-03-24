#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "strassen.h"

int strassen_subroutine(struct matrix *a, struct matrix *b, struct matrix *c, 
        struct matrix **alloc, struct matrix **alloc2, int depth);
int switch_mult(struct matrix *a, struct matrix *b, struct matrix *res, 
        struct matrix **alloc, struct matrix **alloc2, int depth);


int regular_mult(struct matrix *a, struct matrix *b, struct matrix *res) {
    assert(a->subn == b->subn && b->subn == res->subn);
    val_t r;
    for (long j = 0; j < a->subn; j++) {
        for (long i = 0; i < a->subn; i++) {
            r = 0;
            for (long k = 0; k < a->subn; k++) {
                r += get(a, i, k) * get(b, k, j);
            }
            put(res, i, j, r);
        }
    }
    return 0;
}
    

int strassen_mult(struct matrix *matrix1, struct matrix *matrix2, struct matrix *res) {
    /* pad if necessary */
    struct matrix *a, *b, *c;
    if (floor(log(matrix1->n) / log(2)) != log(matrix1->n) / log(2)) {
        a = pad_matrix(matrix1);
        b = pad_matrix(matrix2);
        c = pad_matrix(res);
    } else { 
        a = matrix1;
        b = matrix2;
        c = res;
    }

    /* preallocate submatrix structs */
    long depth = (long) floor(log(matrix1->n) / log(2)) + 1;
    struct matrix **alloc = (struct matrix **) malloc(depth*sizeof(struct matrix *));
    for (int i = 0; i < depth; i++) {
        alloc[i] = (struct matrix *) calloc(NUM_ALLOC, sizeof(struct matrix));
    }

    struct matrix **alloc2 = (struct matrix **) malloc(depth*sizeof(struct matrix *));
    long size = matrix1->n;
    for (int i = 0; i < depth; i++) {
        alloc2[i] = (struct matrix *) calloc(NUM_ALLOC2, sizeof(struct matrix));
        for (int j = 0; j < NUM_ALLOC2; j++) {
            (alloc2[i] + j)->m = (val_t *) calloc(size, sizeof(val_t));
            if (size % 2)
                size = size % 2 + 1;
            else
                size = size % 2;
        }
    }

    /* run strassen */
    strassen_subroutine(a, b, c, alloc, alloc2, 0);

    /* transfer results */
    c->subn = a->n;
    copy_matrix(c, res);

    return 0;
}


int strassen_subroutine(struct matrix *a, struct matrix *b, struct matrix *c, 
        struct matrix **alloc, struct matrix **alloc2, int depth) 
{
    assert(a->subn == b->subn && b->subn == c->subn);

    /* base case */
    if (a->subn == 1) {
        put(c, 0, 0, get(a, 0, 0)*get(b, 0, 0));
        return 0;
    }

    /* set size of subarrays */
    long subn;
    if (a->subn % 2)
        subn = a->subn/2 + 1;
    else 
        subn = a->subn/2;

   
    /* initialize submatrices */
    struct matrix *a11 = init(alloc[depth], a->n, subn, a->off_i, a->off_j, a->m);
    struct matrix *a12 = init(alloc[depth] + 1, a->n, subn, a->off_i, a->off_j + subn, a->m);
    struct matrix *a21 = init(alloc[depth] + 2, a->n, subn, a->off_i + subn, a->off_j, a->m);
    struct matrix *a22 = init(alloc[depth] + 3, a->n, subn, a->off_i + subn, a->off_j + subn, a->m);

    struct matrix *b11 = init(alloc[depth] + 4, b->n, subn, b->off_i, b->off_j, b->m);
    struct matrix *b12 = init(alloc[depth] + 5, b->n, subn, b->off_i, b->off_j + subn, b->m);
    struct matrix *b21 = init(alloc[depth] + 6, b->n, subn, b->off_i + subn, b->off_j, b->m);
    struct matrix *b22 = init(alloc[depth] + 7, b->n, subn, b->off_i + subn, b->off_j + subn, b->m);
    struct matrix *c11 = init(alloc[depth] + 8, c->n, subn, c->off_i, c->off_j, c->m);
    struct matrix *c12 = init(alloc[depth] + 9, c->n, subn, c->off_i, c->off_j + subn, c->m);
    struct matrix *c21 = init(alloc[depth] + 10, c->n, subn, c->off_i + subn, c->off_j, c->m);
    struct matrix *c22 = init(alloc[depth] + 11, c->n, subn, c->off_i + subn, c->off_j + subn, c->m);
    printf("a11\n");
    print_matrix(a11);
    /* the first four buffers are for the intermediate 'm' matrices */
    struct matrix *buf1 = init(alloc2[depth], subn, subn, 0, 0, alloc2[depth][0].m);
    struct matrix *buf2 = init(alloc2[depth] + 1, subn, subn, 0, 0, alloc2[depth][1].m);
    struct matrix *buf3 = init(alloc2[depth] + 2, subn, subn, 0, 0, alloc2[depth][2].m);
    struct matrix *buf4 = init(alloc2[depth] + 3, subn, subn, 0, 0, alloc2[depth][3].m);
    struct matrix *buf5 = init(alloc2[depth] + 4, subn, subn, 0, 0, alloc2[depth][4].m);
    struct matrix *buf6 = init(alloc2[depth] + 5, subn, subn, 0, 0, alloc2[depth][5].m);


    /* To compute c11, compute m1 m4 m5 m7 */
    /* m1 */

    add_matrix(a11, a22, buf5);
    add_matrix(b11, b22, buf6);

    switch_mult(buf5, buf6, buf1, alloc, alloc2, depth+1);
    printf("m1\n");
    print_matrix(buf1);


    /* m4 */
    subtract_matrix(b21, b11, buf6);
    switch_mult(a22, buf6, buf2, alloc, alloc2, depth+1);

    /* m5 */
    add_matrix(a11, a12, buf5);
    switch_mult(buf5, b22, buf3, alloc, alloc2, depth+1);

    /* m7 */
    subtract_matrix(a12, a22, buf5);
    add_matrix(b21, b22, buf6);
    switch_mult(buf5, buf6, buf4, alloc, alloc2, depth+1);

    /* c11 */
    add_matrix(buf1, buf2, c11);
    subtract_matrix(c11, buf3, c11);
    add_matrix(c11, buf4, c11);

    /* To compute c12, overwrite m7: m1 m4 m5 m3 */
    subtract_matrix(b12, b22, buf6);
    switch_mult(a11, buf6, buf4, alloc, alloc2, depth+1);

    /* c12 */
    add_matrix(buf3, buf4, c12);
    
    /* To compute c21, overwrite m5: m1 m4 m2 m3 */
    add_matrix(a21, a22, buf5);
    switch_mult(buf5, b11, buf3, alloc, alloc2, depth+1);

    /* c21 */
    add_matrix(buf2, buf3, c21);

    /* To compute c22, overwrite m4: m1 m6 m2 m3 */
    subtract_matrix(a21, a11, buf5);
    add_matrix(b11, b12, buf6);
    switch_mult(buf5, buf6, buf2, alloc, alloc2, depth+1);

    /* c22 */
    subtract_matrix(buf1, buf3, c22);
    add_matrix(c22, buf4, c22);
    add_matrix(c22, buf2, c22);

    return 0;
}

int switch_mult(struct matrix *a, struct matrix *b, struct matrix *res, 
        struct matrix **alloc, struct matrix **alloc2, int depth) 
{
    assert(a->subn == b->subn && b->subn == res->subn);
    if (a->subn >= SWITCH_THRESH)
        strassen_subroutine(a, b, res, alloc, alloc2, depth);
    else
        regular_mult(a, b, res); 
    return 0;
}
