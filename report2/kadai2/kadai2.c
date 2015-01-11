#include <stdio.h>

#include "my_string.h"
#include "structured_function.h"
#include "lifegame.h"

#define RULE_LEN 1000
#define HEIGHT 50
#define WIDTH 70

int main()
{
  int cell[HEIGHT][WIDTH];
  double value;
  char rule_filename[] = "rule.txt";
  FILE *fp;
  if ((fp = fopen(rule_filename, "r") ) == NULL) {
    fprintf(stderr, "%s cannot be opened.\n", rule_filename);
  }
  char rule[RULE_LEN];
  fgets(rule, RULE_LEN, fp);
  char **value_string = my_strcut(rule, "[,]", NULL, NULL);
  int p = 0;
  Node *root = create_tree(&p, value_string);
  parse(root);
  printf("\n");
  /* value = calculate(root); */
  /* printf("%lf\n", value); */
  fclose(fp);
  return 0;
}
