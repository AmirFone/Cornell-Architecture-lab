#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdio.h>
#include <stdlib.h>

// float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);

// // implemention of matmul_blocking with blocking/tiling
// float **matmul_blocking(float **A, float **B, int A_rows, int A_cols,int B_rows, int B_cols);

// implemention of matmul_sparse with sparse matrix
float **matmul_sparse(float **A, float **B, int A_rows, int A_cols,int B_rows, int B_cols);
#endif /* MATRIX_OPS_H */