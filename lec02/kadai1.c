#include <stdio.h>

int main()
{
    int n;
    
    for (n = 1; n <= 20; n++) {
        printf("%2d %lf\n", n, 1.0/(double)n);
    }
    return 0;
}
