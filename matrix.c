#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int matriz[9]={7, 2, 3, 4, 5, 6, 7, 8, 9};

int main()
{   Matrix m;
    m = create_matrix(matriz,3,3);
    //printf("%d",m.data[0]);

}
Matrix create_matrix(int *data,int n_rows, int n_cols)
{   
    Matrix m;
    int total=n_cols*n_rows;/* calcula o total de entradas da matriz*/
    m.data=malloc(total*sizeof(int));/*Aloca no ponteiro o espaço necessario para guardar a matriz de entrada */
    for (int i=0;i<total;i++){/* Copia a matriz da entrada para a matriz do struct*/
        m.data[i]=data[i];
    }
    m.n_rows=n_rows;
    m.n_cols=n_cols;
    m.stride_rows=n_cols;
    m.stride_cols=1;
    m.offset=0;
    return m;

}
