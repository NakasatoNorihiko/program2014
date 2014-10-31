#include <stdio.h>

int gcd(int a, int b) 
{
    int tmp;
    
    while (b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main() 
{
    int n, m, div;

    for (n = 1; n <= 100; n++) {
        for (m = 1; m <= 100; m++) {
            printf("%d / %d = ", n, m);
            div = gcd(m,n);
            if (m/div == 1) {
                printf("%d\n", n/div);
            } else {
                printf("%d / %d\n", n/div, m/div);
            }
        }
    }
    return 0;
}
    
