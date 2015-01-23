#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "kadai2_ext.h"
#include "char_rule.h"
#include "my_math.h"

void plus_all(char char_or_all[], char *list[], int list_len)
{
  int i;
  char_or_all[0] = '\0';
  
  for (i = 0; i < list_len; i++) {
    if (i < list_len - 1) {
      strcat(char_or_all, "Plus[");
      strcat(char_or_all, list[i]);
      strcat(char_or_all, ",");
    } else {
      strcat(char_or_all, list[i]);
    }      
  }
  for (i = 0; i < list_len-1; i++) {
    strcat(char_or_all, "]");
  }
}

void or_all(char char_or_all[], char *list[], int list_len)
{
  int i;
  char_or_all[0] = '\0';
  
  for (i = 0; i < list_len; i++) {
    if (i < list_len - 1) {
      strcat(char_or_all, "Or[");
      strcat(char_or_all, list[i]);
      strcat(char_or_all, ",");
    } else {
      strcat(char_or_all, list[i]);
    }      
  }
  for (i = 0; i < list_len-1; i++) {
    strcat(char_or_all, "]");
  }
}

void eq_adjecent(char rule[], int n)
{
  char and_all[1000];
  char *list[8];
  int i, j, list_i;
  list_i = 0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (i == 1 && j == 1) continue;
      list[list_i] = (char*)malloc(sizeof(char));
      sprintf(list[list_i], "C%d%d", i+1, j+1) ;
      list_i++;
    }
  }
  plus_all(and_all,list,8);
  char char_n[2];
  char_n[0] = '0' + n;
  char_n[1] = '\0';
  rule[0] = '\0';
  strcat(rule, "Eq[");
  strcat(rule, and_all);
  strcat(rule, ",");
  strcat(rule, char_n);
  strcat(rule, "]");
  for (i = 0; i < 8; i++) {
    free(list[i]);
  }
}


void make_rule(char rule[], int alive, int dead)
{
  char **char_alive_tmp = (char**)malloc(sizeof(char*)*8);
  char **char_dead_tmp  = (char**)malloc(sizeof(char*)*8);
  char char_alive[1000];
  char char_dead[1000];

  int i;
  for (i = 0; (alive / power(10,i)) != 0; i++) {
    char_alive_tmp[i] = (char*)malloc(sizeof(char)*1000);
    eq_adjecent(char_alive_tmp[i], (alive % power(10,i+1)) / power(10,i));
  }
  int alive_n = i;
  for (i = 0; (dead / power(10,i)) != 0; i++) {
    char_dead_tmp[i] = (char*)malloc(sizeof(char)*1000);
    eq_adjecent(char_dead_tmp[i], dead % power(10,i+1) / power(10,i));
  }
  int dead_n = i;

  or_all(char_alive, char_alive_tmp, alive_n);
  or_all(char_dead , char_dead_tmp , dead_n );
  
  rule[0] = '\0';
  strcat(rule, "If[C22,If[");
  strcat(rule, char_alive);
  strcat(rule, ",1,0],If[");
  strcat(rule, char_dead);
  strcat(rule, ",1,0]]");
}
