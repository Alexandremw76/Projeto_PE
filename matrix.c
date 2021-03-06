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
/* Repete a matriz de entrada reps vezes na horizontal */
    Matrix m;
    int *vector;
    int nelementos = matrix.n_rows * matrix.n_cols;
    int index=matrix.offset;

    vector = (int *) malloc(nelementos*reps*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }

    for(int k=0; k<nelementos*reps; k+=matrix.n_cols*reps){
        
        for(int i=0; i<matrix.n_cols*reps; i+=matrix.n_cols){ 

            for(int j=0; j<matrix.n_cols;j++){
                vector[i+j+k] = matrix.data[index];
                index += matrix.stride_cols;
            }
            //index -= matrix.n_cols; 
            index -= matrix.n_cols * matrix.stride_cols;
            //index = (i) * matrix.n_cols + matrix.offset;
        }
        //index = (index+1) * matrix.n_cols + matrix.offset;
        index += matrix.stride_rows;
    }

    m = create_matrix(vector, matrix.n_rows, matrix.n_cols*reps);

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
    

    return matrix.data[index+matrix.offset];
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

    matrix.data[index+matrix.offset]=elem;
}
void print_matrix(Matrix matrix){
    int index = matrix.offset;

    printf("%d Linha(s) x %d Coluna(s)\n", matrix.n_rows, matrix.n_cols);

    printf("[");
    for(int i=0;i<matrix.n_rows;i++){

        if(i>0)
            printf(" ");
        printf("[");

        for(int j=0; j<matrix.n_cols; j++){
            // index = matrix.stride_rows*i+matrix.stride_cols*j;
            // index += matrix.offset;
            printf("%2d", matrix.data[index]);

            index += matrix.stride_cols;
            
            if(j != matrix.n_cols-1)/* caractere separador*/
                printf(" ");
        }

        //reajustar o índice
        index = (i+1) * matrix.stride_rows + matrix.offset;
        /*
        if(i < matrix.n_rows-1)
            printf("]\n");
        else
            printf("]");
        */
        printf("%s", i<matrix.n_rows-1? "]\n" : "]");
    }
    printf("]\n");
}

Matrix transpose(Matrix matrix) {
    Matrix transposed;

    transposed.data = matrix.data;
    transposed.n_rows = matrix.n_cols;
    transposed.n_cols = matrix.n_rows;
    transposed.stride_rows = matrix.stride_cols;
    transposed.stride_cols = matrix.stride_rows;
    transposed.offset = matrix.offset;
    
    return transposed;
}
Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){
    Matrix reshaped;
    int quantidade_de_elementos = matrix.n_rows * matrix.n_cols;

    if(quantidade_de_elementos != new_n_rows * new_n_cols){
        printf("** Erro: nova matriz nao pode ter esse formato**\n");
        exit(1);
    }

    reshaped.data = matrix.data;
    reshaped.n_rows = new_n_rows;
    reshaped.n_cols = new_n_cols;
    reshaped.stride_rows = new_n_cols;
    reshaped.stride_cols = matrix.stride_cols;
    reshaped.offset = matrix.offset;

    return reshaped;
}
Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){
    Matrix sliced;

    if(re-rs>a_matrix.n_rows || ce-cs>a_matrix.n_cols){
        printf("\n** Erro: Índice out of range **\n");
        exit(1);
    }
    sliced.data = a_matrix.data;
    sliced.n_rows = re-rs;
    sliced.n_cols = ce-cs;
    sliced.stride_rows = a_matrix.n_cols;
    sliced.offset = a_matrix.stride_rows * rs + cs;
    
    if(sliced.n_cols == 1)
        sliced.stride_cols = sliced.stride_rows;
    else
        sliced.stride_cols = 1;

    return sliced;
}

int min(Matrix matrix){
   int min_n=matrix.data[matrix.offset];
   int index=matrix.offset;
   for(int i=0;i<matrix.n_rows;i++)
    {   

        for(int j=0; j<matrix.n_cols; j++)
        {
            if (min_n > matrix.data[index]){
                min_n = matrix.data[index];
        }
            index += matrix.stride_cols;
        }

        if(matrix.stride_rows==1)
        { 
            index = matrix.offset + matrix.stride_rows;
        }
        else
        {
            if(matrix.n_cols>1)
            {
                index = (i+1)*matrix.stride_rows + matrix.offset;
            }
        }
    }
    return min_n;
}
int max(Matrix matrix){
   int max_n=matrix.data[matrix.offset];
   int index=matrix.offset;
   for(int i=0;i<matrix.n_rows;i++)
    {   
        for(int j=0; j<matrix.n_cols; j++)
        {
            if (max_n < matrix.data[index])
            {
                max_n = matrix.data[index];
            }
            index += matrix.stride_cols;
        }

        if(matrix.stride_rows==1)
        { 
            index = matrix.offset + matrix.stride_rows;
        }
        else
        {
            if(matrix.n_cols>1)
            {
                index = (i+1)*matrix.stride_rows + matrix.offset;
            }
        }
    }
    return max_n;
}
int argmin(Matrix matrix){
   int min_n=matrix.data[matrix.offset];
   int index=matrix.offset;
   int cont = index;
   for(int i=0;i<matrix.n_rows;i++)
    {   

        for(int j=0; j<matrix.n_cols; j++)
        {
            if (min_n > matrix.data[index])
            {
                min_n = matrix.data[index];
                cont = index;
            }
            index += matrix.stride_cols;
        }

        if(matrix.stride_rows==1)
        { 
            index = matrix.offset + matrix.stride_rows;
        }
        else
        {
            if(matrix.n_cols>1)
            {
                index = (i+1)*matrix.stride_rows + matrix.offset;
            }
        }
    }
    return cont;
}
int argmax(Matrix matrix){
   int max_n=matrix.data[matrix.offset];
   int index=matrix.offset;
   int cont = index;
   for(int i=0;i<matrix.n_rows;i++)
    {   

        for(int j=0; j < matrix.n_cols; j++)
        {
            if (max_n < matrix.data[index])
            {
                max_n = matrix.data[index];
                cont = index;
            }
            index += matrix.stride_cols;
        }

        if(matrix.stride_rows==1)
        { 
            index = matrix.offset + matrix.stride_rows;
        }
        else
        {
            if(matrix.n_cols>1)
            {
                index = (i+1)*matrix.stride_rows + matrix.offset;
            }
        }
    }
    return cont;
}
Matrix add(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols ){
        printf("** Erro: As matrizes possuem dimensões diferentes **\n\n");
        exit(1);
    }
    Matrix matrix;
    int nelementos = matrix_1.n_rows * matrix_2.n_rows;
    int *vector;
    int index_matriz_1=matrix_1.offset;
    int index_matriz_2=matrix_2.offset;
    int cont = 0;
    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=0;i<matrix_1.n_rows;i++)
    {
        for(int j=0; j<matrix_1.n_cols; j++)
        {
            vector[cont]=matrix_1.data[index_matriz_1]+matrix_2.data[index_matriz_2];
            cont++;
            index_matriz_1 += matrix_1.stride_cols;
            index_matriz_2 += matrix_2.stride_cols;

        }

        if(matrix_1.stride_rows==1)
        { 
            index_matriz_1 = matrix_1.offset + matrix_1.stride_rows;
            index_matriz_2 = matrix_2.offset + matrix_2.stride_rows;
        }
        else
        {
            if(matrix_1.n_cols>1)
            {
                index_matriz_1 = (i+1)*matrix_1.stride_rows + matrix_1.offset;
                index_matriz_2 = (i+1)*matrix_2.stride_rows + matrix_2.offset;
            }
        }
    }
    matrix = create_matrix(vector, matrix_1.n_rows, matrix_1.n_cols);
    free(vector);
    return matrix;

}
Matrix sub(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols ){
        printf("** Erro: As matrizes possuem dimensões diferentes **\n\n");
        exit(1);
    }
    Matrix matrix;
    int nelementos = matrix_1.n_rows * matrix_2.n_rows;
    int *vector;
    int index_matriz_1=matrix_1.offset;
    int index_matriz_2=matrix_2.offset;
    int cont = 0;
    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=0;i<matrix_1.n_rows;i++)
    {
        for(int j=0; j<matrix_1.n_cols; j++)
        {
            vector[cont]=matrix_1.data[index_matriz_1]-matrix_2.data[index_matriz_2];
            cont++;
            index_matriz_1 += matrix_1.stride_cols;
            index_matriz_2 += matrix_2.stride_cols;

        }

        if(matrix_1.stride_rows==1)
        { 
            index_matriz_1 = matrix_1.offset + matrix_1.stride_rows;
            index_matriz_2 = matrix_2.offset + matrix_2.stride_rows;
        }
        else
        {
            if(matrix_1.n_cols>1)
            {
                index_matriz_1 = (i+1)*matrix_1.stride_rows + matrix_1.offset;
                index_matriz_2 = (i+1)*matrix_2.stride_rows + matrix_2.offset;
            }
        }
    }
    matrix = create_matrix(vector, matrix_1.n_rows, matrix_1.n_cols);
    free(vector);
    return matrix;

}
Matrix division(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols ){
        printf("** Erro: As matrizes possuem dimensões diferentes **\n\n");
        exit(1);
    }
    Matrix matrix;
    int nelementos = matrix_1.n_rows * matrix_2.n_rows;
    int *vector;
    int index_matriz_1=matrix_1.offset;
    int index_matriz_2=matrix_2.offset;
    int cont = 0;
    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=0;i<matrix_1.n_rows;i++)
    {
        for(int j=0; j<matrix_1.n_cols; j++)
        {
            vector[cont]=matrix_1.data[index_matriz_1]/matrix_2.data[index_matriz_2];
            cont++;
            index_matriz_1 += matrix_1.stride_cols;
            index_matriz_2 += matrix_2.stride_cols;

        }

        if(matrix_1.stride_rows==1)
        { 
            index_matriz_1 = matrix_1.offset + matrix_1.stride_rows;
            index_matriz_2 = matrix_2.offset + matrix_2.stride_rows;
        }
        else
        {
            if(matrix_1.n_cols>1)
            {
                index_matriz_1 = (i+1)*matrix_1.stride_rows + matrix_1.offset;
                index_matriz_2 = (i+1)*matrix_2.stride_rows + matrix_2.offset;
            }
        }
    }
    matrix = create_matrix(vector, matrix_1.n_rows, matrix_1.n_cols);
    free(vector);
    return matrix;

}
Matrix mul(Matrix matrix_1, Matrix matrix_2){
    if (matrix_1.n_rows != matrix_2.n_rows || matrix_1.n_cols != matrix_2.n_cols ){
        printf("** Erro: As matrizes possuem dimensões diferentes **\n\n");
        exit(1);
    }
    Matrix matrix;
    int nelementos = matrix_1.n_rows * matrix_2.n_rows;
    int *vector;
    int index_matriz_1=matrix_1.offset;
    int index_matriz_2=matrix_2.offset;
    int cont = 0;
    vector = (int *) malloc(nelementos*sizeof(int));

    if(!vector){
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    for(int i=0;i<matrix_1.n_rows;i++)
    {
        for(int j=0; j<matrix_1.n_cols; j++)
        {
            vector[cont]=matrix_1.data[index_matriz_1]*matrix_2.data[index_matriz_2];
            cont++;
            index_matriz_1 += matrix_1.stride_cols;
            index_matriz_2 += matrix_2.stride_cols;

        }

        if(matrix_1.stride_rows==1)
        { 
            index_matriz_1 = matrix_1.offset + matrix_1.stride_rows;
            index_matriz_2 = matrix_2.offset + matrix_2.stride_rows;
        }
        else
        {
            if(matrix_1.n_cols>1)
            {
                index_matriz_1 = (i+1)*matrix_1.stride_rows + matrix_1.offset;
                index_matriz_2 = (i+1)*matrix_2.stride_rows + matrix_2.offset;
            }
        }
    }
    matrix = create_matrix(vector, matrix_1.n_rows, matrix_1.n_cols);
    free(vector);
    return matrix;
}