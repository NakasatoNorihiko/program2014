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
    int r;
    int a = 8733;
    int b = 64681;
    r = gcd(a,b);
    printf("gcd(%d, %d) = %d\n", a, b, r);
    return 0;
}
