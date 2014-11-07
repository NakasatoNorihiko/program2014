#include <stdio.h>
#include <string.h>

int roman2num(char*);
int main() 
{
    printf("XIV = %d\n", roman2num("XIV")); //14
    printf("CDXCV = %d\n", roman2num("CDXCV")); //495
    printf("MCMXLV = %d\n", roman2num("MCMXLV")); //1945
    printf("MMMCMXCIX = %d\n", roman2num("MMMCMXCIX")); //3999
    return 0;
}

int roman2num(char *s) 
{
    int len = strlen(s);
    int sum = 0;
    int nnum, pnum;             /* nnumは新しく読み取ったローマ数字の数、pnumは一つ前のローマ数字の数 */
    int i;

    pnum = 0;
    for (i = len-1; i >= 0; i--) {
        switch (s[i]) {
        case 'M':
            nnum = 1000;
            break;
        case 'D':
            nnum = 500;
            break;
        case 'C':
            nnum = 100;
            break;
        case 'L':
            nnum = 50;
            break;
        case 'X':
            nnum = 10;
            break;
        case 'V':
            nnum = 5;
            break;
        case 'I':
            nnum = 1;
            break;
        default:
            return -1;
        }
        if (nnum < pnum) {
            sum -= nnum;
        } else {
            sum += nnum;
        }
        pnum = nnum;
    }
    return sum;
}


