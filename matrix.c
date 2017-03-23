#include "strassen.h"
#include "stdio.h"
#include "stdlib.h"

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

val_t *create(long n) {

	FILE* file = fopen("file.csv", "r");
	val_t *array = malloc(n*n*sizeof(val_t));

	long counter = 0;
	val_t x;

	while(fscanf(file, "%d", &x) != EOF) {
		fscanf(file, "%d", &x);
		long i = n % counter;
		long j = n / counter;
		put(array, i, j, n, x);
		counter++;
	}
	return array;
}