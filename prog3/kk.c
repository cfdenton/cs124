#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#define repetitions 100
#define maxnum 1000000000000 
#define n 100
#define maxiter 25000 

uint64_t rand_uint64_t();
void print_arr(uint64_t *arr);
void print_sol(int *s);
int *rand_sol();
int *rand_neighbor(int *s);
int *rand_part();
int *rand_part_neighbor(int *p);
uint64_t residue(uint64_t *arr, int *sol);
uint64_t part_residue(uint64_t *arr, int *p);
uint64_t *copy_arr(uint64_t *old_arr);
uint64_t part_residue(uint64_t *arr, int *p);


uint64_t repeated_random(uint64_t *arr) {
    int *s = rand_sol();
    
    int *sp;
    for (int i = 0; i < maxiter; i++) {
        sp = rand_sol();

        if (residue(arr, sp) < residue(arr, s)) {
            free(s);
            s = sp;
        } else {
            free(sp);
        }
    }
    return residue(arr, s);
}

uint64_t hill_climbing(uint64_t *arr) {
    int *s = rand_sol();

    int *sp;
    for (int i = 0; i < maxiter; i++) {
        sp = rand_neighbor(s);
        if (residue(arr, sp) < residue(arr, s)) {
            free(s);
            s = sp;
        } else {
            free(sp);
        }
    }
    return residue(arr, s);
}

uint64_t simulated_annealing(uint64_t *arr) {
    int *s = rand_sol();
    int *spp = malloc(n * sizeof(int));
    memcpy(spp, s, n * sizeof(int));
    int *sp;
    double anneal, temp;
    for (int i = 0; i < maxiter; i++) {
        sp = rand_neighbor(s);
        
        temp = pow(10., 10.) * pow(0.8, floor(((double) i)/300.));
        //printf("temp 0 %f\n", (double) i);
        //printf("temp 1 %f\n", floor(((double) i) / 300.));
        //printf("temp %f\n", temp);
        anneal = exp(-(residue(arr, sp) - residue(arr, s))/temp);
        //printf("anneal %f\n", anneal);
        if (residue(arr, sp) < residue(arr, s)) {
            memcpy(s, sp, n * sizeof(int));
        } else if ((double) rand() / RAND_MAX < anneal) {
            memcpy(s, sp, n * sizeof(int));
        }
        if (residue(arr, s) < residue(arr, spp)) {
            memcpy(spp, s, n * sizeof(int));
        }
    }
    
    return residue(arr, spp);
}


uint64_t prep_repeated_random(uint64_t *arr) {
    int *s = rand_part();
    
    int *sp;
    for (int i = 0; i < maxiter; i++) {
        sp = rand_part();

        if (part_residue(arr, sp) < part_residue(arr, s)) {
            free(s);
            s = sp;
        } else {
            free(sp);
        }
    }
    return part_residue(arr, s);
}

uint64_t prep_hill_climbing(uint64_t *arr) {
    int *s = rand_part();

    int *sp;
    for (int i = 0; i < maxiter; i++) {
        sp = rand_part_neighbor(s);
        if (part_residue(arr, sp) < part_residue(arr, s)) {
            free(s);
            s = sp;
        } else {
            free(sp);
        }
    }
    return part_residue(arr, s);
}

uint64_t prep_simulated_annealing(uint64_t *arr) {
    int *s = rand_part();
    int *spp = malloc(n * sizeof(int));
    memcpy(spp, s, n * sizeof(int));
    int *sp;
    double anneal, temp;
    for (int i = 0; i < maxiter; i++) {
        sp = rand_part_neighbor(s);
        
        temp = pow(10., 10.) * pow(0.8, floor((double) i/300.));
        anneal = exp(-(part_residue(arr, sp) - part_residue(arr, s))/temp);
        if (part_residue(arr, sp) < part_residue(arr, s)) {
            memcpy(s, sp, n * sizeof(int));
        } else if ((double) rand() / RAND_MAX < anneal) {
            memcpy(s, sp, n * sizeof(int));
        }
        if (part_residue(arr, s) < part_residue(arr, spp)) {
            memcpy(spp, s, n * sizeof(int));
        }
    }
    
    return part_residue(arr, spp);
}



/* run the karmakar-karp algorithm on a list of numbers. In general, destroys the list */
uint64_t kk(uint64_t *arr) {
    int nonzero = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            nonzero++;
        }
    }
    
    int i, j;
    while (nonzero > 1) {
        i = 0;
        j = 1;
        for (int k = 2; k < n; k++) {
            if (arr[k] > arr[i] && arr[k] <= arr[j]) {
                i = k;
            } else if (arr[k] > arr[j] && arr[k] <= arr[i]) {
                j = k;
            } else if (arr[k] > arr[i] && arr[k] > arr[j]) {
                if (arr[i] > arr[j]) {
                    j = k;
                } else {
                    i = k;
                }
            }
        }

        if (arr[i] > arr[j]) {
            if (arr[j] > 0) {
                nonzero--;
            }
            arr[i] = arr[i] - arr[j];
            arr[j] = 0;
        } else if (arr[i] < arr[j]) {
            if (arr[i] > 0) {
                nonzero--;
            }
            arr[j] = arr[j] - arr[i];
            arr[i] = 0;
        } else if (arr[i] > 0) {
            arr[i] = 0;
            arr[j] = 0;
            nonzero -= 2;
        }
    }

    uint64_t max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            max = arr[i];
        }
    }
    free(arr);
    return max;
}







uint64_t residue(uint64_t *arr, int *sol) {
    long residue = 0;
    for (int i = 0; i < n; i++) {
        residue += ((long) arr[i]) * ((long) sol[i]);
    }
    if (residue > 0) {
        return (uint64_t) residue;
    } else {
        return (uint64_t) (-residue);
    }
}


int *rand_sol() {
    int *sol = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if ((double) rand() / RAND_MAX < .5) {
            sol[i] = 1;
        } else {
            sol[i] = -1;
        }
    }
    return sol;
}

int *rand_neighbor(int *s) {
    int *sp = malloc(n * sizeof(int));
    memcpy(sp, s, n * sizeof(int));
    
    int j, k;
    if ((double) rand() / RAND_MAX < .5) {
        j = rand() % n;
        sp[j] *= -1;
    } else {
        j = rand() % n;
        k = rand() % (n-1);
        if (k >= j) {
            k++;
        }

        sp[j] *= -1;
        sp[k] *= -1;
    }
    return sp;
}

int *rand_part() {
    int *p = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        p[i] = rand() % n;
    }
    return p;
}


int *rand_part_neighbor(int *p) {
    int *pp = malloc(n * sizeof(int));
    memcpy(pp, p, n * sizeof(int));
    
    int i, j;
    while (1) {
        i = rand() % n;
        j = rand() % n;
        if (pp[i] != j) {
            pp[i] = j;
            break;
        }
    }
    //printf("original: ");
    //print_sol(p);
    //printf("neighbor: ");
    //print_sol(pp);
    return pp;
}

uint64_t part_residue(uint64_t *arr, int *p) {
    uint64_t *new_arr = calloc(n, sizeof(uint64_t));

    for (int i = 0; i < n; i++) {
        new_arr[p[i]] += arr[i];
    }
    uint64_t result = kk(new_arr);
    return result; 
}








uint64_t *generate_random() {
    uint64_t *arr = malloc(n * sizeof(uint64_t));

    for (int i = 0; i < n; i++) {
        arr[i] = rand_uint64_t() % maxnum;
    }
    return arr;
}

uint64_t *copy_arr(uint64_t *old_arr) {
    uint64_t *new_arr = malloc(n * sizeof(uint64_t));
    
    memcpy(new_arr, old_arr, n * sizeof(uint64_t));
    return new_arr;
}


void print_arr(uint64_t *arr) {
    for (int i = 0; i < n; i++) {
        printf("%llu ", arr[i]);
    }
    printf("\n");
}

void print_sol(int *s) {
    for (int i = 0; i < n; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");
}

uint64_t rand_uint64_t() {
    uint64_t r = 0;
    r |= ((uint64_t) rand() & 0xFFFF) << 48;
    r |= ((uint64_t) rand() & 0xFFFF) << 32;
    r |= ((uint64_t) rand() & 0xFFFF) << 16;
    r |= ((uint64_t) rand() & 0xFFFF);
    return r;
}



int main(void) {
    srand(time(NULL));
    printf("seeded\n");
    //uint64_t *arr = generate_random();
    //print_arr(arr);
    //printf("repeated random: %llu\n", repeated_random(arr));
    //printf("hill climbing: %llu\n", hill_climbing(arr));
    //printf("simulated annealing: %llu\n", simulated_annealing(arr));
    //printf("prep repeated random: %llu\n", prep_repeated_random(arr));
    //printf("prep hill climbing: %llu\n", prep_hill_climbing(arr));
    //printf("prep simulated annealing: %llu\n", prep_simulated_annealing(arr));
    //printf("kk: %llu\n", kk(arr));

    uint64_t rr = 0;
    uint64_t hc = 0;
    uint64_t sa = 0;
    uint64_t prr = 0; 
    uint64_t phc = 0; 
    uint64_t psa = 0; 
    uint64_t kk_ave = 0;
    uint64_t *arr;
    for (int i = 0; i < repetitions; i++) {
        arr = generate_random();
        rr += repeated_random(arr);
        hc += hill_climbing(arr);
        sa += simulated_annealing(arr);
        prr += prep_repeated_random(arr);
        phc += prep_hill_climbing(arr);
        psa += prep_simulated_annealing(arr);
        kk_ave += kk(arr);
        printf("finished iteration %d\n", i);
    }
    printf("repeated random: %f\n", (double) rr / (double) repetitions);
    printf("hill climbing: %f\n", (double) hc / (double) repetitions);
    printf("simulated annealing: %f\n", (double) sa / (double) repetitions);
    printf("prep repeated random: %f\n", (double) prr / (double) repetitions);
    printf("prep hill climbing: %f\n", (double) phc / (double) repetitions);
    printf("prep simulated annealing: %f\n", (double) psa / (double) repetitions);
    printf("kk: %f\n", (double) kk_ave / (double) repetitions);

}
