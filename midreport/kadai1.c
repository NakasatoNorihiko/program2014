#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

char**  s_strcut(char *ori, char *cut, int *datalen, char *cutsymbol); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
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
  if (cutsymbol[0] != '\0') {
    ret = construct_monomial(atoi(buffer[0]), atoi(buffer[2]));
  } else {
    ret = construct_monomial(atoi(buffer[0]), 0);
  }
  free(buffer);
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
  if (m->c != 0) { 
    printf("%d*x^%d\n", m->c, m->n);
  } else {
    printf("0\n");
  }    
}

int main(int argc, char *argv[])
{
  Monomial *m1 = transform_to_monomial(argv[1]);

  printf("Diff: ");
  diff_monomial(m1);
  print_monomial(m1);

  free(m1);
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
char** s_strcut(char *ori, char *cut, int *datalen, char cutsymbol[MAXLEN]) {
  int i, j; 
  char **data;
  int orilen = s_strlen(ori);
  int cutn = s_strlen(cut);
  int len;
  int string_length[MAXLEN];

  if (cutsymbol != NULL) memset(cutsymbol, '\0', MAXLEN);

  len = 1;/* 何個に分割されるかを示す */
  memset(string_length, 0, 1000);
  for(i = 0; i < orilen; i++) {
    for (j = 0; j < cutn; j++) {
      if (ori[i] == cut[j]) { /* 区切り文字ににあたった時 */
          if (cutsymbol != NULL) cutsymbol[len-1] = ori[i];
          len++;
      } else {            /* 区切り文字でないとき */
        string_length[len-1]++;
      }
    }
  }
  
  data = (char **)malloc(sizeof(char*)*len);
  data[0] = (char*)malloc(sizeof(char) * (string_length[0]+1));
  data[0] = strtok(ori, cut);
    
  for (i = 1; data[i-1] != NULL; i++) {
    data[i] = (char*)malloc(sizeof(char) * (string_length[i]+1));
    data[i] = strtok(NULL, cut);
  }
  if (datalen != NULL) *datalen = len;


  return data;
}
