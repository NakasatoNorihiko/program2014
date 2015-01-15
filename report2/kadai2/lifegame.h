#ifndef _LIFEGAME_H_
#define _LIFEGAME_H_

void init_cells(FILE*);
int  number_life();
void update_cells(Node *);
void plot_cells(FILE*, int);

#endif
