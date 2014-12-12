#include <stdio.h>
#include <stdlib.h>

#define CUTIN 1
#define CUTOUT 0

char**  s_strcut(char *ori, char *cut, int *datalen, int inccut); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
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
  char cut[] = "*^";
  int len;
  char **buffer = s_strcut(string, cut, &len, CUTOUT);
  mono *ret = construct_monomial(atoi(buffer[0]), atoi(buffer[2]));
  return ret;
}

/* a*x^b+c*x^d　形式の文字列をmono**形式に変更 */
mono** transform_to_polynomial(char *string, int *n)
{
  char cut[] = "+-";
  int len, i;
  char **buffer = s_strcut(string, cut, &len, CUTIN);
  mono **ret = (mono **)malloc(sizeof(mono *)*len);
  for (i = 0; i < len; i++) {
    ret[i] = transform_to_monomial(buffer[i]);
  }
  *n = len;
  return ret;
}

/* 単項式を微分する関数 */
void diff_monomial(mono *m) 
{
  m->c = (m->n)*(m->c);
  m->n = m->n - 1;
}

/* 多項式を微分する関数 */
void diff_polynomial(mono **m, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    diff_monomial(m[i]);
  }
}

void print_monomial(mono *m)
{
  printf("%+d*x^%d", m->c, m->n);
}

void print_polynomial(mono **m, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    print_monomial(m[i]);
  }
}

int main(int argc, char *argv[])
{
  int n;
  mono **m1 = transform_to_polynomial(argv[1], &n);

  print_polynomial(m1, n);
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
            
/* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す*/
/* inccut = 0ならcutを出力に含まない inccut = 1なら出力に含む */
char** s_strcut(char *ori, char *cut, int *datalen, int inccut) {
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
      if (ori[i] == cut[j] && i != 0) {
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
      } else if (ori[i] == cut[j] && i != 0) {
        state = 1;
      }
    }
    if (state == 1 && i != 0){
      tmp[k] = '\0';
      data[n] = (char*)malloc(sizeof(char) * (k+1));
      s_strcpy(data[n], tmp);
      if (inccut == CUTOUT) {
        k = 0;
      } else if (inccut == CUTIN){
        tmp[0] = ori[i];
        k = 1;
      }
      n++;
    } else {
      tmp[k] = ori[i];
      k++;
    }
  }
  return data;
}
