#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
float relu(float x)
{
    //  If "x > 0" is true "x" is returned else 0 is returned
    return x > 0 ? x : 0;
}

void applyRelu(float *input, int inputSize)
{
    for (int i = 0; i < inputSize; i++)
    {
        input[i] = relu(input[i]);
    }
}

float *softmax(float *input, int inputSize)
{
    float *softmaxOutput = malloc(inputSize * sizeof(*softmaxOutput));
    if (softmaxOutput == NULL) return NULL; 

    // Calculating the sum of exponentials of the input values
    float expSum = 0.0;
    for (int i = 0; i < inputSize; i++) {
        softmaxOutput[i] = exp(input[i]);
        expSum += softmaxOutput[i];
    }

    // Normalizing the values
    for (int i = 0; i < inputSize; i++) {
        softmaxOutput[i] /= expSum;
    }

    return softmaxOutput;

}


//========= code used for Profiling function (do not modify) ==============================
// int main() {
//     srand(time(NULL));


//     int inputSize = 100000;   

    
//     float *input = (float *)malloc(inputSize * sizeof(float));
//     for (int i = 0; i < inputSize; i++) {
        
//         input[i] = (float)(rand() % 10);
//     }

    
//     float *output = (float *)malloc(inputSize * sizeof(float));
//     for (int i = 0; i < inputSize; i++) {
//         output[i] = relu(input[i]);
//     }

    

//     return 0;
// }