#include "linear.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0)
    {
    return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    for (int i = 0; i < outputSize; i++)
    {
        output[i] = 0.0; // Initializing the output for this neuron to 0

        for (int j = 0; j < inputSize; j++)
        {
            // applying the weights
            output[i] += weights[i][j] * input[j];
        }

        output[i] += biases[i];
    }


    return output;
}


//========= code used for Profiling function (do not modify) ==============================
// int main() {
//     srand(time(NULL));


//     int inputSize = 1000;   
//     int outputSize = 1000;  

    
//     float *input = (float *)malloc(inputSize * sizeof(float));
//     for (int i = 0; i < inputSize; i++) {
        
//         input[i] = (float)(rand() % 10);
//     }


//     float **weights = (float **)malloc(outputSize * sizeof(float *));
//     float *biases = (float *)malloc(outputSize * sizeof(float));

//     for (int i = 0; i < outputSize; i++) {
//         weights[i] = (float *)malloc(inputSize * sizeof(float));
//         for (int j = 0; j < inputSize; j++) {

//             weights[i][j] = (float)(rand() % 10);
//         }


//         biases[i] = (float)(rand() % 10);
//     }


//     float *output = linear(input, weights, biases, inputSize, outputSize);



//     return 0;
// }
