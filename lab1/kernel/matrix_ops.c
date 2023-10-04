#include "matrix_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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




//========= code used for Profiling function (do not modify) ==============================

// int main() {
//     srand(time(NULL));

    
//     int A_rows = 1000;  
//     int A_cols = 1000;  
//     int B_rows = 1000;  
//     int B_cols = 1000;  

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


//     float **result = matmul(matrixA, matrixB, A_rows, A_cols, B_rows, B_cols);



//     return 0;
// }