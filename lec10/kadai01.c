#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 1000
#define MAX_FILENAME 1000
#define BUFSIZE 1000
#define NAMESIZE 30

typedef struct Member_tag
{
    char name[NAMESIZE];
    int age;
    double height;
    double weight;
    struct Member_tag *next;
} Member;

int hash(char *);
Member* construct_member(char *name, int age, double height, double weight, Member *);
Member* add_array(Member **, char *name, int age, double height, double weight);
Member *search_array(Member *array[], char *name);

Member *root_array[HASHSIZE];
    
int main(int argc, char *argv[])
{
    char filename[MAX_FILENAME];
    FILE *fp;
    char buf[BUFSIZE];
    char bufname[NAMESIZE];

    if (argc == 1) {
      fprintf(stderr, "error: you have to enter an argument\nex) ./kadai01 namelist.txt");
      return 0;
    }
    strcpy(filename, argv[1]);
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "error: cannot open %s.\n", filename);
    }

    /* root_arrayに入力ファイルのデータを格納していく */
    while(fgets(buf, BUFSIZE, fp)){
        char *name = strtok(buf, ",");
        int age = atoi(strtok(NULL, ","));
        double height = atof(strtok(NULL, ","));
        double weight = atof(strtok(NULL, ","));
        root_array[hash(name)] = add_array(root_array,name, age, height, weight);
    }

    /* 名前を標準入力から検索する */
    printf("> ");
    while(fgets(bufname, BUFSIZE, stdin)){
        Member *tmp;
        bufname[strlen(bufname)-1] = '\0';
        if ((tmp = search_array(root_array, bufname)) != NULL) {
            printf("name %s\nage %d\nheight %lf\nweight %lf\n", tmp->name, tmp->age, tmp->height, tmp->weight);
        } else {
            printf("name %s is not found.\n", bufname);
        }
        printf("> ");
    }
    return 0;
}

Member *search_array(Member *array[], char name[NAMESIZE])
{
    Member *p;
    for (p = array[hash(name)]; strcmp(name, p->name) != 0;  p = p->next) {
      if (p->next == NULL) {
        return NULL;
      }
    }
    return p;
}

Member* add_array(Member *root_array[], char *name, int age, double height, double weight)
{
    Member *array = root_array[hash(name)];
    /* 最初の要素が存在しなかったら */
    if (array == NULL) {
        array = construct_member(name, age, height, weight, NULL);
    } else {
        Member *p = array;
        for (p = array; p->next != NULL; p = p->next){}
        p->next = construct_member(name, age, height, weight, NULL);
        p = p->next;
    }
    return array;
}

Member* construct_member(char *name, int age, double height, double weight, Member *next)
{
    Member* ret = (Member *)malloc(sizeof(Member));
    strcpy(ret->name, name);
    ret->age = age;
    ret->height = height;
    ret->weight = weight;
    ret->next = next;
    return ret;
}

int hash(char s[BUFSIZE])
{
    unsigned int val;
    int i = 0;
    for (val = 0; s[i] != '\0'; i++) {
        val = s[i] + (31*val);
    }
    
    return (int)(val % HASHSIZE);
}
