#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_LEN 100
#define CONTENT 3

char**  s_strcut(char *ori, char *cut, int *datalen); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
    
int main(int argv, char *argc[])
{
    FILE *fp;
    char buffer[MAX_LEN];
    double max[CONTENT];
    double min[CONTENT];
    double mean[CONTENT];
    double stdev[CONTENT];
    double bufd[CONTENT];
    char cut[1] = {','};        /* 何で切り分けるかを入れる変数(今回は',') */
    char **buf;
    int dlen;                   /* s_strlenの変数datalenを満たすためのへんすう */
    int len = 0;
    int i;

    for (i = 0; i < CONTENT; i++) {
        max[i] = min[i] = mean[i] = stdev[i] = 0;
    }
    
    fp = fopen(argc[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open the file\n");
        return 1;
    }

    while(fgets(buffer, MAX_LEN, fp) != NULL) {
        buf = s_strcut(buffer, cut, &dlen);
        for (i = 0; i < CONTENT; i++) {
            bufd[i] = atoi(buf[i+1]);
            if (len == 0) {
                max[i] = min[i] = bufd[i];
            } else {
                if (bufd[i] > max[i]) {
                    max[i] = bufd[i];
                } else if (bufd[i] < min[i]) {
                    min[i] = bufd[i];
                }
                mean[i] += bufd[i];
            }
            stdev[i] += pow(bufd[i],2);
        }
        len++;
        free(buf);
    }
    
    for (i = 0; i < CONTENT; i++) {
        mean[i] /= len;
        stdev[i] /= len;
        stdev[i] -= pow(mean[i], 2);
        stdev[i] = pow(stdev[i], 0.5);
    }

    for (i = 0; i < CONTENT; i++) {
        switch(i) {
        case 0:
            printf("Age :    ");
            break;
        case 1:
            printf("Height : ");
            break;
        case 2:
            printf("Weight : ");
            break;
        }
        printf("(max,min,mean,stdev) = %3.f, %3.f, %3.1f, %3.1f\n", max[i], min[i], mean[i], stdev[i]);
    }
    fclose(fp);
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
