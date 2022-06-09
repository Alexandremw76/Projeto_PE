#include <stdio.h>
//#include <stdlib.h>
#include "matrix.h"

#define DEBUG1 1
#define DEBUG2 0

int main(){
    Matrix m1, m2, m3;
    int arr1[9] = {7, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[6] = {9, 7, 5, 4, 6, 5};
    int element;

    m1 = create_matrix(arr1,3,3);
    //m1 = zeros_matrix(3,5);
    //m1 = full_matrix(4,4,2);
    //m1 = i_matrix(5);
    //m2 = create_matrix(arr1,1,9);
    //m1 = tile_matrix(m2,3);

    //element1 = get_element(m1, 0, 3);
    //element = get_element(m1, 0, 1);
    //put_element(m1,1,1,7);
    
    //transpose(m1);
    //reshape(m1, 2, 3);
    m1 = slice(m1,0,2,1,3);
    print_matrix(m1);

    #if DEBUG1
    printf("\tDados da matriz m1\n");
    printf("nelementos: %d\n", m1.n_rows * m1.n_cols);
    int *ptr=&m1.data[m1.offset];
    for(;ptr<&m1.data[(m1.n_rows*m1.n_cols)+m1.offset];)
        if(m1.stride_cols==1){
            if(ptr<&m1.data[m1.stride_rows]){
                ptr++;
            }else{

            }
            
        }
        printf("%d ", *ptr);
    printf("\nnrows: %d\nncols: %d\nstride_rows: %d\nstride_cols: %d\noffset: %d\n",
             m1.n_rows, m1.n_cols, m1.stride_rows, m1.stride_cols, m1.offset);
    /*
    printf("\tDados da matriz m2\n");
    printf("nelementos: %d\n", m2.n_rows * m2.n_cols);
    for(int *ptr=m2.data;ptr<&m2.data[m2.n_rows*m2.n_cols];ptr++)
        printf("%d ", *ptr);
    printf("\nnrows: %d\nncols: %d\nstride_rows: %d\nstride_cols: %d\noffset: %d\n",
             m2.n_rows, m2.n_cols, m2.stride_rows, m2.stride_cols, m2.offset);
    */
    #endif

    #if DEBUG2
    printf("\nElement: %d\n", element);

    #endif

    return 0;
}
