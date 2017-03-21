#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10

typedef struct Matrix {
  int rows;
  int cols;
  double ** mpointer;
} matrix;

int main()
{
    // REGULAR MULTIPLICATION ALGORITHM

    // NEED TO MODIFY SO IT USES OUR STRUCT AND POINTERS INSTEAD OF ARRAYS

    // initializing matrices
    int a[n][n];
    int b[n][n];
    int c[n][n];
    int i, j, k;

    // populate a and b with random numbers
    srand(time(NULL));
    for(i=0; i<n; i++){
        for(j=0; j<n; j++) {
            int r1 = rand() % 10;
            int r2 = rand() % 10;
            a[i][j] = r1;
            b[i][j] = r2;
        }
    }

    // initialize c to be all zeros
    for(i=0; i<n; i++){
        for(j=0; j<n; j++) {
            c[i][j] = 0;
        }
    }

    // multiplication step
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            for(k=0; k<n; k++)
            {
                c[i][k]+=a[i][j]*b[j][k];
            }

    // print matrix A
    printf("\nMatrix A:\n");
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
        {
            printf("%d  ", a[i][j]);
            if(j == n-1)
                printf("\n\n");
        }

    // print matrix B
    printf("\nMatrix B:\n");
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
        {
            printf("%d  ", b[i][j]);
            if(j == n-1)
                printf("\n\n");
        }

    // print resultant matrix
    printf("\nResulting Matrix:\n");
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
        {
            printf("%d  ", c[i][j]);
            if(j == n-1)
                printf("\n\n");
        }

    return 0;
}