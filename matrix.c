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
    int index=0;
    for(int i=0; i<ri; i++)
        index += matrix.stride_rows;
    
    for(int i=0; i<ci; i++)
        index++;
    

    return matrix.data[index];
}
void put_element(Matrix matrix, int ri, int ci,int elem){
    if (ri >= matrix.n_rows || ci >= matrix.n_cols){
        printf("** Erro: índice out of range **\n\n");
        exit(1);
    }
    int index=0;
    for(int i=0; i<ri; i++)
        index += matrix.stride_rows;
    for(int i=0; i<ci; i++)
        index++;

    matrix.data[index]=elem;
}
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

Matrix transpose(Matrix matrix) {

    matrix.n_rows = matrix.n_cols;
    matrix.n_cols = matrix.n_rows;
    matrix.stride_rows = matrix.stride_cols;
    matrix.stride_cols = matrix.stride_rows;
    
    return matrix;
}
Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){
    int quantidade_de_elementos = matrix.n_rows * matrix.n_cols;

    if(quantidade_de_elementos != new_n_rows * new_n_cols){
        printf("** Erro: nova matriz nao pode ter esse formato**\n");
        exit(1);
    }

    matrix.n_rows = new_n_rows;
    matrix.n_cols = new_n_cols;
    matrix.stride_rows = new_n_cols;

    return matrix;
}

int min(Matrix matrix){
    int min_n=matrix.data[matrix.offset];
    for(int i=matrix.offset; i<matrix.n_cols*matrix.n_rows; i++){
        if(min_n>matrix.data[i]){
            min_n=matrix.data[i];
        }
    }
    return min_n;
}
int max(Matrix matrix){
    int max_n=matrix.data[matrix.offset];
    for(int i=matrix.offset; i<matrix.n_cols*matrix.n_rows; i++){
        if(max_n<matrix.data[i]){
            max_n=matrix.data[i];
        }
    }
    return max_n;
}
int argmin(Matrix matrix){
    int min_n=min(matrix);
    for(int i=matrix.offset; i<matrix.n_cols*matrix.n_rows; i++){
        if(matrix.data[i]==min_n){
            return i;

        }
    }
    printf("\n");
}
int argmax(Matrix matrix){
    int max_n=max(matrix);
    for(int i=matrix.offset; i<matrix.n_cols*matrix.n_rows; i++){
        if(matrix.data[i]==max_n){
            return i;

        }
    }
}

Matrix add(Matrix matrix_1, Matrix matrix_2){

     if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols || matrix_1.offset != matrix_2.offset ){
        printf("** Erro: As matrizes possuem dimensões diferentes ou offsets diferentes**\n\n");
        exit(1);
    }
    Matrix matrix;
    int *vector;
    int nelementos = matrix_1.n_rows * matrix_2.n_cols;

    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=matrix_1.offset; i<nelementos; i++)
        vector[i] = matrix_1.data[i]+matrix_2.data[i];

    matrix = create_matrix(vector, matrix_1.n_rows, matrix_2.n_cols);
    free(vector);
    return matrix;

}
Matrix sub(Matrix matrix_1, Matrix matrix_2){

     if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols || matrix_1.offset != matrix_2.offset ){
        printf("** Erro: As matrizes possuem dimensões diferentes ou offsets diferentes**\n\n");
        exit(1);
    }
    Matrix matrix;
    int *vector;
    int nelementos = matrix_1.n_rows * matrix_2.n_cols;

    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=matrix_1.offset; i<nelementos; i++)
        vector[i] = matrix_1.data[i]-matrix_2.data[i];

    matrix = create_matrix(vector, matrix_1.n_rows, matrix_2.n_cols);
    free(vector);
    return matrix;

}
Matrix division(Matrix matrix_1, Matrix matrix_2){
     if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols || matrix_1.offset != matrix_2.offset ){
        printf("** Erro: As matrizes possuem dimensões diferentes ou offsets diferentes**\n\n");
        exit(1);
    }
    Matrix matrix;
    int *vector;
    int nelementos = matrix_1.n_rows * matrix_2.n_cols;

    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=matrix_1.offset; i<nelementos; i++)
        vector[i] = matrix_1.data[i]/matrix_2.data[i];

    matrix = create_matrix(vector, matrix_1.n_rows, matrix_2.n_cols);
    free(vector);
    return matrix;

}
Matrix mul(Matrix matrix_1, Matrix matrix_2){

     if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols || matrix_1.offset != matrix_2.offset ){
        printf("** Erro: As matrizes possuem dimensões diferentes ou offsets diferentes**\n\n");
        exit(1);
    }
    Matrix matrix;
    int *vector;
    int nelementos = matrix_1.n_rows * matrix_2.n_cols;

    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=matrix_1.offset; i<nelementos; i++)
        vector[i] = matrix_1.data[i]*matrix_2.data[i];

    matrix = create_matrix(vector, matrix_1.n_rows, matrix_2.n_cols);
    free(vector);
    return matrix;

}

