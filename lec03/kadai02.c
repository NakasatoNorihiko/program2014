#include <stdio.h>
#include <math.h>

int is_prime(int);

int main()
{
    double epro = 1;            /*  オイラー積 */
    double pi;
    int i;
    const int max = 10000;
    
    for (i = 2; i <= max; i++) {
        if (is_prime(i)) {
            epro *= 1 - 1 / ((double) i*i);
        }
    }
    pi = sqrt(6 / epro);

    printf("pi = %lf\n", pi);

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

