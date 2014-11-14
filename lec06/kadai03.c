#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char *pol;
    char **mon;
    char tmp[20];
    /* int state = 1;              /\* 0なら単項式の外 *\/ */
    
    int i,j,k,n;                  /* nは単項式の数 */
    int len = 0;                      /* 全体の長さ */
    i = j = n = 0;
    strcpy(tmp, "");

    while(argv[1][len] != '\0') {
        len++;
    }
    mon = (char **)malloc(sizeof(char*) * (len+1));
    
    i = 0;
    for (i = 0; i <= len; i++) {
        if (argv[1][i] != '+' && argv[1][i] != '-' && argv[1][i] != '\0') {
            tmp[j] = argv[1][i];
            j++;
        } else {
            tmp[j] = '\0';
            mon[n] = (char *)malloc(sizeof(char) * (j+1));
            for (k = 0; k < j+2; k++) {
                mon[n][k] = tmp[k];
            }
            j = 0;
            if (argv[1][i] == '-') {
                tmp[j] = argv[1][i];
                j++;
            }
            n++;
        }
    }
    printf("Polynomial = %s\n", argv[1]);
    for (i = 0; i < n; i++) {
        printf("Monomial %d = %s\n", i+1, mon[i]);
    }
    return 0;
}
