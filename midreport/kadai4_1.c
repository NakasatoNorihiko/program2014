/* 多項式の加算、減算、乗算を定義する */
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

/* 多項式の定義 */
typedef struct Polynomial_tag
{
  Monomial **mono;               /* 単項式の配列　*mono[0]が0次項、*mono[1]が1次項を表す */
  int n;                        /* 最大次数 */
} Polynomial;

/* a*x^b　の形式の文字列を Monomial*形式に変換 */
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

/* 多項式を初期化 */
Polynomial* initialize_polynomial(int n)
{
  int i;
  Polynomial* ret = (Polynomial*)malloc(sizeof(Polynomial));
  ret->mono = (Monomial**)malloc(sizeof(Monomial*)*(n+1));
  ret->n = n;
  for (i = 0; i <= n; i++) {
    ret->mono[i] = (Monomial*)malloc(sizeof(Monomial));
    ret->mono[i]->c = 0;
    ret->mono[i]->n = i;
  }
  return ret;
}

void copy_polynomial(Polynomial *p1, Polynomial *p2)
{
  int i;
  if (p2->n <= p1->n) {
    p1->n = p2->n;
    for (i = 0; i <= p2->n; i++) {
      p1->mono[i]->c = p2->mono[i]->c;
    }
    for (i = p2->n + 1; i <= p1->n; i++) {
      p1->mono[i]->c = 0;
    }
  } else {
    for (i = 0; i <= p1->n; i++) {
      p1->mono[i]->c = p2->mono[i]->c;
    }
  }    
}
  
/* 最高次項の係数が0の時、次数を減らし最高次項の係数がゼロにならないようにする */
void zero_delete(Polynomial *p)
{
  int i = p->n;
  while (p->mono[i]->c == 0 && i > 0) {
    free(p->mono[i]);
    (p->n)--;
    i--;
  }
}
/* 多項式を作る関数 */
/* 同類項をまとめた多項式を生成する */
Polynomial* transform_to_polynomial(char *string)
{
  char cut[] = "+-";
  int len, i;
  int maxn = 0;                 /* 最大次数 */
  char cutsymbol[MAXLEN];
  char **buffer = s_strcut(string, cut, &len, cutsymbol);
  Polynomial *tmp = (Polynomial *)malloc(sizeof(Polynomial));
  tmp->mono = (Monomial**)malloc(sizeof(Monomial*)*(len+1));
  for (i = 0; i < len; i++) {
    tmp->mono[i] = transform_to_monomial(buffer[i]);
    if (cutsymbol[i] == '-') {
      tmp->mono[i]->c *= -1;
    }
    if (tmp->mono[i]->n > maxn) {
      maxn = tmp->mono[i]->n;
    }
  }
  Polynomial *ret = initialize_polynomial(maxn);
  for (i = 0; i < len; i++) {
    if (tmp->n >= 0) { 
      ret->mono[tmp->mono[i]->n]->c += tmp->mono[i]->c;
    } else {
      return NULL;
    }
  }
  free(tmp);
  return ret;
}

void print_monomial(Monomial *m)
{
  if (m == NULL) fprintf(stderr, "NULL\n");
  if (m->n != 0 && m->n != 1) { 
    printf("%+d*x^%d ", m->c, m->n);
  } else if (m->n == 1) {
    printf("%+d*x ", m->c);
  } else if (m->n == 0) {
    printf("%+d ", m->c);
  }
}

void print_polynomial(Polynomial *p)
{
  if (p == NULL) fprintf(stderr, "NULL\n");
  int i;
  for (i = 0; i <= p->n; i++) {
    print_monomial(p->mono[i]);
  }
  printf("\n");
}

/* 多項式のスカラー倍 */
Polynomial *scalar_polynomial(Polynomial *p1, int c)
{
  Polynomial *scalar = initialize_polynomial(p1->n);
  int i;
  for (i = 0; i <= p1->n; i++) {
    scalar->mono[i]->c = p1->mono[i]->c * c;
  }
  return scalar;
}

/* 多項式の加算 p1, p2は同類項でまとめられ、次数は昇順で並んでいるとする*/
Polynomial *addition_polynomial(Polynomial *p1, Polynomial *p2){
  int maxn;
  int i;
  if (p1->n > p2->n) {
    maxn = p1->n;
  } else {
    maxn = p2->n;
  }
  Polynomial *addition = initialize_polynomial(maxn);
  for (i = 0; i <= maxn; i++) {
    if (i <= p1->n && i <= p2->n) { 
      addition->mono[i]->c = p1->mono[i]->c + p2->mono[i]->c;
    } else if (i <= p1->n) {
      addition->mono[i]->c = p1->mono[i]->c;
    } else if (i <= p2->n) {
      addition->mono[i]->c = p2->mono[i]->c;
    }
  }
  zero_delete(addition);
  return addition;
}

/* 多項式の減算 */
Polynomial *subtraction_polynomial(Polynomial *p1, Polynomial *p2)
{
  Polynomial *subtraction = addition_polynomial(p1, scalar_polynomial(p2,-1));
  return subtraction;
}

/* 多項式同士の乗算 */
Polynomial *product_polynomial(Polynomial *p1, Polynomial *p2)
{
  int i,j;
  const int max = p1->n + p2->n;
  Polynomial *product = initialize_polynomial(max);
  for (i = 0; i <= p1->n; i++) {
    for (j = 0; j <= p2->n; j++) {
      product->mono[p1->mono[i]->n + p2->mono[j]->n]->c += p1->mono[i]->c * p2->mono[j]->c;
    }
  }
  return product;
}

/* 多項式の除算 */
Polynomial *quotient_polynomial(Polynomial *dividend, Polynomial *divisor)
{
  int i, j, c;
  Polynomial *quotient = initialize_polynomial(dividend->n - divisor->n);
  Polynomial *tmp = initialize_polynomial(divisor->n);

  for (i = 0; i <= divisor->n; i++)  {
    tmp->mono[i]->c = dividend->mono[i+dividend->n-divisor->n]->c;
  }
  for (i = dividend->n; i >= divisor->n; i--) { 
    quotient->mono[i-divisor->n]->c = tmp->mono[divisor->n]->c / divisor->mono[divisor->n]->c;
    c = quotient->mono[i-divisor->n]->c;
    tmp = subtraction_polynomial(tmp, scalar_polynomial(divisor, c));
    if (i != divisor->n) {
      for (j = divisor->n; j > 0; j--) {
        tmp->mono[j]->c = tmp->mono[j-1]->c;
      }
      tmp->mono[0]->c = dividend->mono[i-divisor->n-1]->c;
    }
  }
  free(tmp);
  return quotient;
}

/* 多項式のあまり */
Polynomial *remainder_polynomial(Polynomial *dividend, Polynomial *divisor)
{
  Polynomial *quotient = quotient_polynomial(dividend, divisor);
  Polynomial *product = product_polynomial(quotient, divisor);
  Polynomial *remainder = subtraction_polynomial(dividend, product);
  free(quotient);
  free(product);
  return remainder;
}

/* ユークリッド互除法で最大公約数を求める */
Polynomial *euclidean(Polynomial *p1, Polynomial *p2)
{
  int max;
  int i;
  Polynomial *major;
  Polynomial *minor;
  Polynomial *sub;              /* 引き算する */
  Polynomial *tmp;

  max = (p1->n > p2->n) ? p1->n : p2->n;

  major = initialize_polynomial(max);
  minor = initialize_polynomial(max);

  if (p1->n > p2->n) {
    copy_polynomial(major, p1);
    copy_polynomial(minor, p2);
  } else {
    copy_polynomial(major, p2);
    copy_polynomial(minor, p1);
  }

  while (!(minor->n == 0 && minor->mono[0]->c == 0)) {
    sub = initialize_polynomial(major->n);
    for (i = minor->n; i >= 0; i--) {
      sub->mono[i+ major->n - minor->n]->c = minor->mono[i]->c;
    }
    for (i = major->n - minor->n - 1; i >= 0; i--) {
      sub->mono[i]->c = 0;
    }

    tmp = subtraction_polynomial(major, scalar_polynomial(sub, major->mono[major->n]->c / sub->mono[major->n]->c));
    if (minor->n >= tmp->n) {
      copy_polynomial(major, minor);
      copy_polynomial(minor, tmp);
    } else {
      copy_polynomial(major, tmp);
    }
    print_polynomial(major);
    print_polynomial(minor);
    free(tmp);
    free(sub);
  }
  return major;
}

int main(int argc, char *argv[])
{
  char test1[] = "x^5-x^4+x^2-1";
  char test2[] = "x^3-x^2+x-1";
  Polynomial *p1 = transform_to_polynomial(test1);
  Polynomial *p2 = transform_to_polynomial(test2);
  /* Polynomial *p1 = transform_to_polynomial(argv[1]); */
  /* Polynomial *p2 = transform_to_polynomial(argv[2]); */
  Polynomial *ans = euclidean(p1, p2);
  print_polynomial(p1);
  print_polynomial(ans);
  
  free(p1);
  free(p2);
  free(ans);
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

