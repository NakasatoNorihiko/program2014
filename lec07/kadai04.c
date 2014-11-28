#include <stdio.h>
#include <math.h>
#define N 1000
#define MAX 10000

int random_integer(int);

int main()
{
    int x[MAX];
    int i, j;
    double ave, var, kur;
    ave = var = kur = 0;
    
    for (i = 0; i < MAX; i++){
        x[i] = 0;
    }

    for (i = 0; i < MAX; i++) {
        for (j = 0; j < N; j++) {
            if (random_integer(2)) {
                x[i]++;
            } else {
                x[i]--;
            }
        }
        ave += x[i];
    }

    ave /= MAX;
    for (i = 0; i < MAX; i++) {
        var += pow(x[i] - ave, 2);
        kur += pow(x[i] - ave, 4);
    }
    
    var /= MAX;
    kur /= MAX * pow(var,2);

    printf("N:%d\naverage:%lf\nvariable:%lf\nkutosis:%lf\n", N,ave, var, kur);
    
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
