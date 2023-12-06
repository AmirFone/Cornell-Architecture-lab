#include "nn.h"
#include <stdlib.h>

#define CONV_OUTPUT_CHANNELS 32 // Replace 32 with the actual constant if different

float *flatten(float ***input, int inputSize, int depth)
{
    if (inputSize <= 0 || depth <= 0)
    {
        return NULL;
    }

    int outputSize = inputSize * inputSize * depth;
    float *output = (float *)malloc(outputSize * sizeof(float));
    if (!output) return NULL; // Check for malloc failure

    float *outPtr = output;
    for (int k = 0; k < depth; k++)
    {
        for (int i = 0; i < inputSize; i++)
        {
            for (int j = 0; j < inputSize; j++)
            {
                *outPtr++ = input[k][i][j];
            }
        }
    }

    return output;
}

void destroyConvOutput(float ***convOutput, int convOutputSize)
{
    for (int i = 0; i < CONV_OUTPUT_CHANNELS; i++)
    {
        for (int j = 0; j < convOutputSize; j++)
        {
            free(convOutput[i][j]);
        }
        free(convOutput[i]);
    }
    free(convOutput);
}

int forwardPass(float ***image, int numChannels, float ****conv1WeightsData, float **fc1WeightsData, float **fc2WeightsData, float *conv1BiasData, float *fc1BiasData, float *fc2BiasData)
{
    // 1. Perform the convolution operation
    float ***convOutput = convolution_im2col(image, numChannels, conv1WeightsData, conv1BiasData, CONV_OUTPUT_CHANNELS, 28, 3);

    // 2. Flatten the output
    float *fcInput = flatten(convOutput, 26, CONV_OUTPUT_CHANNELS);
    if (!fcInput) {
        destroyConvOutput(convOutput, 26); // Free memory in case of failure
        return -1; // Indicate failure
    }

    // 3. Perform the fully connected operations
    float *fcOutput1 = linear(fcInput, fc1WeightsData, fc1BiasData, 26 * 26 * CONV_OUTPUT_CHANNELS, 128);
    applyRelu(fcOutput1, 128);
    float *fcOutput2 = linear(fcOutput1, fc2WeightsData, fc2BiasData, 128, 10);

    // 4. Apply the final softmax activation
    float *softmaxOutput = softmax(fcOutput2, 10);

    // 5. Make predictions
    int predictedClass = predict(softmaxOutput, 10);

    // Clean up the memory usage
    destroyConvOutput(convOutput, 26);
    free(fcInput);
    free(fcOutput1);
    free(fcOutput2);
    free(softmaxOutput);

    return predictedClass;
}

inline int predict(float *probabilityVector, int numClasses) // inlined for potential performance improvement
{
    int predictedClass = 0;
    float maxProbability = probabilityVector[0];

    for (int i = 1; i < numClasses; i++)
    {
        if (probabilityVector[i] > maxProbability)
        {
            maxProbability = probabilityVector[i];
            predictedClass = i;
        }
    }
    return predictedClass;
}
