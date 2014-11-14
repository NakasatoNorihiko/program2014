#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    int sum = 0;
    int n = atoi(argv[1]);
    for (i = 1; i <= n; i++){
        sum += i;
    }
    printf("%d\n", sum);
    return 0;
}
