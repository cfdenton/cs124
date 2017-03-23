/*
 * Header for CS124 programming assignment 2
 * Matrix multiplication with Strassen's algorithm
 * Carl Denton and Menaka Narayanan
 */


typedef int val_t;

struct matrix {
    long n;
    long off_i;
    long off_j;
    val_t *m;
};

struct matrix *init(long n, long off_i, long off_j, val_t *m);
struct matrix *init_blank(long n);
struct matrix *init_rand(long n, long entry_lim);

val_t get(struct matrix *matrix, long i, long j);
void put(struct matrix *matrix, long i, long j, val_t new_val);
void add(struct matrix *matrix, long i, long j, val_t add_val);

int strassen_mult(struct matrix *a, struct matrix *b, struct matrix *res);
int regular_mult(struct matrix *a, struct matrix *b, struct matrix *res);

void add_matrix(struct matrix *matrix1, struct matrix *matrix2, struct matrix *res);
