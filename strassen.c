#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define dim 2


// matrix structure
struct Matrix {
    int rows;
    int cols;
    int ** mpointer;
} matrix;


// helper function to sum matrices
void sum(double ** x, double ** y int n, double ** z) {
	for(int i=0; i<n; i++) {
		for (int j=0; i<n; j++)
			// FIX: should this be changed to return a matrix?
			z[i][j] = x[i][j] + y[i][j];
	}
}


// helper function to subtract matrices
void difference(double ** a, double ** b, int n, double ** c) {
	for(int i=0; i<n; i++) {
		for (int j=0; i<n; j++)
            // FIX: should this be changed to return a matrix?
            z[i][j] = x[i][j] - y[i][j];
	}
}


// TODO: HELPER FUNCTION TO ALLOCATE MEMORY



// TODO: HELPER FUNCTION TO FREE MEMORY



// Strassen multiplication method
void rec multiply(int ** x, int ** y, int n, int ** z) {
    
    /* Base case */    

    // TODO: modify so we can switch back to regular multiplication at a certain point   
    if (dim==1) {
    	c[0][0] = a[0][0]*b[0][0];
    	return;
    }

    else {
    	
        /* Half the dimension and use it to construct submatrices of X and Y */

        // new dimension
    	int n = dim/2;
    	
    	// TODO: figure out a way to pad submatrices with zeros if dim is not even


        int ** a, ** b, ** c, ** d, ** e, ** f, ** g, ** h, ** p, ** q, ** r, ** s; 
        
        // TODO: allocate memory

    	// divide matrices into 4 parts and define their indices
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                
                // submatrices of x
                a[i][j] = x[i][j];          // top left
                b[i][j] = x[i][n+j];        // top right
                c[i][j] = x[n+i][j];        // bottom left
                d[i][j] = x[n+i][n+j];      // bottom right

                // submatrices of y
                e[i][j] = y[i][j];          // top left
                f[i][j] = y[i][n+j];        // top right
                g[i][j] = y[n+i][j];        // bottom left
                h[i][j] = y[n+i][n+j];      // bottom right
            }
        }


        /* Use the submatrices of X and Y to construct helper matrices P1 through P7 */

        int ** helper1, ** helper2, ** helper3;
        int ** p1, ** p2, ** p3, ** p4, ** p5, ** p6, ** p7;
        
        // TODO: allocate memory
    
        // P1
        difference(f, h, n, helper2);
        multiply(a, helper2, n, p1);

        // P2
        sum(a, b, n, helper1);
        multiply(helper1, h, n, p2);

        // P3
        sum(c, d, n, helper1);
        multiply(helper1, e, n, p3);

        // P4
        difference(g, e, n, helper2);
        multiply(d, helper2, n, p4);

        // P5
        sum(a, d, n, helper1);
        sum(e, h, n, helper2);
        multiply(helper1, helper2, n, p5);

        // P6
        s1 = difference(b, d, n, helper1);
        s2 = sum(g, h, n, helper2);
        multiply(helper1, helper2, n, p6);

        // P7
        s1 = difference(a, c, n, helper1);
        s2 = sum(e, f, n, helper2);
        multiply(helper1, helper2, n, p7);

        
        /* Use P1 through P7 to define the indices of our resultant Z matrix */

        // top left submatrix
        sum(p5, p4, n, helper1);
        sum(p2, p6, n, helper2);
        difference(helper1, helper2, n, p);
        
        // top right submatrix
        sum(p1, p2, n, q);
        
        // bottom left submatrix
        sum(p3, p4, n, r);

        // bottom right submatrix
        sum(p5, p1, n, helper1);
        difference(p3, p7, n, helper2);
        difference(helper1, helper2, n, s);

        // consolidate submatrices in Z
        for(i=0; i<n; i++)
            for(j=0; j<n; j++)
                {
                    z[i][j] = p[i][j];
                    z[i][n+j] = q[i][j];
                    z[n+i][j] = r[i][j];
                    z[n+i][j+i] = s[i][j];               
                }
    }

}


int main () {

    /* THIS SHOULD USE OUR STRUCT AND POINTERS INSTEAD OF ARRAYS, NEED TO FIX */

	// initializing matrices
	int x[dim][dim];
    int y[dim][dim];
    int z[dim][dim];
    int i, j;


    // populate a and b with random numbers
    srand(time(NULL));
    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++) {
            int r1 = rand() % 10;
            int r2 = rand() % 10;
            x[i][j] = r1;
            y[i][j] = r2;
        }
    }


    // initialize z to be all zeros
    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++) {
            z[i][j] = 0;
        }
    }

    multiply(x, y, dim, z)

}