#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "my_string.h"
#include "tree_function.h"

void parse(Node *n) 
{
  printf("%s", n->value);

  if (n->n_branch == 0) {
    return;
  }

  int i;
  printf("[");
  for (i = 0; i < n->n_branch; i++) {
    parse(n->branch[i]);
    if (i + 1 < n->n_branch) {
      printf(",");
    }
  }
  printf("]");
  return;
}

int find_n_branch(char value[])
{
  /* 枝が1本出る関数はbranch[0],2本出る関数はbranch[1]にある */
  char* branch[2][4] = {{"Sin" , "Cos"     , ""     , ""},
                        {"Plus", "Subtract", "Times", "Divide"}};
  char *e;
  strtod(value, &e);
  /* valueが数字だったら */
  if (strcmp(e, "") == 0) {
    return 0;
  }
  
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      if (strcmp(e, branch[i][j]) == 0) {
        return i+1;
      }
    }
  }
  
  return -1;                    /* 予定語に入っておらず、数でもない場合 */
}

Node *create_tree(int *pos, char **s)
{
  int i;
  Node *current_node = (Node*)malloc(sizeof(Node));
  strcpy(current_node->value, s[*pos]);
  current_node->n_branch = find_n_branch(current_node->value);
  
  (*pos)++;
  if (current_node->n_branch == 0) {
    current_node->branch = NULL;
  } else {
    current_node->branch = (Node**)malloc(sizeof(Node*)*current_node->n_branch);
    for (i = 0; i < current_node->n_branch; i++) {
      current_node->branch[i] = create_tree(pos, s);        /* 次の文字のノードを作成 */
    }
  }
  return current_node;
}

double calculate(Node *n)
{
  if (n == NULL) {
    return -1;
  }
  char *e;
  double current_value = strtod(n->value, &e);
  int i;
    
  if (strcmp(e, "") == 0){
    return current_value;
  }

  double next_value[MAX_BRANCH];
  for (i = 0; i < n->n_branch; i++) {
    next_value[i] = calculate(n->branch[i]);
  }
  if (strcmp(n->value, "Plus") == 0) {
    return next_value[0] + next_value[1];
  } else if (strcmp(n->value, "Subtract") == 0) {
    return next_value[0] - next_value[1];
  } else if (strcmp(n->value, "Times") == 0) {
    return next_value[0] * next_value[1];
  } else if (strcmp(n->value, "Divide") == 0) {
    return next_value[0] / next_value[1];
  } else if (strcmp(n->value, "Sin") == 0) {
    return sin(next_value[0]);
  } else if (strcmp(n->value, "Cos") == 0) {
    return cos(next_value[0]);
  } else {
    printf("error: %s is not a string you can use.\n", n->value);
    return -1;
  }
}


