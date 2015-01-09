#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node 
{
    char value;
    struct node *left;
    struct node *right;
} Node;

void parse(Node *n)
{
    printf("%c", n->value);
    if (isdigit(n->value) == 0) {
        parse(n->left);
        parse(n->right);
    }
    return;
}

Node *create_tree(int *pos, char *s)
{
    Node *current_node = (Node*)malloc(sizeof(Node));
    current_node->value = s[*pos];

    if (isdigit(s[*pos])) {     /* 数字ならば */
        current_node->left = NULL;
        current_node->right = NULL;
        (*pos)++;
        return current_node;
    } else {                    /* 数字じゃないなら探索を継続する */
        (*pos)++;
        current_node->left = create_tree(pos, s);        /* 次の文字のノードを作成 */
        current_node->right = create_tree(pos, s);
    }
    return current_node;
}

double calculate(Node *n)
{
    char value[2];
    if (isdigit(n->value)){
        value[0] = n->value;
        value[1] = '\0';
        return atof(value);
    }
    
    double left = calculate(n->left);
    double right = calculate(n->right);
    if (n->value == '+') {
        return left + right;
    } else if (n->value == '-') {
        return left - right;
    } else if (n->value == '*') {
        return left * right;
    } else if (n->value == '/') {
        return left / right;
    } else {
        printf("error: there is character which is not '+-*/'\n");
        return -1;
    }
}

int main()
{
    char *str = "+-8*2+-8/27-*5*3+-8*2+-8/22-*2*315//2/9755/*2/945"; /* 234.138095 */
    int p = 0;
    double value = 0.0;
    Node *root = create_tree(&p, str);
    parse(root);
    printf("\n");
    value = calculate(root);
    printf("%lf\n", value);
    
    return 0;
}

     
