#include <stdio.h>
#include <math.h>
#define R_MAX 100000
#define N 10000

int random_integer(int);
int xorshift();
int disjoint(int, int);

int main()
{
    double prob = 0;
    double pi;
    int u1, u2;
    int i, j;

    for (i = 0; i < N; i++) {
        u1 = random_integer(R_MAX);
        u2 = random_integer(R_MAX);
        if (disjoint(u1, u2) == 1) {
            prob++;
        }
    }
    prob /= N;
    
    pi = pow(6/prob, 0.5);
    printf("%lf\n", pi);
    return 0;
    
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

int random_integer(int m) 
{
    return xorshift() % m;
}

int disjoint(int a, int b)
{
    int i;
    int minor = a;
    if (a > b) {
        minor = b;
    } 
    for (i = 2; i < minor/2+1; i++){
        if (a % i == 0) {
            if (b % i == 0) {
                return 0;
            }
        }
    }
    return 1;
}

    
