#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 70
#define STATUS 10

static int cell[HEIGHT][WIDTH];        /* 0 生物存在せず、1 元の生物 2進化後物 3最終進化生物 */
int cell_num[STATUS];

void init_cells()
{
    int i, j;

    for (i = 0; i < STATUS; i++) {
        cell_num[i] = 0;
    }
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            cell[i][j] = rand() % 2;
        }
    }
}

void print_cells(FILE *fp)
{
    int i, j;
    char c;
    fprintf(fp, "----------\n");

    for (i = 0; i < STATUS; i++) {
        cell_num[i] = 0;
    }
    
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (cell[i][j] != 0) {
                c = cell[i][j]+'0';
                cell_num[cell[i][j]]++;
            } else {
                c = ' ';
                cell_num[0]++;
            }
            fputc(c, fp);
        }
        fputc('\n', fp);
    }
    fflush(fp);

    sleep(1);
}

void count_adjacent_cells(int i, int j, int n[STATUS])
{
    int k, l;
    for (k = 0; k < STATUS; k++) {
        n[k] = 0;
    }
    for (k = i - 1; k <= i + 1; k++) {
        if (k < 0 || k >= HEIGHT) continue;
        for (l = j - 1; l <= j + 1; l++) {
            if (k == i && l == j) continue;
            if (l < 0 || l >= WIDTH) continue;
            n[cell[k][l]]++;
        }
    }
}

void update_cells()
{
    int i, j, k;
    int n[STATUS];
    int nt;
    int cell_next[HEIGHT][WIDTH];
    int end = 0;

    for (i = 0; i < HEIGHT; i++ ){
        for ( j = 0; j < WIDTH; j++) {
            cell_next[i][j] = 0;
        }
    }
    
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            count_adjacent_cells(i, j, n);
            nt = 0;
            for (k = 1; k < STATUS; k++) {
                nt += n[k];
            }
            
            if (cell[i][j] == 0) {
                if (nt == 3) {
                    end  = 0;
                    for (k = 1; k < STATUS; k++) {
                        if (n[k] == 3 && (rand() % 10 != 0)) {
                            cell_next[i][j] = k;
                            end = 1;
                        } else if (n[k] == 3)  {
                            cell_next[i][j] = k+1;
                            end = 1;
                        }
                    }
                    if (end == 0) {
                        if (n[9] + n[8] == 3) {
                            cell_next[i][j] = 9;
                            end =1 ;
                        }
                    }
                    for (k = STATUS - 2; k > 1 && end == 0; k--) {
                        if (n[k-1]+n[k]+n[k+1] == 3) {
                            cell_next[i][j] = k;
                            end = 1;
                        } 
                    }
                    if (end == 0) {
                        if (n[2] + n[1] == 3) {
                            cell_next[i][j] = 2;
                        }
                    }
                }
            } else {
                if (nt == 2 || nt == 3) {
                    cell_next[i][j] = cell[i][j];
                } else {
                    cell_next[i][j] = 0;
                }
            }

        }
    }
    
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            cell[i][j] = cell_next[i][j];
        }
    }
}


int main()
{
    int gen = 1;
    int i;
    FILE *fp;

    if ((fp = fopen("cells3.txt", "w")) == NULL) {
        fprintf(stderr, "error: cannot open a file.\n");
        return 1;
    }

    init_cells();
    print_cells(fp);

    while (1) {
        printf("generation = %d, number =", gen++);
        for (i = 1; i < STATUS; i++) {
            printf(" %d", cell_num[i]);
        }
        printf("\n");
        update_cells();
        print_cells(fp);
    }

    fclose(fp);
}
