#include <assert.h>
#include "conv.h"
#include "linear.h" 
#include "matrix_ops.h"
#include "functional.h"

int main() {

  // Test convolution
  float image_data[1][5][5] = {
    {
      {0, 0, 0, 0, 0}, 
      {0, 1, 1, 1, 0},
      {0, 1, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0}
    }
  };

  int numChannels = 1;
  float ***image = init_image(image_data, 5, numChannels);

  float kernel_data[1][1][3][3] = {
    {
      { 
        {1, 0, 1},
        {2, 0, 2},
        {1, 0, 1}  
      }
    }
  };

  float ***output = convolution(image, numChannels, kernel_data, NULL, 1, 5, 3);

  float expected_values[1][3][3] = {
    {
      {2, 6, 2},
      {2, 8, 2}, 
      {2, 6, 2}
    }
  };

  for(int i=0; i<1; i++) {
    for(int j=0; j<3; j++) {
      for(int k=0; k<3; k++) {
        assert(output[i][j][k] == expected_values[i][j][k]);
      }
    }
  }

  // Test linear
  float input[] = {1.0, 2.0, 3.0};
  
  float *weights[] = {(float[]){1.0, 2.0, 3.0}, (float[]){4.0, 5.0, 6.0}};
  
  float biases[] = {0.1, 0.2};

  float *linear_output = linear(input, weights, biases, 3, 2);

  assert(linear_output[0] == 14.1);
  assert(linear_output[1] == 32.2);

  // Test matrix multiplication
  float A[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
  float B[2][2] = {{2.0, 0.0}, {1.0, 2.0}};

  float **C = matmul(A, B, 2, 2, 2, 2);

  assert(C[0][0] == 4.0);
  assert(C[0][1] == 4.0);
  assert(C[1][0] == 10.0);
  assert(C[1][1] == 8.0);

  return 0;
}