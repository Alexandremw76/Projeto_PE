#include <stdio.h>
//#include <stdlib.h>
#include "matrix.h"

#define DEBUG1 0
#define DEBUG2 0

int main(){
    Matrix m1, m2;
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[] = {1, 2, 3, 4, 5, 6};
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int element;

    m1 = create_matrix(arr3,4,3);
    print_matrix(m1);
    //m1 = zeros_matrix(3,5);
    //m1 = full_matrix(4,4,2);
    //m1 = i_matrix(5);
    //m2 = create_matrix(arr1,1,9);
    //m1 = tile_matrix(m2,3);

    //element1 = get_element(m1, 0, 3);
    //element = get_element(m1, 0, 1);
    //put_element(m1,1,1,7);
    
    //reshape(m1, 2, 3);
    m1 = slice(m1,1,3,0,2);
    print_matrix(m1);
    m1 = transpose(m1);
    print_matrix(m1);

    #if DEBUG1
    printf("\tDados da matriz m1\n");
    printf("nelementos: %d\n", m1.n_rows * m1.n_cols);
    //int *ptr=&m1.data[m1.offset];
    
    int cont = 0;
    int nelementos = m1.n_rows*m1.n_cols;
    /* n sei se funciona com transposta */
    for(int i=m1.offset;cont<nelementos;i+=m1.stride_rows){
        for(int j=0;j<m1.n_cols;j++){
            printf(" %d", m1.data[i+j]);
            cont++;
        }
    }
    printf("\nnrows: %d\nncols: %d\nstride_rows: %d\nstride_cols: %d\noffset: %d\n",
             m1.n_rows, m1.n_cols, m1.stride_rows, m1.stride_cols, m1.offset);
    #endif

    #if DEBUG2
    printf("\nElement: %d\n", element);

    #endif

    return 0;
}
