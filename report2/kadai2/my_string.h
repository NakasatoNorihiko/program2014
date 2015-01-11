#ifndef _MY_STRING_H_
#define _MY_STRING_H_

char**  my_strcut(char *ori, char *cut, int *datalen, char *); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
int my_strlen(char *);
void my_strcpy(char *, char *);

#endif
