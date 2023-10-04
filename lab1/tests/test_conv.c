#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

// free the convolution results
void free_result(float ***result, int numFilters, int outputSize) {
    for (int f = 0; f < numFilters; f++) {
        for (int r = 0; r < outputSize; r++) {
            free(result[f][r]);
        }
        free(result[f]);
    }
    free(result);
}
// free the image data
void free_image(float ***image, int imageSize, int numChannels) {
    for (int k = 0; k < numChannels; k++) {
        for (int i = 0; i < imageSize; i++) {
            free(image[k][i]);
        }
        free(image[k]);
    }
    free(image);
}

void test_conv(void) {
    // Input
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
    
    int numFilters = 1;
    int inputSize = 5;
    int kernelSize = 3;
    float biasData[1] = {0.1}; // Setting your bias values

    float ****kernel = malloc(numFilters * sizeof(*kernel));
    for (int f = 0; f < numFilters; f++) {
        kernel[f] = malloc(numChannels * sizeof(*kernel[f]));
        for (int k = 0; k < numChannels; k++) {
            kernel[f][k] = malloc(kernelSize * sizeof(*kernel[f][k]));
            for (int i = 0; i < kernelSize; i++) {
                kernel[f][k][i] = malloc(kernelSize * sizeof(*kernel[f][k][i]));
                for (int j = 0; j < kernelSize; j++) {
                    kernel[f][k][i][j] = kernel_data[f][k][i][j];
                }
            }
        }
    }

    
    float ***result = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);

    // Expected output
    float expected_values[1][3][3] = {
        {
            {2.1, 6.1, 2.1},
            {2.1, 8.1, 2.1},
            {2.1, 6.1, 2.1}
        }
    };

    // Checking if the computed output matches the expected output
    for (int f = 0; f < numFilters; f++) {
        for (int r = 0; r < 3; r++) { 
            for (int c = 0; c < 3; c++) { 
                TEST_ASSERT_FLOAT_WITHIN(.1, expected_values[f][r][c], result[f][r][c]);
            }
        }
    }

    // Free memory
    free_result(result, numFilters, 3); 
    free_image(image, 5, numChannels);

    for (int f = 0; f < numFilters; f++) {
        for (int k = 0; k < numChannels; k++) {
            for (int i = 0; i < kernelSize; i++) {
                free(kernel[f][k][i]);
            }
            free(kernel[f][k]);
        }
        free(kernel[f]);
    }
    free(kernel);
}


// test two 
void test_conv_edge_detection(void) {
    // Input
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
                {-1, -1, -1},
                {-1, 8, -1},
                {-1, -1, -1}
            }
        }
    };
    
    int numFilters = 1;
    int inputSize = 5;
    int kernelSize = 3;
    float biasData[1] = {0.0};

    float ****kernel = malloc(numFilters * sizeof(*kernel));
    for (int f = 0; f < numFilters; f++) {
        kernel[f] = malloc(numChannels * sizeof(*kernel[f]));
        for (int k = 0; k < numChannels; k++) {
            kernel[f][k] = malloc(kernelSize * sizeof(*kernel[f][k]));
            for (int i = 0; i < kernelSize; i++) {
                kernel[f][k][i] = malloc(kernelSize * sizeof(*kernel[f][k][i]));
                for (int j = 0; j < kernelSize; j++) {
                    kernel[f][k][i][j] = kernel_data[f][k][i][j];
                }
            }
        }
    }

    // Calling the convolution function
    float ***result = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);

    // Expected output
    float expected_values[1][3][3] = {
    {
        {6,  4, 6},
        {4, 0, 4},
        {6,  4, 6}
    }
    };


    // Checking if the computed output matches the expected output
    for (int f = 0; f < numFilters; f++) {
        for (int r = 0; r < 3; r++) { 
            for (int c = 0; c < 3; c++) { 
                TEST_ASSERT_FLOAT_WITHIN(.1, expected_values[f][r][c], result[f][r][c]);
            }
        }
    }

    // Free memory
    free_result(result, numFilters, 3); 
    free_image(image, 5, numChannels);

    // Free kernel
    for (int f = 0; f < numFilters; f++) {
        for (int k = 0; k < numChannels; k++) {
            for (int i = 0; i < kernelSize; i++) {
                free(kernel[f][k][i]);
            }
            free(kernel[f][k]);
        }
        free(kernel[f]);
    }
    free(kernel);
}

void test_conv_lateral_edge_detection(void) {
    // Input
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
                {1, 0, -1},
                {2, 0, -2},
                {1, 0, -1}
            }
        }
    };
    
    int numFilters = 1;
    int inputSize = 5;
    int kernelSize = 3;
    float biasData[1] = {0.0};

    float ****kernel = malloc(numFilters * sizeof(*kernel));
    for (int f = 0; f < numFilters; f++) {
        kernel[f] = malloc(numChannels * sizeof(*kernel[f]));
        for (int k = 0; k < numChannels; k++) {
            kernel[f][k] = malloc(kernelSize * sizeof(*kernel[f][k]));
            for (int i = 0; i < kernelSize; i++) {
                kernel[f][k][i] = malloc(kernelSize * sizeof(*kernel[f][k][i]));
                for (int j = 0; j < kernelSize; j++) {
                    kernel[f][k][i][j] = kernel_data[f][k][i][j];
                }
            }
        }
    }

    // Calling the convolution function
    float ***result = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);

    // Expected output
    float expected_values[1][3][3] = {
        {
            {0,0, 2},
            {0, 0, 2},
            {0, 0, 2}
        }
    };


    // Checking if the computed output matches the expected output
    for (int f = 0; f < numFilters; f++) {
        for (int r = 0; r < 3; r++) { 
            for (int c = 0; c < 3; c++) { 
                TEST_ASSERT_FLOAT_WITHIN(.1, expected_values[f][r][c], result[f][r][c]);
            }
        }
    }

    // Free memory
    free_result(result, numFilters, 3); 
    free_image(image, 5, numChannels);

    // Free kernel
    for (int f = 0; f < numFilters; f++) {
        for (int k = 0; k < numChannels; k++) {
            for (int i = 0; i < kernelSize; i++) {
                free(kernel[f][k][i]);
            }
            free(kernel[f][k]);
        }
        free(kernel[f]);
    }
    free(kernel);
}