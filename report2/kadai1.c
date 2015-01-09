#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define VALUE_LEN 10
#define MAXLEN 100
    
char**  s_strcut(char *ori, char *cut, int *datalen, char *); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
int s_strlen(char *);
void s_strcpy(char *, char *);

typedef struct Node_tag
{
    char value[VALUE_LEN];
    struct Node_tag *left;
    struct Node_tag *right;
} Node;

void parse(Node *n) 
{
    printf("%s", n->value);
    char *e;
    double value = strtod(n->value, &e);
    if (strcmp(e, "") != 0 && (strcmp(e, "Sin") != 0 || strcmp(e, "Cos") != 0)){
        printf("[");
        parse(n->left);
        printf(",");
        parse(n->right);
        printf("]");
    } else if (strcmp(e, "Sin") == 0 || strcmp(e, "Cos") == 0) {
        printf("[");
        parse(n->left);
        printf("]");
    }
    return;
}

Node *create_tree(int *pos, char **s)
{
    char *e;
    Node *current_node = (Node*)malloc(sizeof(Node));
    strcpy(current_node->value, s[*pos]);
    double value = strtod(current_node->value, &e);

    if (strcmp(e, "") == 0) {
        current_node->left = NULL;
        current_node->right = NULL;
        (*pos)++;
        return current_node;
    } else if (strcmp(e, "Sin") == 0 || strcmp(e, "Cos") == 0) {
        (*pos)++;
        current_node->left = create_tree(pos, s);
        current_node->right = NULL;
    } else {
        (*pos)++;
        current_node->left = create_tree(pos, s);        /* 次の文字のノードを作成 */
        current_node->right = create_tree(pos, s);
    }
    return current_node;
}

double calculate(Node *n)
{
    char *e;
    double value = strtod(n->value, &e);
    
    if (strcmp(e, "") == 0){
        return value;
    }
    
    double left = calculate(n->left);
    double right = calculate(n->right);
    if (strcmp(n->value, "Plus") == 0) {
        return left + right;
    } else if (strcmp(n->value, "Subtract") == 0) {
        return left - right;
    } else if (strcmp(n->value, "Times") == 0) {
        return left * right;
    } else if (strcmp(n->value, "Divide") == 0) {
        return left / right;
    } else if (strcmp(n->value, "Sin") == 0) {
        return sin(left);
    } else if (strcmp(n->value, "Cos") == 0) {
        return cos(left);
    } else {
        printf("error: there is character which is not '+-*/'\n");
        return -1;
    }
}

int main(int argc, char *argv[])
{
    int p = 0;
    double value;
    char **value_string = s_strcut(argv[1], "[,]", NULL, NULL);
    Node *root = create_tree(&p, value_string);
    parse(root);
    printf("\n");
    value = calculate(root);
    printf("%lf\n", value);
    /* double d; */
    /* char *e; */
    /* d = strtod("Sin" , &e); */
    /* printf("%lf\n", d); */
    /* printf("%s\n", e); */
    
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

