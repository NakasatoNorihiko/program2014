#include <stdio.h>
#include <stdlib.h>
#include "tree_function.h"
#include "lifegame.h"
#include "kadai2_ext.h"

void init_cells(FILE *fp)
{
  int w, h;
  char tmp[WIDTH+10];
  if (fp == NULL) {
    for (w = 0; w < WIDTH; w++) {
      for (h = 0; h < HEIGHT; h++) {
        cells[h][w] = rand() % 2;
      }
    }
  } else {
    for (h = 0; fgets(tmp, WIDTH+10, fp) != NULL && h < HEIGHT; h++) {
      for (w = 0; tmp[w] != '\n' && w < WIDTH; w++) {
        cells[h][w] = (tmp[w] == '#') ? 1 : 0;
      }
      for (; w < WIDTH; w++) {
        cells[h][w] = 0;
      }
    }
  }
  for (; h < HEIGHT; h++) {
    for (w = 0; w < WIDTH; w++) {
      cells[h][w] = 0;
    }
  }
}

int number_life()
{
  int life_num = 0;
  int i, j;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if (cells[i][j] != 0) {
        life_num++;
      }
    }
  }
  return life_num;
}

void plot_cells(FILE *p, int step)
{
  int i, j;

  fprintf(p, "set title 'generation=%d'\n", step);
  fprintf(p, "plot '-' using 1:2 with points pt 5 ps 1\n");
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if (cells[i][j] == 1) {
        fprintf(p, "%d\t%d\n", j, i);
      }
    }
  }
  fprintf(p, "e\n");
}

void update_cells(Node *rule)
{
  int i, j;
  int new_cells[HEIGHT][WIDTH];

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      new_cells[i][j] = calculate(rule, i, j);
    }
  }
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cells[i][j] = new_cells[i][j];
    }
  }
}

