#include <iostream>
#include <random>
#include <stdio.h>
#define N 1000000

using namespace std;

std::random_device seed_gen;
std::mt19937 engine(seed_gen());

unsigned int xorshift();
int random_integer(int);
int random_ex_integer(int m, int ex[], int exn);


/*
engine()

*/
int main() 
{
    int dian, diaboxn;
    int select[4];
    int dia;
    int i,j, k;
    dian = diaboxn = 0;

    for (k = 0; k < 10; k++) {
        for (i = 0; i < N; i++) {
            dia = 1;
            for (j = 0; j < 4; j++ ){
                select[j] = random_ex_integer(52, select, j);
                if (select[j] > 12 && j >= 1) {
                    dia = 0;
                }
            }
            if (dia == 1) {
                dian++;
                if (select[0] >= 0 && select[0] <= 12) {
                    diaboxn++;
                }
            }
        }
        printf("%lf\n", (double)diaboxn/dian);
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
    //return w = (w^ (w>>19)) ^ (t ^ (t >> 8));
    return engine();
    
}

int random_integer(int m) 
{
    return xorshift() % m;
}

int random_ex_integer(int m, int ex[], int exn)
{
    int ret = xorshift() % (m-exn);
    int i;

    for (i = 0; i < exn; i++) {
        if (ret >= ex[i]) {
            ret++;
        }
    }
    return ret;
}
