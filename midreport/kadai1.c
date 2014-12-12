#include <stdio.h>
#include <stdlib.h>

char**  s_strcut(char *ori, char *cut, int *datalen); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
int s_strlen(char *);
void s_strcpy(char *, char *);

/* 単項式の定義 */
typedef struct monomial 
{
    int c;
    int n;
} mono;

/* 単項式をつくる関数 */
mono* construct_monomial(int c, int n)
{
    mono *ret = (mono*)malloc(sizeof(mono));
    ret->c = c;
    ret->n = n;
    return ret;
}

/* a*x^b　の形式の文字列を mono*形式に進化 */
mono* transform_to_monomial(char *string)
{
  char cut[] = {'*', '^'};
  int len;
  char **buffer;
  buffer = s_strcut(string, cut, &len);
  mono *ret = construct_monomial(atoi(buffer[0]), atoi(buffer[2]));
  return ret;
}

/* 単項式を微分する関数 */
void diff_monomial(mono *m) 
{
    m->c = (m->n)*(m->c);
    m->n = m->n - 1;
}

void print_monomial(mono *m)
{
    printf("%d*x^%d\n", m->c, m->n);
}

int main(int argc, char *argv[])
{
  mono *m1 = transform_to_monomial(argv[1]);

  printf("Diff: ");
  diff_monomial(m1);
  print_monomial(m1);

  return 0;
}

int s_strlen(char *str)
{
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}

void s_strcpy(char *str1, char *str2)
{
    int len;
    int i;
    len = s_strlen(str2);
    for (i = 0; i <= len; i++) {
        str1[i] = str2[i];
    }
    return;
}
            
/* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す */
char** s_strcut(char *ori, char *cut, int *datalen) {
    int i, j, k, n;
    char **data;
    int orilen = s_strlen(ori);
    int cutn = s_strlen(cut);
    char tmp[1000];
    int state;

    *datalen = 1;                  /* 何個に分割されるかを示す */
    n = 0;
    for(i = 0; i < orilen; i++) {
        for (j = 0; j < cutn; j++) {
            if (ori[i] == cut[j]) {
                (*datalen)++;
            }
        }
    }
    data = (char **)malloc(sizeof(char*)*(*datalen));

    k = 0;
    for (i = 0; i <= orilen; i++) {
        state = 0;
        for (j = 0; j < cutn; j++) {
            if (ori[i] == '\0') {
                state = 1;
            } else if (ori[i] == cut[j]) {
                state = 1;
            }
        }
        if (state == 1){
            tmp[k] = '\0';
            data[n] = (char*)malloc(sizeof(char) * (k+1));
            s_strcpy(data[n], tmp);
            k = 0;
            n++;
        } else {
            tmp[k] = ori[i];
            k++;
        }
    }

    return data;
}
