#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define maxnum 1000000000000
#define maxiter 25000
#define arrsize 100

// PROBLEMS
// make sure moduloing is correct
// mallocing?
// for random repeated every now and then we get a num like 25 as a residue

long residue(long *arr, long *sol) {
    long res = 0;
    for(long i = 0; i < arrsize; i++) {
        res += arr[i] * sol[i];
    }
    return labs(res);
}

/* generate a random array to partition. remember to free this */
long *generate_random(long n) {
    printf("Generating random array\n");

    long *arr = malloc(sizeof(long)*n);
    for (long i=0; i<n; i++) {
        arr[i] = (long) random() % maxnum;
    }
    return arr;
}

long anneal(long *arr, long *s, long *sp, long i) {
    return exp(-(residue(arr, sp) - residue(arr, s))/
        (pow(10., 10.)*pow(0.8, floor(i / 300.))));
}

long kk(long *arr) {
    printf("Running KK\n");

    int nonzero = 0;
    for (int i=0; i<arrsize; i++) {
        if (arr[i] > 0) {
            nonzero++;
        }
    }

    long i, j;
    while(nonzero > 1) {
        i = random() % (arrsize - 1);
        j = random() % (arrsize - 1);
        if (i == j) {
            continue;
        }

        if (arr[i] > arr[j]) {
            if (arr[j] != 0) {
                nonzero--;
            }
            if (arr[j] == arr[i] && arr[i] != 0) {
                nonzero--;
            }
            arr[i] = arr[i] - arr[j];
            arr[j] = 0;
        }
        else {
            if (arr[i] != 0) {
                nonzero--;
            }
            if (arr[j] == arr[i] && arr[j] != 0) {
                nonzero--;
            }
            arr[j] = arr[j] - arr[i];
            arr[i] = 0;
        }
    }

    long res = 0;
    for(int i = 0; i < arrsize; i++) {
        if (arr[i] > 0) {
            res = arr[i];
            break;
        }
    }
    printf("KK algorithm residue: %ld\n", res);
    return res;
}

long *rand_sol(int n) {
    long *sol = malloc(sizeof(long)*n);
    for (long i=0; i<n; i++) {
        /* generates random number between 0 and 1 */
        double prob = (double) random() / (double) RAND_MAX;
        if (prob > 0.5) {
            sol[i] = 1;
        }
        else {
            sol[i] = -1;
        }
    }
    return sol;
}


long *rand_neighbor(long *sol) {
    long *sprime= malloc(sizeof(long)*arrsize);
    for (long j=0; j<arrsize; j++) {
            sprime[j] = sol[j];
    }
    if (((double)rand() / (double)RAND_MAX) < 0.5) {
        long j = rand() % (arrsize-1);
        sprime[j] *= -1;
    }
    else {
        long j = rand() % (arrsize-1);
        long k = rand() % (arrsize-1);
        if (k >= j) {
            k++;
        }
        sprime[j] *= -1;
        sprime[k] *= -1;
    }
    return sprime;
}


long *repeated_random(long *arr) {
    long *s = rand_sol(arrsize);

    // print original array
    for (long i=0; i<arrsize; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");

    for(long i=0; i<maxiter; i++) {
        long *sprime = rand_sol(arrsize);

        // // print random solution array
        // for (int j=0; j<arrsize; j++) {
        //     printf("%d ", sprime[j]);
        // }
        // printf("\n");

        if (residue(s, sprime) < residue(arr, s)) {
            // deep copy?
            for(long j=0; j<arrsize; j++) {
                s[j] = sprime[j];
                // free(sprime);
            }
        } 
    }
    printf("repeated random residue: %ld\n", residue(s, arr));
    return s;
}

long *hill_climbing(long *arr) {
    long *s = rand_sol(arrsize);

    for(long i=0; i<maxiter; i++) {
        long *sprime = rand_neighbor(s);

        if (residue(arr, sprime) < residue(arr, s)) {
            // deep copy?
            for(long j=0; j<arrsize; j++) {
                s[j] = sprime[j];
                // free(sprime);
            }
        }
    }
    printf("Hill climbing residue: %ld\n", residue(arr, s));
    return s;
}


long *simulated_annealing(long *arr) {
    long *s = rand_sol(arrsize);
    long *spp = malloc(sizeof(long)*arrsize);
    memcpy(spp, s, arrsize);

    for(long i=0; i<maxiter; i++) {
        long *sp = rand_neighbor(s);
        if (residue(arr, sp) < residue(arr, s)) {
            for(long j=0; j<arrsize; j++) {
                s[j] = sp[j];
                // free(sp);
            }
        }
        else if (((double)rand() / (double)RAND_MAX) < anneal(arr, s, sp, i)){
            for(long j=0; j<arrsize; j++) {
                s[j] = sp[j];
                // free(sp);
            }            
        }

        if (residue(arr, s) < residue(arr, spp)) {
            for(long j=0; j<arrsize; j++) {
                spp[j] = s[j];
                // free(s);
            }            
        }
    }

    printf("simulated annealing residue: %ld\n", residue(arr, spp));
    return spp;
}

int main(void) {
    srand(time(NULL));

    long *arr = generate_random(arrsize);
    kk(arr);
    repeated_random(arr);
    hill_climbing(arr);
    simulated_annealing(arr);
    return 0;
}
