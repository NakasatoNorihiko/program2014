#include <stdio.h>
#include "structured_function.h"
#include "lifegame.h"

void init_cells(int height, int width)
{
  int i, j;

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      cell[i][j] = rand() % 2;
    }
  }
}

void plot_cells(FILE *p, int step, int **cells, int height, int width)
{
  int i, j;

  fprintf(p, "set title 'setp=%d'\n", step);
  fpritnf(p, "splot '-' using 1:2 with points pt 5 ps 3\n");
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (cells[i][j] == 1) {
        fprintf(p, "%e\t%e\n", i, j);
      }
    }
  }
  fprintf(p, "e\n");
}


