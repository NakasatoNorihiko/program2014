/* 多項式の加算、減算、乗算を定義する */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define MAXLEN 100           /* 項数の最大*/
#define ERROR 0.0001            /* 誤差の許容範囲 */

char**  s_strcut(char *ori, char *cut, int *datalen, char *); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
int s_strlen(char *);
void s_strcpy(char *, char *);

typedef struct
{
  double *a;                   /* 係数 */
  int n;                        /* ベクトルの次数 */
} Polynomial;

void transform_to_monomial(char *string, double *d, int *n)
{
  char cut[] = "*^";
  char cutsymbol[MAXLEN];
  char **buffer = s_strcut(string, cut, NULL, cutsymbol);
  if (cutsymbol[1] == '*' && cutsymbol[2] == '^') {
    *n = atoi(buffer[2]);
    d[atoi(buffer[2])] += atof(buffer[0]);
  } else if (cutsymbol[1] == '^') {
    *n = atoi(buffer[1]);
    d[atoi(buffer[1])] += 1;
  } else if (cutsymbol[1] == '*') {
    *n = 1;
    d[1] += atof(buffer[0]);
  } else if (strcmp(buffer[0],"x")== 0) {
    *n = 1;
    d[1] += 1;
  } else {
    *n = 0;
    d[0] += atof(buffer[0]);
  }
  free(buffer);
}

/* 多項式を初期化して生成 */
Polynomial* initialize_polynomial(int n)
{
  if (n >= 0) {
    Polynomial* ret = (Polynomial*)malloc(sizeof(Polynomial));
    ret->a = (double*)malloc(sizeof(double)*(n+1));
    ret->n = n;
    memset(ret->a, 0, n+1);
    return ret;
  } else {
    return NULL;
  }
}

void copy_polynomial(Polynomial *p1, Polynomial *p2)
{
  int i;
  if (p2->n <= p1->n) {
    p1->n = p2->n;
    for (i = 0; i <= p2->n; i++) {
      p1->a[i] = p2->a[i];
    }
    for (i = p2->n + 1; i <= p1->n; i++) {
      p1->a[i] = 0.0;
    }
  } else {
    for (i = 0; i <= p1->n; i++) {
      p1->a[i] = p2->a[i];
    }
  }    
}
  
/* 最高次項の係数が0の時、次数を減らし最高次項の係数がゼロにならないようにする */
void zero_delete(Polynomial *p)
{
  while (fabs(p->a[p->n]) <= ERROR && p->n > 0) {
    (p->n)--;
  }
  p->a = (double*)realloc(p->a, sizeof(double)*(p->n+1));
}
/* 多項式を作る関数 */
/* 同類項をまとめた多項式を生成する */
Polynomial* transform_to_polynomial(char *string)
{
  char cut[] = "+-";
  int len, i;
  int maxn = 0;                 /* 最大次数 */
  int tmpn = 0;
  char cutsymbol[MAXLEN];
  char **buffer = s_strcut(string, cut, &len, cutsymbol);
  Polynomial *tmp = (Polynomial *)malloc(sizeof(Polynomial));
  tmp->a = (double*)malloc(sizeof(double)*(MAXLEN));
  memset(tmp->a, 0, MAXLEN);
  for (i = 0; i < len; i++) {
    transform_to_monomial(buffer[i], tmp->a ,&tmpn);
    if (cutsymbol[i] == '-') {
      tmp->a[tmpn] *= -1;
    }
    if (tmpn > maxn) {
      maxn = tmpn;
    }
  }
  tmp->n = maxn;
  zero_delete(tmp);
  return tmp;
}

void print_polynomial(Polynomial *p)
{
  if (p == NULL) fprintf(stderr, "NULL\n");
  int i;
  for (i = 0; i <= p->n; i++) {
    if (i != 0 && i != 1) { 
      printf("%+2.1lf*x^%d ", p->a[i], i);
    } else if (i == 1) {
      printf("%+2.1lf*x ", p->a[i]);
    } else if (i == 0) {
      printf("%+2.1lf ", p->a[i]);
    }
  }
  printf("\n");
}

/* 多項式のスカラー倍 */
Polynomial *scalar_polynomial(Polynomial *p1, double c)
{
  Polynomial *scalar = initialize_polynomial(p1->n);
  int i;
  for (i = 0; i <= p1->n; i++) {
    scalar->a[i] = p1->a[i] * c;
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
      addition->a[i] = p1->a[i] + p2->a[i];
    } else if (i <= p1->n) {
      addition->a[i] = p1->a[i];
    } else if (i <= p2->n) {
      addition->a[i] = p2->a[i];
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
      product->a[i + j] += p1->a[i] * p2->a[j];
    }
  }
  return product;
}

/* x^(shift)倍する */
Polynomial* shift_polynomial(Polynomial *p, int shift)
{
  int i;
  Polynomial *s = initialize_polynomial(shift+p->n);
  if (shift >= 0) {
    for (i = 0; i <= p->n; i++) {
      s->a[i+shift] = p->a[i];
    }
    for (i = 0; i < shift; i++) {
      s->a[i] = 0;
    }
    return s;
  } else {
    for (i = 0; i <= p->n + shift; i++) {
      s->a[i] = p->a[i-shift];
    }
    return s;
  }
}

/* 多項式の除算 */
Polynomial *quotient_polynomial(Polynomial *dividend, Polynomial *divisor)
{
  int i, j, c;
  Polynomial *quotient = initialize_polynomial(dividend->n - divisor->n);
  /* Polynomial *tmp = initialize_polynomial(divisor->n); */

  Polynomial *tmp = initialize_polynomial(dividend->n);
  copy_polynomial(tmp, dividend);

  for (i = dividend->n; i >= divisor->n; i--) {
    if (i-divisor->n ==  tmp->n - divisor->n) {
      quotient->a[i-divisor->n] = tmp->a[tmp->n] / divisor->a[divisor->n];
      c = quotient->a[i-divisor->n];
      tmp = subtraction_polynomial(tmp, scalar_polynomial(shift_polynomial(divisor, tmp->n - divisor->n), c));
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

  while (!(minor->n == 0 && minor->a[0] <= ERROR)) {
    sub = initialize_polynomial(major->n);
    sub = shift_polynomial(minor, major->n - minor->n);

    tmp = subtraction_polynomial(major, scalar_polynomial(sub, major->a[major->n] / sub->a[major->n]));
    if (minor->n >= tmp->n) {
      copy_polynomial(major, minor);
      copy_polynomial(minor, tmp);
    } else {
      copy_polynomial(major, tmp);
    }
    free(tmp);
    free(sub);
  }
  return major;
}

int main(int argc, char *argv[])
{
  /* char test1[] = "x^6+3*x^5+x^3+2*x^2-4*x-3"; */
  /* char test2[] = "x^3+5*x^2+3*x-9"; */
  char test1[] = "x^4+x+1";
  char test2[] = "x^2+1";
  /* Polynomial *p1 = transform_to_polynomial(argv[1]); */
  /* Polynomial *p2 = transform_to_polynomial(argv[2]); */
  printf("GCD ");
  print_polynomial(quotient_polynomial(p1, p2));
  print_polynomial(remainder_polynomial(p1, p2));
  
  free(p1);
  free(p2);
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
char** s_strcut(char ori[], char *cut, int *datalen, char cutsymbol[MAXLEN]) {
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

