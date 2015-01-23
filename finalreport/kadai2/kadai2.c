#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"
#include "tree_function.h"
#include "lifegame.h"
#include "char_rule.h"
#include "kadai2_ext.h"

#define RULE_LEN 1000

/* argv[1]:生命維持の条件 argv[2]:生命誕生の条件 argv[3]:初期値のファイル argv[4]:最大ステップ数 argv[5]:出力ファイル名ex) ./kadai2 23 3 init.txt 100 lifegame.gif*/
int main(int argc, char *argv[])
{
  int generation = 0;
  int step;
  if (argc >= 2) {
    step = atoi(argv[4]);
  } else {
    fprintf(stderr, "step number is nessesary as a argument.\n");
    return -1;
  }
  
  char rule[1000];
  
  int alive = atoi(argv[1]);
  int dead  = atoi(argv[2]);
  
  make_rule(rule, alive, dead);
  printf("%s\n", rule);
  
  FILE *fpr, *fpw,  *gp;
  if ((fpr = fopen(argv[3], "r") ) == NULL) {
    fprintf(stderr, "%s cannot be opened.\n", argv[3]);
    fprintf(stderr, "initial position is random.\n");
    fpr = NULL;
  }
  char result_filename[] = "lifegame.dat";
  if ((fpw = fopen(result_filename, "w") ) == NULL) {
    fprintf(stderr, "%s cannot be opened.\n", result_filename);
    return -1;
  }
  if ((gp = popen("gnuplot", "w")) == NULL) {
    fprintf(stderr, "gnuplot cannot be used.\n");
    return -1;
  }

  Node *node_rule = char2tree(rule);
  printf("\n");

  fprintf(gp, "set terminal gif animate delay 10 optimize size 640,480\n");
  fprintf(gp, "set output \"%s\"\n", argv[5]);
  fprintf(gp, "set xrange [%d:%d]\n", 0, WIDTH);
  fprintf(gp, "set yrange [%d:%d]\n", HEIGHT, 0);
  fprintf(gp, "unset key\n");

  init_cells(fpr);
  fprintf(fpw, "%d %d\n", generation, number_life());
  plot_cells(gp, generation);
  for (generation = 1; generation <= step; generation++) {
    update_cells(node_rule);
    fprintf(fpw, "%d %d\n", generation, number_life());
    plot_cells(gp, generation);
  }
  fprintf(gp, "unset output\n");
  
  fclose(fpr);
  fclose(fpw);
  fclose(gp);
  free(node_rule);
  return 0;
}
