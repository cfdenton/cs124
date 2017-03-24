#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "strassen.h"

int strassen_subroutine(struct matrix *a, struct matrix *b, struct matrix *c, 
        struct matrix **alloc, int depth);
int switch_mult(struct matrix *a, struct matrix *b, struct matrix *res, struct matrix **alloc, int depth);

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
        alloc[i] = (struct matrix *) malloc(NUM_ALLOC * sizeof(struct matrix *));
    }

    /* run strassen */
    strassen_subroutine(a, b, c, alloc, 0);

    /* transfer results */
    c->subn = a->n;
    copy_matrix(c, res);

    return 0;
}


int strassen_subroutine(struct matrix *a, struct matrix *b, struct matrix *c, 
        struct matrix **alloc, int depth) 
{
    assert(a->subn == b->subn && b->subn == c->subn);

    printf("strassen subroutine\n");

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
    struct matrix *a11 = init(NULL, a->n, subn, a->off_i, a->off_j, a->m);
    struct matrix *a12 = init(NULL, a->n, subn, a->off_i, a->off_j + subn, a->m);
    struct matrix *a21 = init(NULL, a->n, subn, a->off_i + subn, a->off_j, a->m);
    struct matrix *a22 = init(NULL, a->n, subn, a->off_i + subn, a->off_j + subn, a->m);
    struct matrix *b11 = init(NULL, b->n, subn, b->off_i, b->off_j, b->m);
    struct matrix *b12 = init(NULL, b->n, subn, b->off_i, b->off_j + subn, b->m);
    struct matrix *b21 = init(NULL, b->n, subn, b->off_i + subn, b->off_j, b->m);
    struct matrix *b22 = init(NULL, b->n, subn, b->off_i + subn, b->off_j + subn, b->m);
    struct matrix *c11 = init(NULL, c->n, subn, c->off_i, c->off_j, c->m);
    struct matrix *c12 = init(NULL, c->n, subn, c->off_i, c->off_j + subn, c->m);
    struct matrix *c21 = init(NULL, c->n, subn, c->off_i + subn, c->off_j, c->m);
    struct matrix *c22 = init(NULL, c->n, subn, c->off_i + subn, c->off_j + subn, c->m);

    /* the first four buffers are for the intermediate 'm' matrices */
    struct matrix *buf1 = init_blank(subn);
    struct matrix *buf2 = init_blank(subn);
    struct matrix *buf3 = init_blank(subn);
    struct matrix *buf4 = init_blank(subn);

    /* the last two are to store additions and subtractions before the multiplicatiosn */
    struct matrix *buf5 = init_blank(subn);
    struct matrix *buf6 = init_blank(subn);

    /* To compute c11, compute m1 m4 m5 m7 */
    /* m1 */

    add_matrix(a11, a22, buf5);
    add_matrix(b11, b22, buf6);
    switch_mult(buf5, buf6, buf1, alloc, depth+1);

    /* m4 */
    subtract_matrix(b21, b11, buf6);
    switch_mult(a22, buf6, buf2, alloc, depth+1);

    /* m5 */
    add_matrix(a11, a12, buf5);
    switch_mult(buf5, b22, buf3, alloc, depth+1);

    /* m7 */
    subtract_matrix(a12, a22, buf5);
    add_matrix(b21, b22, buf6);
    switch_mult(buf5, buf6, buf4, alloc, depth+1);

    /* c11 */
    add_matrix(buf1, buf2, c11);
    subtract_matrix(c11, buf3, c11);
    add_matrix(c11, buf4, c11);

    /* To compute c12, overwrite m7: m1 m4 m5 m3 */
    subtract_matrix(b12, b22, buf6);
    switch_mult(a11, buf6, buf4, alloc, depth+1);

    /* c12 */
    add_matrix(buf3, buf4, c12);
    
    /* To compute c21, overwrite m5: m1 m4 m2 m3 */
    add_matrix(a21, a22, buf5);
    switch_mult(buf5, b11, buf3, alloc, depth+1);

    /* c21 */
    add_matrix(buf2, buf3, c21);

    /* To compute c22, overwrite m4: m1 m6 m2 m3 */
    subtract_matrix(a21, a11, buf5);
    add_matrix(b11, b12, buf6);
    switch_mult(buf5, buf6, buf2, alloc, depth+1);

    /* c22 */
    subtract_matrix(buf1, buf3, c22);
    add_matrix(c22, buf4, c22);
    add_matrix(c22, buf2, c22);

    destroy_matrix(buf1);
    destroy_matrix(buf2);
    destroy_matrix(buf3);
    destroy_matrix(buf4);
    destroy_matrix(buf5);
    destroy_matrix(buf6);

    return 0;
}

int switch_mult(struct matrix *a, struct matrix *b, struct matrix *res, struct matrix **alloc, int depth) {
    assert(a->subn == b->subn && b->subn == res->subn);
    if (a->subn >= SWITCH_THRESH)
        strassen_subroutine(a, b, res, alloc, depth);
    else
        regular_mult(a, b, res); 
    return 0;
}
