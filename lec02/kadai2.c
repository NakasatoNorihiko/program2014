#include <stdio.h>

int main()
{
    int n, ans, i;
    
    for (n = 0; n <= 20; n++) {
        ans = 1;
        for (i = 0; i < n; i++) {
            ans *= 2;
        }
        printf("%2d %d\n", n, ans);
    }
    return 0;
}
