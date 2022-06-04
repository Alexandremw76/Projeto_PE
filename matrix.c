#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix create_matrix(int *data,int n_rows, int n_cols){

    Matrix matrix;
    /* calcula o total de entradas da matriz*/
    int nelementos = n_rows * n_cols;

    /*Aloca no ponteiro o espaço necessario para guardar a matriz de entrada */
    matrix.data = (int *) malloc(nelementos * sizeof(int));
    
    //matrix.data == NULL
    if(!matrix.data){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }

    /* Copia a matriz da entrada para a matriz do struct*/
    for (int i=0;i<nelementos;i++){
        matrix.data[i] = data[i];
    }

    matrix.n_rows = n_rows;
    matrix.n_cols = n_cols;
    matrix.stride_rows = n_cols;
    matrix.stride_cols = 1;
    matrix.offset = 0;

    return matrix;
}

Matrix zeros_matrix(int n_rows, int n_cols){
    Matrix matrix;
    int *null_vector = (int *) calloc(n_rows * n_cols, sizeof(int));

    matrix = create_matrix(null_vector, n_rows, n_cols);

    free(null_vector);
    return matrix;
}

Matrix full_matrix(int n_rows, int n_cols, int value){
    Matrix matrix;
    int *vector = (int *) calloc(n_rows * n_cols, sizeof(int));

    for(int i=0; i<n_rows*n_cols; i++)
        vector[i] = value;
    
    matrix = create_matrix(vector, n_rows, n_cols);

    free(vector);
    return matrix; 
}

Matrix i_matrix(int n){
    Matrix matrix;

    matrix = zeros_matrix(n,n);

    for(int i=0; i<n*n; i+=n+1)
        matrix.data[i] = 1;

    return matrix;
}

Matrix tile_matrix(Matrix matrix, int reps){
    Matrix m;
    int *vector;
    int nelementos = matrix.n_rows * matrix.n_cols * reps * reps;

    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }

    for(int i=0; i<nelementos; i+=matrix.n_rows*matrix.n_cols){
        for(int j=0; j<(matrix.n_rows*matrix.n_cols);j++){
            vector[i+j] = matrix.data[j];
        }
    }

    m = create_matrix(vector, matrix.n_rows*reps, matrix.n_cols*reps);

    free(vector);
    return m;
}

int get_element(Matrix matrix, int ri, int ci){
    if (ri >= matrix.n_rows || ci >= matrix.n_cols){
        printf("** Erro: índice out of range **\n\n");
        exit(1);
    }
    int index;
    for(int i=0; i<ri; i++)
        index += matrix.stride_rows;
    for(int i=0; i<ci; i++)
        index++;

    return matrix.data[index];
}

