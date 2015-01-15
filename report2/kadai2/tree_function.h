#ifndef _FUNCTION_STRUCTURING_H_
#define _FUNCTION_STRUCTURING_H_

#define VALUE_LEN 10
#define MAX_BRANCH 100
    
typedef struct Node_tag
{
  char value[VALUE_LEN];
  struct Node_tag **branch;
  int n_branch;
} Node;

void parse(Node *);
Node *char2tree(char[]);
int  find_n_branch(char *);
Node *create_tree(int *, char **);
int  calculate(Node *,int, int);

#endif

