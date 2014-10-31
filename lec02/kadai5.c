#include <stdio.h>

// 先頭の単語の中にいる場合1, それ以外0
#define FIRST 1
#define NOFIRST 0

int main()
{
    int c, state;
    
    state = FIRST;
    while((c = getchar()) != EOF) {
        if (state == FIRST) {
            if (c == ' ') {
                state = NOFIRST;
            } else {
                putchar(c);
            }
        } else {
            if (c == '\n') {
                state = FIRST;
            }
        }
    }
    return 0;
}
