#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void inverse(double **A);
void swap(double *, double *);

int main(int argc, char *argv[])
{
    double *mat[2];
    int i, j;

    for (i = 0; i < 2; i++) {
        mat[i] = (double *)malloc(sizeof(double));
    }
    
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            mat[i][j] = atof(argv[2*i+j+1]);
        }
    }
    inverse(mat);
    printf("[%lf %lf][%lf %lf]\n", mat[0][0], mat[0][1], mat[1][0], mat[1][1]);
    
    return 0;
}

void inverse(double **A)
{
    double det = A[0][0]*A[1][1] - A[0][1]*A[1][0];
    int i,j;
    
    swap(&A[0][0], &A[1][1]);
    A[0][1] *= -1;
    A[1][0] *= -1;
    for (i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            A[i][j] /= det;
        }
    }
    return;
}

void swap(double *a, double *b)
{
    double tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
