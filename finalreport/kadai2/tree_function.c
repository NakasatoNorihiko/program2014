#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "my_string.h"
#include "tree_function.h"
#include "kadai2_ext.h"

#define RULE_LEN 1000

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

Node *char2tree(char char_rule[]) {
  char **value_string = my_strcut(char_rule, "[,]", NULL, NULL);
  int p = 0;
  Node *node_rule = create_tree(&p, value_string);
  free(value_string);
  return node_rule;
}

int find_n_branch(char value[])
{
  char *e;
  strtod(value, &e);
  
  char* branch[3][7] = {{"Not" , ""     , ""         , ""      , ""  , ""  , ""  },
                        {"Plus", "Times", "Subtract", "Divide", "Eq", "Or", "And"},
                        {"If"  , ""     , ""         , ""      , ""  , ""  , ""  }};

  if (strcmp(e, "") == 0) {
    return 0;
  }
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 7; j++) {
      if (strcmp(e, branch[i][j]) == 0) {
        return i+1;
      }
    }
  }
  return 0;                    /* 予定語に入っておらず、数でもない場合 */
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

/* kadai1のcalculateとは異なる */
int calculate(Node *n, int height, int width)
{
  if (n == NULL) {
    return -1;
  }
  char *e;
  double current_value = strtod(n->value, &e);
  int i;
  current_value = (int)current_value;

  if (strcmp(e, "") == 0){
    return current_value;
  }
  
  if (n->value[0] == 'C') {
    int h = n->value[1] - '2';
    int w = n->value[2] - '2';
    if ((height + h >= 0 && height + h < HEIGHT) && (width + w >= 0 && width + w < WIDTH)) {
      return cells[height + h][width + w];
    } else {
      return 0;
    }
  }

  int next_value[MAX_BRANCH];
  for (i = 0; i < n->n_branch; i++) {
    next_value[i] = calculate(n->branch[i], height, width);
  }
  if (strcmp(n->value, "Plus") == 0) {
    return next_value[0] + next_value[1];
  } else if (strcmp(n->value, "Times") == 0) {
    return next_value[0] * next_value[1];
  } else if (strcmp(n->value, "Subtract") == 0) {
    return next_value[0] - next_value[1];
  } else if (strcmp(n->value, "Divide") == 0) {
    return next_value[0] / next_value[1];
  } else if (strcmp(n->value, "Eq") == 0) {
    return (next_value[0] == next_value[1]);
  } else if (strcmp(n->value, "If") == 0 ){
    return (next_value[0] > 0 ? next_value[1] : next_value[2]);
  } else if (strcmp(n->value, "Or") == 0) {
    return (next_value[0] > 0 || next_value[1] > 0);
  } else if (strcmp(n->value, "And") == 0) {
    return (next_value[0] > 0 && next_value[1] > 0);
  } else if (strcmp(n->value, "Not") == 0) {
    return (next_value[0] > 0 ? 0 : 1);
  } else {
    printf("error: %s is not a string you can use.\n", n->value);
    return -1;
  }
}

