#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int my_strlen(char *str)
{
  int len = 0;
  while(str[len] != '\0') {
    len++;
  }
  return len;
}

void my_strcpy(char *str1, char *str2)
{
  int len;
  int i;
  len = my_strlen(str2);
  for (i = 0; i <= len; i++) {
    str1[i] = str2[i];
  }
  return;
}
            
/* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す *cutsymbol　に何で切られたのかを書く*/
char** my_strcut(char *ori, char *cut, int *datalen, char cutsymbol[MAXLEN]) {
  int i, j; 
  char **data;
  int orilen = my_strlen(ori);
  int cutn = my_strlen(cut);
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

