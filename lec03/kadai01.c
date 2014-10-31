#include <stdio.h>
#include <math.h>

int is_prime(int);

int main()
{
    int i;
    for (i = 2; i <= 1000; i++) {
        if (is_prime(i) == 1) {
            printf("%d is prime\n", i);
        }
    }
    return 0;
}

int is_prime(int n) 
{
    int sqr = sqrt(n);
    int i;

    if ((n % 2) == 0 && n != 2) {
        return 0;
    }
    for (i = 3; i <= sqr; i += 2) {
        if ((n % i) == 0) {
            return 0;
        }
    }
    return 1;
}
