#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strassen.h"

int strassen_mult(val_t *a, val_t *b, val_t *res, long n) {
    (void) a; (void) b; (void) res; (void) n;
    return 0;
}

int regular_mult(val_t *a, val_t *b, val_t *res, long n) {
    val_t r = 0;
    for (long j = 0; j < n; j++) {
        for (long i = 0; i < n; i++) {
            for (long k = 0; k < n; k++) {
                r += get(a, i, k, n) * get(b, k, j, n);
            }
            put(res, i, j, n, r);
        }
    }
    return 0;
}

