#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int s_strlen(char *);            /* 文字列の長さを測る関数 */
void s_strcpy(char *, char *);   /* 文字列をコピーする関数 */
char**  s_strcut(char *ori, char *cut, int *cutn); /* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す */

int main(int argc, char *argv[]) 
{
    char **mon;

    int monn;                 /* monnは単項式の数 */
    int i,j;
    
    mon = s_strcut(argv[1], "+-", &monn);
    
    for (i = 0; i < monn; i++) {
      if (mon[i][0] == '+') {
        for (j = 0; j < s_strlen(mon[i]); j++) {
          mon[i][j] = mon[i][j+1];
        }
      }
    }
    printf("Polynomial = %s\n", argv[1]);
    for (i = 0; i < monn; i++) {
        printf("Monomial %d = %s\n", i+1, mon[i]);
    }
    free(mon);
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
     } else if (ori[i] == cut[j]) {
        state = 1;
      }
    }
    if (state == 1 && i != 0){
      tmp[k] = '\0';
      data[n] = (char*)malloc(sizeof(char) * (k+1));
      s_strcpy(data[n], tmp);
      tmp[0] = ori[i];
      k = 1;
      n++;
    } else {
      tmp[k] = ori[i];
      k++;
    }
  }

  return data;
}
