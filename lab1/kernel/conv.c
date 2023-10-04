#include "conv.h"
#include "functional.h"
#include <time.h>

float ***convolution(float ***image, int numChannels, float ****kernel, float *biasData, int numFilters, int inputSize, int kernelSize)
{
    int outputSize = inputSize - kernelSize + 1;

    float ***convOutput = malloc(numFilters * sizeof(*convOutput));
    for (int i = 0; i < numFilters; i++)
    {
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++)
        {
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
            for (int k = 0; k < outputSize; k++)
            {
                convOutput[i][j][k] = 0.0; // initialize to 0
            }
        }
    }

    // Performing the convolution operation
    for (int f = 0; f < numFilters; f++) {
        for (int r = 0; r < outputSize; r++) {
            for (int c = 0; c < outputSize; c++) {
                for (int i = 0; i < kernelSize; i++) {
                    for (int j = 0; j < kernelSize; j++) {
                        for (int k = 0; k < numChannels; k++) {
                            // Each filter is dot-multiplied with a patch of the image, and the result is summed in the output.
                            convOutput[f][r][c] += image[k][r + i][c + j] * kernel[f][k][i][j];
                        }
                    }
                }
                // Adding the bias
                convOutput[f][r][c] += biasData[f];
                // ReLU activation
                convOutput[f][r][c] = relu(convOutput[f][r][c]);                
            }
        }
    }

    return convOutput;
}

//========= code used for Profiling function (do not modify) ==============================
// int main() {
//     srand(time(NULL));
//     int numChannels = 3; 
//     int numFilters = 2;  

    
//     int inputSize = 1000; 
//     int kernelSize = 3;   

    
//     float ***inputImage = malloc(numChannels * sizeof(*inputImage));
//     for (int k = 0; k < numChannels; k++) {
//         inputImage[k] = malloc(inputSize * sizeof(*inputImage[k]));
//         for (int i = 0; i < inputSize; i++) {
//             inputImage[k][i] = malloc(inputSize * sizeof(*inputImage[k][i]));
//             for (int j = 0; j < inputSize; j++) {
                
//                 inputImage[k][i][j] = (float)(rand() % 10);
//             }
//         }
//     }

    
//     float ****kernels = malloc(numFilters * sizeof(*kernels));
//     for (int f = 0; f < numFilters; f++) {
//         kernels[f] = malloc(numChannels * sizeof(*kernels[f]));
//         for (int k = 0; k < numChannels; k++) {
//             kernels[f][k] = malloc(kernelSize * sizeof(*kernels[f][k]));
//             for (int i = 0; i < kernelSize; i++) {
//                 kernels[f][k][i] = malloc(kernelSize * sizeof(*kernels[f][k][i]));
//                 for (int j = 0; j < kernelSize; j++) {
                    
//                     kernels[f][k][i][j] = (float)(rand() % 10);
//                 }
//             }
//         }
//     }

    
//     float biasData[] = {0.1, -0.1};

    
//     float ***convolutionResult = convolution(inputImage, numChannels, kernels, biasData, numFilters, inputSize, kernelSize);

    
//     if (convolutionResult == NULL) {
        
//         return 1;
//     }

    
//     for (int k = 0; k < numChannels; k++) {
//         for (int i = 0; i < inputSize; i++) {
//             free(inputImage[k][i]);
//         }
//         free(inputImage[k]);
//     }
//     free(inputImage);

//     for (int f = 0; f < numFilters; f++) {
//         for (int k = 0; k < numChannels; k++) {
//             for (int i = 0; i < kernelSize; i++) {
//                 free(kernels[f][k][i]);
//             }
//             free(kernels[f][k]);
//         }
//         free(kernels[f]);
//     }
//     free(kernels);

//     for (int f = 0; f < numFilters; f++) {
//         for (int r = 0; r < inputSize - kernelSize + 1; r++) {
//             free(convolutionResult[f][r]);
//         }
//         free(convolutionResult[f]);
//     }
//     free(convolutionResult);

//     return 0;
// }
