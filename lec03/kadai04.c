#include <stdio.h>
#include <math.h>

double f(double);
double dfdx(double);
double newton(double);

int main() {
    double x0 = 1.0;
    double solution = newton(x0);
    printf("solution is %f\n", solution);
    return 0;
}

double f(double x)
{
    return exp(x) + x;
}

double dfdx(double x)
{
    return exp(x) + 1;
}

double newton(double xn)
{
    const double e = 0.000001;     /* 停止条件 */
    double xnp1 = xn - f(xn) / dfdx(xn);
    if (fabs(xnp1 - xn) < e) {
        return xnp1;
    } else {
        return newton(xnp1);
    }
}

