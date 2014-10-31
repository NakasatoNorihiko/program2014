#include <stdio.h>
#include <math.h>

void primelist(int[], int);

int main()
{
    const int max = 6;          /* 10^maxまでの素数を調べる */
    int len = pow(10,max);
    int prime[len];
    int pi = 0;
    int i,j, n;
   
    primelist(prime, len);

    for (i = 1; i <= max; i++) {
        n = pow(10,i);
        pi = 0;
        for (j = 0; j < n; j++) {
            pi += prime[j];
        }
        printf("n = %7d pi(n) = %5d pi(n)/(n/log(n)) = %lf\n", n, pi, (double)pi / ((double)n / log(n)));
    }
    

    return 0;
}

void primelist(int list[], int len)
{
    int sqr = sqrt(len);
    int i, j;
    for(i = 1; i < len; i++) {
        list[i] = 1;
    }

    /* 検査数の分だけふるい落としていく */
    for (i = 2; i <= sqr; i++) {
        if (list[i-1]) {
            for (j = i*2; j <= len; j += i) {
                list[j-1] = 0;
            }
        }
    }
    return;
}


