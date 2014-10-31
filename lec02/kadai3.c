#include <stdio.h>

int main()
{
    int n, i;
    long long ans;
    
    for (n = 0; n <= 20; n++) {
        ans = 1;
        for (i = 0; i < n; i++) {
            ans *= i+1;
        }
        printf("%2d %lld\n", n, ans);
    }
    return 0;
}
