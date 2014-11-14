#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) 
{
    double **A, **B, **C;
    char tmp[10];
    int i, j, k;
    int row[2], column[2];            /* 行の数、列の数 */
    int m, n;

    for (i = 0; i < 2; i++){
        row[i] = column[i] = 0;
    }
    
    for (i = 0; i < 2; i++) {
        j = 0;
        while(argv[i+1][j] != '\0') {
            if (argv[i+1][j] == ',') {
                column[i]++;
            } else if (argv[i+1][j] == ':') {
                row[i]++;
            }
            j++;
        }
        column[i] = (column[i] / 2) + 1;
    }

    A = (double**)malloc(sizeof(double*)*row[0]);
    for (i = 0; i < row[0]; i++) {
        A[i] = (double*)malloc(sizeof(double)*column[0]);
    }
    B = (double**)malloc(sizeof(double*)*row[1]);
    for (i = 0; i < row[1]; i++) {
        B[i] = (double*)malloc(sizeof(double)*column[1]);
    }
    C = (double**)malloc(sizeof(double*)*row[0]);
    for (i = 0; i < row[0]; i++) {
        C[i] = (double*)malloc(sizeof(double)*column[1]);
    }
    

    k = 0;
    
    for (i = 0; i < 2; i++) {
        m = n = 0;
        j = 0;
        while(argv[i+1][j] != '\0') {
            while(argv[i+1][j] != ',' && argv[i+1][j] != ':') {
                tmp[k] = argv[i+1][j];
                j++;
                k++;
            }
            tmp[k] = '\0';
            if (i == 0) {
                A[m][n] = atof(tmp);
            } else {
                B[m][n] = atof(tmp);
            }
            if (argv[i+1][j] == ',') {
                n++;
            } else if (argv[i+1][j] == ':') {
                m++;
                n = 0;
            }
            k = 0;
            j++;
            strcpy(tmp, "");
        }
    }

    for (m = 0; m < row[0]; m++) {
        for (k = 0; k < column[1]; k++) {
            C[m][k] = 0;
        }
    }
    for (m = 0; m < row[0]; m++) {
        for (n = 0; n < column[0]; n++) {
            for (k = 0; k < column[1]; k++) {
                C[m][k] += A[m][n] * B[n][k];
            }
        }
    }
    
    for (i = 0; i < 2; i++) {
        for (m = 0; m < row[i]; m++) {
            for (n = 0; n < column[i]; n++) {
                if (i == 0) {
                    printf("%lf ", A[m][n]);
                } else {
                    printf("%lf ", B[m][n]);
                }
            }
            printf("\n");
        }
    }
    for (m = 0; m < row[0]; m++) {
        for (k = 0; k < column[1]; k++) {
            printf("%lf ", C[m][k]);
        }
        printf("\n");
    }
    

    return 0;
}


