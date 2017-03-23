/*
 * Header for CS124 programming assignment 2
 * Matrix multiplication with Strassen's algorithm
 * Carl Denton and Menaka Narayanan
 */


typedef int val_t;

val_t get(val_t *matrix, long i, long j, long n);
void put(val_t *matrix, long i, long j, long n, val_t new_val);

int strassen_mult(val_t *a, val_t *b, val_t *res, long n);
int regular_mult(val_t *a, val_t *b, val_t *res, long n);
