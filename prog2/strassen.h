/*
 * Header for CS124 programming assignment 2
 * Matrix multiplication with Strassen's algorithm
 * Carl Denton and Menaka Narayanan
 */

#define SWITCH_THRESH 36 

typedef int val_t;

struct matrix {
    long n;
    long subn;
    long off_i;
    long off_j;
    int padded;
    val_t *m;
};

struct matrix *init(struct matrix *matrix, long n, long subn, long off_i, long off_j, val_t *m);
struct matrix *init_blank(long n);
struct matrix *init_report(long n, struct matrix *m);
struct matrix *init_rand(long n, long entry_lim);
struct matrix *init_blank_padded(long n);
struct matrix *pad_matrix(struct matrix *matrix);

void destroy_matrix(struct matrix *mat);

val_t get(struct matrix *matrix, long i, long j);
void put(struct matrix *matrix, long i, long j, val_t new_val);
void add(struct matrix *matrix, long i, long j, val_t add_val);

int regular_mult(struct matrix *a, struct matrix *b, struct matrix *res);
int strassen_mult(struct matrix *a, struct matrix *b, struct matrix *res);

void add_matrix(struct matrix *matrix1, struct matrix *matrix2, struct matrix *res);
void subtract_matrix(struct matrix *a, struct matrix *b, struct matrix *res);    
void copy_matrix(struct matrix *a, struct matrix *b);

void print_matrix(struct matrix *matrix);
