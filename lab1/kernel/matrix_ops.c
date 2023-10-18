#include "matrix_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//deprecated implementation of matmul
float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    // Matrix multiplication of A and B
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < A_cols; k++) {
                // row i of A * column j of B
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    

    return C;
}


#define TILE_SIZE 128 //also tried  64, 256
float **matmul_blocking(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    // Allocating memory for the resulting matrix C
    float** C = (float**) malloc(A_rows * sizeof(float*));

    for (int i = 0; i < A_rows; i++) C[i] = (float*) calloc(B_cols, sizeof(float));
    //implementing loop tiling 
    //to optimize matrix multiplication by dividing the computation into smaller and cache-friendly tiles.
    for(int t1 = 0; t1 < A_rows; t1 += TILE_SIZE)
        for(int t2 = 0; t2 < B_cols; t2 += TILE_SIZE)
            for(int t3 = 0; t3 < A_cols; t3 += TILE_SIZE)
                for(int i = t1; i < t1+TILE_SIZE && i < A_rows; i++)
                    for(int j = t2; j < t2+TILE_SIZE && j < B_cols; j++) {
                        float sum = 0;
                        for(int k = t3; k < t3+TILE_SIZE && k < A_cols; k++)
                            sum += A[i][k] * B[k][j];
                        C[i][j] += sum;
                    }
    return C;
}




//========= code used for Profiling function (do not modify) ==============================

// int main() {
//     srand(time(NULL));

    
//     int A_rows = 100;  
//     int A_cols = 100;  
//     int B_rows = 100;  
//     int B_cols = 100;  

//     float **matrixA = (float **)malloc(A_rows * sizeof(float *));
//     for (int i = 0; i < A_rows; i++) {
//         matrixA[i] = (float *)malloc(A_cols * sizeof(float));
//         for (int j = 0; j < A_cols; j++) {

//             matrixA[i][j] = (float)(rand() % 10);
//         }
//     }


//     float **matrixB = (float **)malloc(B_rows * sizeof(float *));
//     for (int i = 0; i < B_rows; i++) {
//         matrixB[i] = (float *)malloc(B_cols * sizeof(float));
//         for (int j = 0; j < B_cols; j++) {

//             matrixB[i][j] = (float)(rand() % 10);
//         }
//     }
    
//     // Running function and timing it and saving that to a csv file

//     // FILE *csvFile = fopen("100x100_blocking.csv", "w");
//     // if (!csvFile) {
//     //     perror("Failed to open CSV file for writing");
//     //     return 1;
//     // }

//     // fprintf(csvFile, "Iteration,Wall-Clock Time (ms)\n");

//     for (int i = 0; i < 50; i++) {
//         // clock_t start_time = clock();
//         float **result = matmul_blocking(matrixA,matrixB,A_rows, A_cols, B_rows, B_cols);
//         // clock_t end_time = clock();

//         // if (result == NULL) {
//         //     perror("Matrix multiplication error");
//         //     return 1;
//         // }

//         // Calculating the elapsed time in milliseconds
//         // double elapsed_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;

//         // printf("Iteration %d: Wall-Clock Time %.2f ms\n", i, elapsed_time);

//         // fprintf(csvFile, "%d,%.2f\n", i, elapsed_time);

//         // free(result);
//     }

//     // fclose(csvFile);


//     return 0;
// }