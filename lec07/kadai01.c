#include <stdio.h>
#include <math.h>

unsigned int xorshift();
int random_integer(int);
double random_double();
double random_normal();

int main() 
{
    int i;
    
    for (i = 0; i < 100; i++) {
        printf("%lf\n", random_normal());
    }
    return 0;
}

int random_integer(int m) 
{
    return xorshift() % m;
}

double random_double() 
{
    return (double)xorshift() / 4294967295;
}

double random_normal()
{
    double u1 = random_double();
    double u2 = random_double();

    while (u1 == 0 || u2 == 0) {
        if (u1 == 0){
            u1 = random_double();
        }
        if (u2 == 0) {
            u2 = random_double();
        }
    }
    
    return (pow(-2*log(u1),0.5)*cos(2*M_PI*u2));
}

unsigned int xorshift() 
{
    static unsigned int x = 1;
    static unsigned int y = 2;
    static unsigned int z = 3;
    static unsigned int w = 4;
    unsigned int t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w^ (w>>19)) ^ (t ^ (t >> 8));
}
