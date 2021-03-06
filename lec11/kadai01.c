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

int main()
{
    char *str = "+/9*84-*84+73"; /* 22.281250 */
    int p = 0;
    Node *root = create_tree(&p, str);
    parse(root);
    printf("\n");
    return 0;
}

     
