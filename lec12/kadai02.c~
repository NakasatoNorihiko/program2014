#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ndsolve(double (*)(double, double), double, double, double);
double RL(double, double);

const double h = 0.001;

int main() 
{
    ndsolve(RL, 0, 0, 10);
    return 0;
}

double RL(double i, double t) 
{
    double R = 1;
    double L = 1;
    double E;
    if (t >= 1 && t <= 2) {
        E = 1;
    } else {
        E = 0;
    }
    double didt = E/L - R/L * i;
    return didt;
}

void ndsolve(double (*f)(double, double), double x0, double t0, double tend)
{
    double t;
    double x = x0;
    
    for (t = t0; t < tend; t += h) {
        x += h * f(x,t);
        printf("%lf\t%lf\n", t, x);
    }
}
