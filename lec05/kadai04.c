#include <stdio.h>
#include <string.h>

void uppercase(char *s);
int main() {
    char s[] = "hello world";
    uppercase(s);
    printf("%s\n",s); // 出力は“HELLO WORLD”
    return 0;
}

void uppercase(char *s)
{
    int len = strlen(s);
    int i;

    for (i = 0; i < len; i++) {
        if (*(s+i) >= 'a' && *(s+i) <= 'z'){
            *(s+i) += 'A'-'a';
        }
    }
    return;
}


