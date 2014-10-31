#include <stdio.h>
#include <math.h>

void primelist(int[], int);

int main() 
{
    const int max = 1000;
    int prime[max];             /* iが素数のときprime[i-1]=1,素数でないときprime[i-1]=0 */
    int i,j;

    primelist(prime, max);
    
    for (i = 4; i <= max; i += 2) {
        for (j = 2; j <= (i+1)/2; j++) {
            if(prime[j-1] && prime[i-j-1]) {
                printf("%d = %d + %d\n", i, j, i-j);
            }
        }
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

