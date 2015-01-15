#ifndef _TREE_FUNCTION_H_
#define _TREE_FUNCTION_H_

#define VALUE_LEN 10
#define MAX_BRANCH 100
    
typedef struct Node_tag
{
  char value[VALUE_LEN];
  struct Node_tag **branch;
  int n_branch;
} Node;

void parse(Node *);
Node *create_tree(int *, char **);
double calculate(Node *);

#endif

