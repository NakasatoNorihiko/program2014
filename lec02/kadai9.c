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
    int a, b, c;

    for (c = 1; c <= 100; c++) {
        for (b = 1; b <= c; b++) {
            for (a = 1; a <= b; a++) {
                if (gcd(a,b) == 1) {
                    if ((a*a) + (b*b) == (c*c)) {
                        printf("%2d^2 + %2d^2 =  %2d^2\n", a, b, c);
                    }
                }
            }
        }
    }
    return 0;
}

