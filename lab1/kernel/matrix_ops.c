#include "matrix_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    // Structure to represent a sparse matrix entry 
    typedef struct {
        int row, col;
        float val;
    } Entry;

    float **result = (float **)malloc(sizeof(float *) * A_rows);
    for (int i = 0; i < A_rows; i++) {
        result[i] = (float *)calloc(B_cols, sizeof(float));
    }
    // Allocate memory for the result matrix
    Entry *sparse_A = (Entry*) malloc(sizeof(Entry) * A_rows * A_cols);
    int sparse_A_len = 0;
     
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < A_cols; j++) {
            if (A[i][j] != 0) {
                sparse_A[sparse_A_len].row = i;
                sparse_A[sparse_A_len].col = j;
                sparse_A[sparse_A_len].val = A[i][j];
                sparse_A_len++;
            }
        }
    }
    // Perform sparse matrix multiplication
    for (int i = 0; i < sparse_A_len; i++) {
        for (int j = 0; j < B_cols; j++) {
            if (B[sparse_A[i].col][j] != 0) {
                result[sparse_A[i].row][j] += sparse_A[i].val * B[sparse_A[i].col][j];
            }
        }
    }
// Free sparse matrix
    free(sparse_A);
    return result;
} 