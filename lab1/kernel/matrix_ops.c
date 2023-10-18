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

// Deprecated optimized implementation of matmu using loop tiling 
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



typedef struct {
    int row, col;
    float val;
} Entry;

Entry *create_csr(float **matrix, int rows, int cols) {
    Entry *sparse_matrix = (Entry*)malloc(sizeof(Entry) * rows * cols);
    int sparse_matrix_len = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse_matrix[sparse_matrix_len].row = i;
                sparse_matrix[sparse_matrix_len].col = j;
                sparse_matrix[sparse_matrix_len].val = matrix[i][j];
                sparse_matrix_len++;
            }
        }
    }

    return sparse_matrix;
}

float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    typedef struct {
        int row, col;
        float val;
    } Entry;

    float **result = (float **)malloc(sizeof(float *) * A_rows);
    for (int i = 0; i < A_rows; i++) {
        result[i] = (float *)calloc(B_cols, sizeof(float));
    }
    
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
    
    for (int i = 0; i < sparse_A_len; i++) {
        for (int j = 0; j < B_cols; j++) {
            if (B[sparse_A[i].col][j] != 0) {
                result[sparse_A[i].row][j] += sparse_A[i].val * B[sparse_A[i].col][j];
            }
        }
    }
    
    free(sparse_A);
    return result;
}


//========= code used for Profiling function (do not modify) ==============================


// Function to generate sparse matrix
float **generateSparseMatrix(int rows, int cols) {
    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++) {
            // We generate a random number and make it sparse by making 
            // 50% of the elements zero
            float element = ((float)(rand() % 10) / 10.0) < 0.5 ? 0 : (float)(rand() % 10);
            matrix[i][j] = element;
        }
    }
    return matrix;
}


int main() {
    srand(time(NULL));

    int A_rows = 100;  
    int A_cols = 100;  
    int B_rows = 100;  
    int B_cols = 100;  

    float **matrixA = generateSparseMatrix(A_rows, A_cols);
    float **matrixB = generateSparseMatrix(B_rows, B_cols);
    
    // Running function and timing it and saving that to a csv file

    FILE *csvFile = fopen("100x100_sparse.csv", "w");
    if (!csvFile) {
        perror("Failed to open CSV file for writing");
        return 1;
    }

    fprintf(csvFile, "Iteration,Matmul_Sparse Time (ms),Matmul Time (ms)\n");

    for (int i = 0; i < 50; i++) {
        // matmul_sparse
        clock_t start_time = clock();
        float **result_sparse = matmul_sparse(matrixA, matrixB, A_rows, A_cols, B_rows, B_cols);
        clock_t end_time = clock();

        if (result_sparse == NULL) {
            perror("Sparse Matrix multiplication error");
            return 1;
        }
        
        // Calculating the elapsed time in milliseconds
        double elapsed_time_sparse = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;

        // matmul
        start_time = clock();
        float **result = matmul(matrixA, matrixB, A_rows, A_cols, B_cols);
        end_time = clock();

        if (result == NULL) {
            perror("Matrix multiplication error");
            return 1;
        }
        
        double elapsed_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;

        fprintf(csvFile, "%d,%.2f,%.2f\n", i, elapsed_time_sparse, elapsed_time);

        free(result_sparse);
        free(result);
    }
    fclose(csvFile);

    return 0;
}