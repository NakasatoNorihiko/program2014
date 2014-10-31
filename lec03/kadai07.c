#include <stdio.h>
#include <math.h>

double bisection(double xn, double xp);
double f(double x);
    
int main()
{
    double xn, xp, ans;
    xn = 1.0;
    xp = 2.0;

    ans = bisection(xn,xp);
    printf("%lf\n", ans);

    return 0;
}


double bisection(double xn, double xp)
{
    double xm,e;
    e = 0.000001;
    
    xm = 0.5 * (xn + xp);
    if (f(xm) < 0) {
        xn = xm;
    } else {
        xp = xm;
    }
    if (fabs(xp - xn) < e) {
        return xp;
    } else {
        return bisection(xn, xp);
    }
}

double f(double x)
{
    return x*x - 2;
}
