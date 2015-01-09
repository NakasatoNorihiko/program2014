#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000             /* 項数の最大*/

char**  s_strcut(char *ori, char *cut, int *datalen, char *); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
int s_strlen(char *);
void s_strcpy(char *, char *);

/* 単項式の定義 */
typedef struct Monomial_tag
{
  int c;
  int n;
} Monomial;

/* 単項式をつくる関数 */
Monomial* construct_monomial(int c, int n)
{
  Monomial *ret = (Monomial*)malloc(sizeof(Monomial));
  ret->c = c;
  ret->n = n;
  return ret;
}

/* a*x^b　の形式の文字列を Monomial*形式に進化 */
Monomial* transform_to_monomial(char *string)
{
  char cut[] = "*^";
  char cutsymbol[MAXLEN];
  char **buffer = s_strcut(string, cut, NULL, cutsymbol);
  Monomial *ret;
  if (cutsymbol[1] == '*' && cutsymbol[2] == '^') {
    ret = construct_monomial(atoi(buffer[0]), atoi(buffer[2]));
  } else if (cutsymbol[1] == '^') {
    ret = construct_monomial(1,atoi(buffer[1]));
  } else if (cutsymbol[1] == '*') {
    ret = construct_monomial(atoi(buffer[0]),1);
  } else if (strcmp(buffer[0],"x")== 0) {
    ret = construct_monomial(1,1);
  } else {
    ret = construct_monomial(atoi(buffer[0]),0);
  }
  free(buffer);
  return ret;
}

/* a*x^b+c*x^d　形式の文字列をmono**形式に変更 */
Monomial** transform_to_polynomial(char *string, int *n)
{
  char cut[] = "+-";
  int len, i;
  char cutsymbol[MAXLEN];
  char **buffer = s_strcut(string, cut, &len, cutsymbol);
  Monomial **ret = (Monomial **)malloc(sizeof(Monomial *)*len);
  for (i = 0; i < len; i++) {
    ret[i] = transform_to_monomial(buffer[i]);
    if (cutsymbol[i] == '-') {
      ret[i]->c *= -1;
    }
  }
  *n = len;
  return ret;
}

/* 単項式を微分する関数 */
void diff_monomial(Monomial *m) 
{
  if (m->n != 0) {
    m->c = (m->n)*(m->c);
    m->n = m->n - 1;
  } else {
    m->c = 0;
    m->n = 0;
  }
}

void print_monomial(Monomial *m)
{
  if (m->n != 0 && m->n != 1) { 
    printf("%+d*x^%d", m->c, m->n);
  } else if (m->n == 1) {
    printf("%+d*x", m->c);
  } else if (m->n == 0 && m->c != 0) {
    printf("%+d", m->c);
  }    
}

/* 多項式を微分する関数 */
void diff_polynomial(Monomial **m, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    diff_monomial(m[i]);
  }
}

void print_polynomial(Monomial **m, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    print_monomial(m[i]);
  }
}

int main(int argc, char *argv[])
{
  int n;
  Monomial **m1 = transform_to_polynomial(argv[1], &n);

  diff_polynomial(m1, n);
  printf("\nDiff: ");
  print_polynomial(m1, n);
  
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
            
/* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す *cutsymbol　に何で切られたのかを書く*/
char** s_strcut(char *ori, char *cut, int *datalen, char cutsymbol[MAXLEN]) {
  int i, j; 
  char **data;
  int orilen = s_strlen(ori);
  int cutn = s_strlen(cut);
  int len;
  int string_length[MAXLEN];
  int firstsymbol = 0;              /* 最初に-+が来るか */
  char *tmp;

  if (cutsymbol != NULL) memset(cutsymbol, '\0', MAXLEN);

  len = 1;/* 何個に分割されるかを示す */
  memset(string_length, 0, MAXLEN);
  for(i = 0; i < orilen; i++) {
    for (j = 0; j < cutn; j++) {
      if (ori[i] == cut[j]) { /* 区切り文字ににあたった時 */
        if (i == 0) firstsymbol = 1;
        if (cutsymbol != NULL) {
          if (firstsymbol) {
            cutsymbol[len-1] = ori[i];
          } else {
            cutsymbol[len] = ori[i];
          }
        }
        len++;
      } else {            /* 区切り文字でないとき */
        string_length[len-1]++;
      }
    }
  }
    
  data = (char **)malloc(sizeof(char*)*len);
  data[0] = (char*)malloc(sizeof(char) * (string_length[0]+1));
  data[0] = strtok(ori, cut);
    
  for (i = 1; (tmp = strtok(NULL, cut)) != NULL; i++) {
    data[i] = (char*)malloc(sizeof(char) * (string_length[i]+1));
    data[i] = tmp;
  }
  if (datalen != NULL) *datalen = len;

  return data;
}

