#include <stdio.h>

int main() 
{
    int i,n;

    for (i = 1; i <= 100; i++) {
        n = i;
        printf("%d", n);
        while (n != 1) {
            if ((n % 2) == 0) {
                n /= 2;
            } else {
                n = n * 3 + 1;
            }
            printf(" -> %d", n);
        }
        printf("\n");
    }
    printf("Done!\n");
    return 0;
}
        
