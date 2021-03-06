#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
#define MAX_LINE 15000

char**  s_strcut(char *ori, char *cut, int *datalen); /* 文字列oriをcutに含まれる文字で切り分ける関数 datallenにdataの要素数を返す */
int s_strlen(char *);
void s_strcpy(char *, char *);
    
typedef struct person_s
{
    char name[20];
    int age;
    double weight;
    double height;
    struct person_s *next;
    struct person_s *previous;
} person;

person* construct_person(char name[20], int age, double weight, double height, person *previous)
{
    person* ret = (person *)malloc(sizeof(person));
    strcpy(ret->name, name);
    ret->age = age;
    ret->weight = weight;
    ret->height = height;
    ret->next = NULL;
    if (previous != NULL) {   /* 前が存在したら */
        /* previous->next = ret;   /\* 前のpersonを作ったpersonに連結する *\/ */
        ret->previous = previous;
    } else {
        ret->previous = NULL;
    }
    return ret;
}

void print_person(person* p) 
{
    printf("name: %s\nage: %d\nweight: %lf\nheight: %lf\n", p->name, p->age, p->weight, p->height);
}

/* 最初のメンバ*p, 表示する人数n */
void print_many_person(person *p, int n) 
{
    int i;
    person *print = p;
    for (i = 0; i < n; i++) {
        print_person(print);
        print = print->next;
    }
    printf("\n");
}
    
void delete_person(person *h, char *s)
{
    person *c = h;
    do {
        if (strcmp(c->name, s) == 0) {
            print_person(c);
            printf("was deleted.\n");
            if (c->previous != NULL) {
                (c->previous)->next = c->next;
            }
            if (c->next != NULL) {
                (c->next)->previous = c->previous;
            }
        }
        c = c->next;
    } while (c != NULL);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int len = 0;

    char cut[1] = {','};
    char **buf;
    char buffer[MAX_LEN];
    FILE *fp;
    person *current, *first;
    int dlen;                   /* s_strlenの変数datelenを満たすだけの変数、意味はない */

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Failed to open the file\n");
        return 1;
    }

    len = 0;
    while(fgets(buffer, MAX_LEN, fp) != NULL) {
        buf = s_strcut(buffer, cut, &dlen);
        if (len == 0) {
          current = construct_person(buf[0], atoi(buf[1]), atof(buf[3]), atof(buf[2]), NULL);
          first = current;
        } else {
          current->next = construct_person(buf[0], atoi(buf[1]), atof(buf[3]), atof(buf[2]), current);
          current = current->next;
        }
        len++;
        free(buf);
    }

    print_many_person(first, 5);
    delete_person(first,argv[2]);
    print_many_person(first, 5);

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
            
/* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す */
char** s_strcut(char *ori, char *cut, int *datalen) {
    int i, j, k, n;
    char **data;
    int orilen = s_strlen(ori);
    int cutn = s_strlen(cut);
    char tmp[1000];
    int state;

    *datalen = 1;                  /* 何個に分割されるかを示す */
    n = 0;
    for(i = 0; i < orilen; i++) {
        for (j = 0; j < cutn; j++) {
            if (ori[i] == cut[j]) {
                (*datalen)++;
            }
        }
    }
    data = (char **)malloc(sizeof(char*)*(*datalen));

    k = 0;
    for (i = 0; i <= orilen; i++) {
        state = 0;
        for (j = 0; j < cutn; j++) {
            if (ori[i] == '\0') {
                state = 1;
            } else if (ori[i] == cut[j]) {
                state = 1;
            }
        }
        if (state == 1){
            tmp[k] = '\0';
            data[n] = (char*)malloc(sizeof(char) * (k+1));
            s_strcpy(data[n], tmp);
            k = 0;
            n++;
        } else {
            tmp[k] = ori[i];
            k++;
        }
    }

    return data;
}
