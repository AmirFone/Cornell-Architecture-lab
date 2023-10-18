#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"


void test_matmul_square_matrices(void)
{
    // Setup
    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(2 * sizeof(float));
        A[i][0] = 1.0;
        A[i][1] = 2.0;
    }

    float **B = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        B[i] = (float *)malloc(2 * sizeof(float));
        B[i][0] = 3.0;
        B[i][1] = 4.0;
    }

    
    float **C = matmul_blocking(A, B, 2, 2, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_EQUAL_FLOAT(9.0, C[0][0], __LINE__, "Expected 9.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(12.0, C[0][1], __LINE__, "Expected 12.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(9.0, C[1][0], __LINE__, "Expected 9.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(12.0, C[1][1], __LINE__, "Expected 12.0");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);  // Don't forget to free the result matrix C
}

void test_matmul_incompatible_dimensions(void)
{

    // Setup
    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
        A[i][0] = 1.0;
        A[i][1] = 2.0;
        A[i][2] = 3.0;
    }

    float **B = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        B[i] = (float *)malloc(2 * sizeof(float));
        B[i][0] = 4.0;
        B[i][1] = 5.0;
    }

    // Run function under test
    float **C = matmul_blocking(A, B, 2, 3, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
}


void test_matmul_three_by_three_matrices(void)
{
    // Setup
    float **A = (float **)malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
        A[i][0] = 4.0;
        A[i][1] = 7.0;
        A[i][2] = 2.0;
    }

    float **B = (float **)malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++)
    {
        B[i] = (float *)malloc(3 * sizeof(float));
        B[i][0] = 3.0;
        B[i][1] = 6.0;
        B[i][2] = 1.0;
    }

    float **C = matmul_blocking(A, B, 3, 3, 3, 3);

    // Check expectations
    UNITY_TEST_ASSERT_EQUAL_FLOAT(39.0, C[0][0], __LINE__, "Expected 39.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(78.0, C[0][1], __LINE__, "Expected 78.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(13.0, C[0][2], __LINE__, "Expected 13.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(39.0, C[1][0], __LINE__, "Expected 39.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(78.0, C[1][1], __LINE__, "Expected 78.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(13.0, C[1][2], __LINE__, "Expected 13.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(39.0, C[2][0], __LINE__, "Expected 39.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(78.0, C[2][1], __LINE__, "Expected 78.0");
    UNITY_TEST_ASSERT_EQUAL_FLOAT(13.0, C[2][2], __LINE__, "Expected 13.0");

    // Cleanup
    for (int i = 0; i < 3; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);  
}


void test_matmul_five_by_five_matrices(void) {
    // Setup
    float A[5][5] = {{0,0,3,7,76}, {76,	7,67,67,6}, {76,	7,	67,	67,	 67},{ 6,	7,	67,	 6,	 76},{76,	7,	77,	76,	767}};
    float B[5][5] = {{0,67,67,67,67}, {67,	67,	 6,	 7,67}, {67,	 7,	 7,	 0,	 0},{787, 8,0,0,78},8,	70,	 0,	 0,	 0};
    float a[5][5]={{6318.000000, 5397.000000, 21.000000, 0.000000, 546.000000}, {57735.000000, 6986.000000, 5603.000000, 5141.000000, 10787.000000}, {58223.000000,11256.000000, 5603.000000, 5141.000000, 10787.000000},{10288,6708,913,451,1339},{71576,60398,5673,5141,11489}}; 
    float *pA[] = {&A[0][0], &A[1][0], &A[2][0], &A[3][0], &A[4][0]};
    float *pB[] = {&B[0][0], &B[1][0], &B[2][0], &B[3][0], &B[4][0]};
    float *ans[]={&a[0][0], &a[1][0], &a[2][0], &a[3][0], &a[4][0]};
    float **result = matmul(pA, pB, 5, 5, 5, 5);

    // Print the result
    // printf("Result of matrix multiplication is :\n");
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            // printf("%f ", result[i][j]);
            UNITY_TEST_ASSERT_EQUAL_FLOAT(a[i][j], result[i][j], __LINE__, "Not What Expected");
        }
        // printf("\n");
    }

    // Free the memory allocated for the result array
    for (int i=0; i<5; i++) {
        free(result[i]);
    }
    free(result);
}