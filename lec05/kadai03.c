#include <stdio.h>
#include <string.h>

void reverse(char *s);
int main() {
    char s[] = "hello";
    reverse(s);
    printf("%s\n",s); // 出力は“olleh” return 0;

    return 0;
}

void reverse(char *s)
{
    int len = strlen(s);                    /* *sの長さを格納する変数 */
    int i;
    char tmp;

    for (i = 0; i < len/2; i++) {
        tmp = *(s+i);
        *(s+i) = *(s+len-i-1);
        *(s+len-i-1) = tmp;
    }
}
