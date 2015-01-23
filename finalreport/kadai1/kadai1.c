#include <stdio.h>

#include "my_string.h"
#include "tree_function.h"

int main(int argc, char *argv[])
{
    int p = 0;
    double value;
    /* char test_expression[] = "Subtract[Plus[Sin[3.4],Times[Cos[4.1],8]],Divide[Sin[2.1],Cos[1.2]]]"; */
    /* char **value_string = my_strcut(test_expression, "[,]", NULL, NULL); */
    char **value_string = my_strcut(argv[1], "[,]", NULL, NULL);
    Node *root = create_tree(&p, value_string);
    parse(root);
    printf(" = ");
    value = calculate(root);
    printf("%lf\n", value);
    
    return 0;
}
