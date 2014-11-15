#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double **value;                 /* 数値 */
  int row;                      /* 行の数 */
  int column;                   /* 列の数 */
} matrix_t;

int s_strlen(char *);            /* 文字列の長さを測る関数 */
void s_strcpy(char *, char *);   /* 文字列をコピーする関数 */
char**  s_strcut(char *ori, char *cut, int *cutn); /* 文字列oriをcutに含まれる文字で切り分ける関数 datalenにdataの要素数を返す */
void str2mat(char *ori, matrix_t *mat, char *row, char *column);
matrix_t* pmat(matrix_t *, matrix_t *);
void pdarray(double *, int);

int main(int argc, char *argv[]) 
{
    int i;
    matrix_t mat[2];            /* A, B*/
    matrix_t *C;
    int m;

    for (i = 0; i < 2; i++) {
      str2mat(argv[i+1], &(mat[i]), ":", ",");
    }

    C = pmat(&(mat[0]), &(mat[1]));

    for (i = 0; i < 2; i++) {
      if (i == 0) {
        printf("A=\n");
      } else if (i == 1){
        printf("B=\n");
      } 
      for (m = 0; m < mat[i].row; m++) {
        pdarray((mat[i].value)[m], mat[i].column);
      }
    }
    printf("A*B=\n");
    for (m = 0; m < C->row; m++) {
      pdarray((C->value)[m], C->column);
    }
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

/* 文字列oriと区切り規則row, columnを元に行列を作りdouble**を返す。*matに行列の大きさを返す */
void str2mat(char *ori, matrix_t *mat, char *row, char *column) {
  char ***cmat;                 /* doubleにする直前の行列 */
  char **crowmat;              /* 列が区切られていない文字列 */
  double **matrix;
  int i, j;

  crowmat = s_strcut(ori, row, &(mat->row));
  (mat->row)--;
  cmat = (char***)malloc(sizeof(char**)*(mat->row));
  for (i = 0; i < mat->row; i++) {
    cmat[i] = s_strcut(crowmat[i], column, &(mat->column));
  }

  matrix = (double**)malloc(sizeof(double*)*(mat->row));
  for (i = 0; i < mat->row; i++) {
    matrix[i] = (double*)malloc(sizeof(double)*(mat->column));
  }
  
  for (i = 0; i < mat->row; i++) {
    for (j = 0; j < mat->column; j++) {
      matrix[i][j] = atof(cmat[i][j]);
    }
  }

  mat->value = matrix;
  free(cmat);
  free(crowmat);

  return;
}

matrix_t* pmat(matrix_t *A, matrix_t *B)
{
  matrix_t *C;
  C = (matrix_t*)malloc(sizeof(matrix_t));
  int i, m, k, n;
  if (A->column != B->row) {
    printf("Aの列数とBの行数が一致していません\n");
    return NULL;
  } else {
    C->value = (double**)malloc(sizeof(double*)*(A->row));
    for (i = 0; i < A->row; i++) {
      (C->value)[i] = (double*)malloc(sizeof(double)*(B->column));
    }
    for (m = 0; m < A->row; m++) {
      for (k = 0; k < B->column; k++) {
        (C->value)[m][k] = 0;
      }
    }
    for (m = 0; m < A->row; m++) {
      for (n = 0; n < A->column; n++) {
        for (k = 0; k < B->column; k++) {
          (C->value)[m][k] += (A->value)[m][n] * (B->value)[n][k];
        }
      }
    }
    C->row = A->row;
    C->column = B->column;
  }
  return C;
}

void pdarray(double *array, int n) {
  int i;
  printf("[");
  for (i = 0; i < n; i++) {
    printf("%lf", array[i]);
    if (i != n-1) {
      printf(",");
    } else {
      printf("]\n");
    }
  }
  return;
}
