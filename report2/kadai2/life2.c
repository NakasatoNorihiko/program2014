/* 初期値パターン入力規則 */

/* 生命存在 -> # */
/* 存在しない -> ' ' or 入力なし */
/* 改行によって行変更 */

#include <stdio.h>              
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 70
#define BUFSIZE 1000

int cell[HEIGHT][WIDTH];
int cell_num;

void init_cells()
{
    int i, j;
    char buf[BUFSIZE];
    FILE *fp;
    const char *filename = "init_life.txt";

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("error: can't open %s\n", filename);
        return;
    }

    i = 0;
    while (fgets(buf, BUFSIZE, fp) != NULL && i < HEIGHT) {
        j = 0;
        while(buf[j] != '\n' && j < WIDTH) {
            cell[i][j] = (buf[j] == '#') ? 1 : 0;
            j++;
        }
        while (j < WIDTH) {
            cell[i][j] = 0;
            j++;
        }
        i++;
    }
    while (i < HEIGHT) {
        for (j = 0; j < WIDTH; j++) {
            cell[i][j] = 0;
        }
        i++;
    }
    
    cell_num = 0;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            cell_num += cell[i][j];
        }
    }
    fclose(fp);
}

void print_cells(FILE *fp)
{
    int i, j;
    char c;
    fprintf(fp, "----------\n");

    cell_num = 0;
    
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (cell[i][j] == 1) {
                c = '#';
                cell_num++;
            } else {
                c = ' ';
            }
            fputc(c, fp);
        }
        fputc('\n', fp);
    }
    fflush(fp);

    sleep(1);
}

int count_adjacent_cells(int i, int j)
{
    int n = 0;
    int k, l;
    for (k = i - 1; k <= i + 1; k++) {
        if (k < 0 || k >= HEIGHT) continue;
        for (l = j - 1; l <= j + 1; l++) {
            if (k == i && l == j) continue;
            if (l < 0 || l >= WIDTH) continue;
            n += cell[k][l];
        }
    }
    return n;
}

void update_cells()
{
    int i, j;
    int cell_next[HEIGHT][WIDTH];

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            int n = count_adjacent_cells(i, j);
            if (cell[i][j] == 0) {
                if (n == 3)  
                    cell_next[i][j] = 1;
                else         
                    cell_next[i][j] = 0;
            } else {
                if (n == 2 || n == 3)  
                    cell_next[i][j] = 1;
                else 	  
                    cell_next[i][j] = 0;
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

    FILE *fp;

    if ((fp = fopen("cells.txt", "w")) == NULL) {
        fprintf(stderr, "error: cannot open a file.\n");
        return 1;
    }

    init_cells();
    print_cells(fp);

    while (1) {
        printf("generation = %d the number of cells = %d\n", gen++, cell_num);
        update_cells();
        print_cells(fp);
    }

    fclose(fp);
}
