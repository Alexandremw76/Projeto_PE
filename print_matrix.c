#include <stdio.h>

typedef struct {
  int *data;
  int n_rows;
  int n_cols;
  int stride_rows;
  int stride_cols;
  int offset;
} Matrix;

void print_matrix(Matrix matrix){
    int index = 0;

    printf("%d Linha(s) x %d Coluna(s)\n", matrix.n_rows, matrix.n_cols);

    printf("[");
    for(int i=0;i<matrix.n_rows; i++){

        if(i>0)
            printf(" ");
        printf("[");

        /* caso matriz transposta */
        if(matrix.stride_rows==1)
            index = i;

        for(int j=0; j<matrix.n_cols; j++){
            printf("%d", matrix.data[index]);

            if(j != matrix.n_cols-1)
                printf(" ");

            index += matrix.stride_cols;
        }
        if(i < matrix.n_rows-1)
            printf("]\n");
        else
            printf("]");
    }
    printf("]\n");
}