#ifndef CREATION_H
#define CREATION_H

typedef struct {
  int *data;
  int n_rows;
  int n_cols;
  int stride_rows;
  int stride_cols;
  int offset;
} Matrix;

/* função geral para criação de uma matriz */
Matrix create_matrix(int *data, int n_rows, int n_cols);
#endif
