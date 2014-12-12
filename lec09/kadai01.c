#include <stdio.h>
#include <stdlib.h>

typedef struct monomial 
{
    int c;
    int n;
} mono;

/* 単項式をつくる関数 */
mono* construct_monomial(int c, int n)
{
    mono *ret = (mono*)malloc(sizeof(mono));
    ret->c = c;
    ret->n = n;
    return ret;
}

/* 単項式を微分する関数 */
void diff_monomial(mono *m) 
{
    m->c = (m->n)*(m->c);
    m->n = m->n - 1;
}

void print_monomial(mono *m)
{
    printf("%d*x^%d\n", m->c, m->n);
}

int main()
{
    mono *m1;

    m1 = construct_monomial(-4, 10);
    print_monomial(m1);
    diff_monomial(m1);
    print_monomial(m1);

    return 0;
}
