/* #include <iostream> */
/* #include <random> */
#include <stdio.h>
#include <stdlib.h>
#define N 10000000

/* using namespace std; */

/* std::random_device seed_gen; */
/* std::mt19937 engine(seed_gen()); */

unsigned int xorshift();
int random_integer(int);

int main() 
{
    int dian, diaboxn;
    int select[4];
    int dia;
    int i,j, k, d;

    for (k = 0; k < 10; k++) { 
        dian = diaboxn = 0;
        for (i = 0; i < N; i++) {
            d  = 0;
            dia = 1;
            for (j = 0; j < 4; j++ ){
                select[j] = random_integer(52-j);
                if (select[j] <= 12-d) {
                    d++;
                } else if(j >= 1) {
                    break;
                }
                if (j == 3) {
                    dian++;
                    if (select[0] >= 0 && select[0] <= 12 && j == 3) {
                        diaboxn++;
                    }
                }
            }
        }
        printf("%lf\n", (double)diaboxn/(double)dian);
    }
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
    /* return engine(); */
}

int random_integer(int m) 
{
    return xorshift() % m;
}
