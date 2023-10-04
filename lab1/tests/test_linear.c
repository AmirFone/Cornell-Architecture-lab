#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_linear.h"

void test_linear() {
  
  // Test 1
  {
      // Input
      float input[] = {1.0, 2.0, 3.0};

      // Weights
      float **weights = (float **)malloc(2 * sizeof(float *));
      for (int i = 0; i < 2; i++) {
          weights[i] = (float *)malloc(3 * sizeof(float));
      }

    
      weights[0][0] = -1.0;
      weights[0][1] = -2.0;
      weights[0][2] = -3.0;
      weights[1][0] = -4.0;
      weights[1][1] = -5.0;
      weights[1][2] = -6.0;

      // Biases
      float biases[] = {-0.1, -0.2};

      float expected_output[] = {-14.1, -32.2};

      // Compute output
      float *output = linear(input, weights, biases, 3, 2);

      // Check output
      TEST_ASSERT_FLOAT_WITHIN(0.001, expected_output[0], output[0]);
      TEST_ASSERT_FLOAT_WITHIN(0.001, expected_output[1], output[1]);

      // Clean up
      free(output);
  
      for (int i = 0; i < 2; i++) {
          free(weights[i]);
      }
      free(weights);
  }
  

}

  // Test 2
 void test_linear_two() {
      // Input
      float input[] = {2.0, 3.0, 4.0};

      // Weights
      float **weights = (float **)malloc(2 * sizeof(float *));
      for (int i = 0; i < 2; i++) {
          weights[i] = (float *)malloc(3 * sizeof(float));
      }

      // filling the weights array with some values
      weights[0][0] = 0.5;
      weights[0][1] = -0.5;
      weights[0][2] = 1.0;
      weights[1][0] = 2.0;
      weights[1][1] = -1.0;
      weights[1][2] = -0.5;

      // Biases
      float biases[] = {0.0, 0.5};

      // Expected output: (input * weights + biases)
      float expected_output[] = {3.5, -0.5};

      // Compute output
      float *output = linear(input, weights, biases, 3, 2);

      // Check output
      TEST_ASSERT_FLOAT_WITHIN(0.001, expected_output[0], output[0]);
      TEST_ASSERT_FLOAT_WITHIN(0.001, expected_output[1], output[1]);

      // Clean up
      free(output);

      // Free the allocated memory for weights
      for (int i = 0; i < 2; i++) {
          free(weights[i]);
      }
      free(weights);
  }

void test_linear_zero_all() {
    // printf("test_linear_zero_all\n");
  
  // Input 
  float input[] = {0.0, 0.0, 0.0};

  // Weights
  float **weights = (float **)malloc(2 * sizeof(float *));
  for (int i = 0; i < 2; i++) {
      weights[i] = (float *)malloc(3 * sizeof(float));
  }
  
    // filling the weights array with some values
  weights[0][0] = 0.0;
  weights[0][1] = 0.0;
  weights[0][2] = 0.0;
  weights[1][0] = 0.0;
  weights[1][1] = 0.0;
  weights[1][2] = 0.0;

  // Biases
  float biases[] = {0.0, 0.0};
  
  // Expected output: (input * weights + biases)
  float expected_output[] = {0.0, 0.0};

  // computing outputs 
  float *output = linear(input, weights, biases, 3, 2);

  
  TEST_ASSERT_FLOAT_WITHIN(0.001, expected_output[0], output[0]);
  TEST_ASSERT_FLOAT_WITHIN(0.001, expected_output[1], output[1]);
  

  free(output);
  
  // Free the allocated memory for weights
  for (int i = 0; i < 2; i++) {
      free(weights[i]);
  }
  free(weights);
}