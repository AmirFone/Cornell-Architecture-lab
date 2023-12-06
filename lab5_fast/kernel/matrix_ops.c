#include "matrix_ops.h"
#include <stdlib.h>
#include <stdio.h>

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    // Allocate memory for the result matrix
    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j = 0; j < B_cols; j++) {
            C[i][j] = 0.0;
        }
    }

    // Loop order changed to optimize cache usage
    for (int i = 0; i < A_rows; ++i) {
        for (int k = 0; k < A_cols; ++k) {
            for (int j = 0; j < B_cols; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}