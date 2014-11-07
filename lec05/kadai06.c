#include <stdio.h>
#include <string.h>

void num2roman(int, char[]);
void nnum2roman(int quo, char*, char *one, char *five, char *ten);

int main() 
{
    char roman[20];

    num2roman(14, roman);
    printf("14 = %s\n", roman); //XIV
    num2roman(495, roman);
    printf("495 = %s\n", roman); //CDXCV
    num2roman(1945, roman);
    printf("1945 = %s\n", roman); //MCMXLV
    num2roman(3999, roman);
    printf("3999 = %s\n", roman); //MMMCMXCIX
    
    return 0;
}

void num2roman(int argn, char roman[])
{
    int n = argn;               /* 引数は残しておく */
    int quo;
    int i;

    strcpy(roman, "");

    quo = n / 1000;
    n %= 1000;
    for (i = quo; i > 0; i--) {
        strcat(roman, "M");
    }

    nnum2roman(n/100, roman, "C", "D", "M");
    n %= 100;

    nnum2roman(n/10, roman, "X", "L", "C");
    n %= 10;

    nnum2roman(n, roman, "I", "V", "X");
}

/* n桁目だけローマ数字に変換する */
/* quo: 10^(n-1)で割ったときの商, char: ローマ数字を出力するためのポインタ　one: 10^(n-1)を表す文字, five: 5*10^(n-1)を表す文字, ten: 10*10^(n-1)を表す文字 */
/* 例 n=2のとき quo 10で割ったときの商, one: 10 = X, five: 50 -> L, ten 100 -> C */
void nnum2roman(int quo, char *roman, char *one, char *five, char *ten)
{
    int i;
    
    if (quo == 4) {
        strcat(roman, one);
        strcat(roman, five);
    } else if (quo == 9) {
        strcat(roman, one);
        strcat(roman, ten);
    } else {
        if (quo / 5 > 0) {
            strcat(roman, five);
        } 
        for (i = quo%5; i > 0; i--) {
            strcat(roman, one);
        }
    }
}


