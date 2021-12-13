#include <stdio.h>
#include <stdlib.h>

int main() {

        int i,j,matrix_x,matrix_y;
        int *matrix1_ptr;
        int *matrix2_ptr;
        int *matrix_sum_ptr;

        printf("행렬 크기를 입력해주세요(X Y) : ");
        scanf("%d %d", &matrix_x,&matrix_y);

        matrix1_ptr = (int *)malloc(matrix_x * matrix_y * sizeof(int));
        matrix2_ptr = (int *)malloc(matrix_x * matrix_y * sizeof(int));
        matrix_sum_ptr = (int *)malloc(matrix_x * matrix_y * sizeof(int));

        if(matrix1_ptr == NULL || matrix2_ptr == NULL || matrix_sum_ptr == NULL) {
                printf("Memory Failed Allocate");
                exit(-1);

        }

        printf("Input Matrix 1 Numbers \n");
        for( i= 0; i < matrix_x*matrix_y; i++ )
                scanf("%d", &matrix1_ptr[i]);

        printf("Input Matrix 2 Numbers \n");
        for( i=0; i < matrix_x * matrix_y; i++ )
                scanf("%d", &matrix2_ptr[i]);

        for( i=0; i < matrix_x * matrix_y; i++ )
                matrix_sum_ptr[i] = matrix1_ptr[i]+matrix2_ptr[i];


        printf("Matrix Sum \n");
        for( i=0; i <matrix_x; i++ ) {
                printf("\n");
                for( j = 0; j <matrix_y; j++)
                        printf("%d",matrix_sum_ptr[i*j]);
        }

        free(matrix1_ptr);
        free(matrix2_ptr);
        free(matrix_sum_ptr);

}
