#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ndsolve(double (**f)(double*, double), double* x0, double t0, double tend, int N);

const double h  = 0.1;
const double c1 = 0.15;
const double c2 = 0.2;
const double c3 = 7.1;

double rosseler_0(double *x, double t) 
{
    return -x[1] - x[2];
}
double rosseler_1(double *x, double t) 
{
    return x[0] + c1 * x[1];
}
double rosseler_2(double *x, double t) 
{
    return c2 + x[2]*(x[0]-c3);
}

int main() 
{
    double (*rosseler[])(double*, double) = {rosseler_0, rosseler_1, rosseler_2};
    double x0[] = {0, 0, 0};
    ndsolve(rosseler, x0, 0, 1000, 3);
    return 0;
}

void ndsolve(double (**f)(double*, double), double* x0, double t0, double tend, int N)
{
    double t;
    int i;
    double *x    = (double*)malloc(sizeof(double)*N);;
    double *tmpx = (double*)malloc(sizeof(double)*N);
    
    for (t = t0; t < tend; t += h) {
        for (i = 0; i < N; i++) {
            tmpx[i] = x[i] + h * f[i](x, t);
        }
        for (i = 0; i < N; i++) {
            x[i] = tmpx[i];
        }
        printf("%lf", t);
        for (i = 0; i < N; i++) {
            printf("\t%lf", x[i]);
        }
        printf("\n");
    }
}
