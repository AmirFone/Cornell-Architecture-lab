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

    
    float **C = matmul(A, B, 2, 2, 2, 2);

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
    float **C = matmul(A, B, 2, 3, 2, 2);

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

    float **C = matmul(A, B, 3, 3, 3, 3);

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