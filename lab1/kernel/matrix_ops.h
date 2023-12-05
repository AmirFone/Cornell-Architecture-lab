#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdio.h>
#include <stdlib.h>

// // implemention of matmul_multithread with blocking/tiling
float **matmul_multithread(float **A, float **B, int A_rows, int A_cols,int B_rows, int B_cols);

#endif /* MATRIX_OPS_H */