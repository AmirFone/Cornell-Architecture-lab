#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_functional.h"
#include <float.h>


void test_softmax(void) {
    float input1[] = {1.0, 2.0, 3.0};
    float input2[] = {0.0, -1.0, 1.0};
    float input3[] = {10.0, 20.0, 30.0};
    float *inputs[] = {input1, input2, input3};
    
    for(int j = 0; j < 3; j++) {
        float *output = softmax(inputs[j], 3);
        float sum = 0.0;

        // Checking that the sum of the output is around 1
        for (int i = 0; i < 3; i++) {
            sum += output[i];
        }

        TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);

        int maxInputIndex = 0;
        int maxOutputIndex = 0;

        for (int i = 1; i < 3; i++) {
            if (inputs[j][i] > inputs[j][maxInputIndex]) {
                maxInputIndex = i;
            }
            if (output[i] > output[maxOutputIndex]) {
                maxOutputIndex = i;
            }
        }

        TEST_ASSERT_EQUAL_INT(maxInputIndex, maxOutputIndex);

        // Cleanup
        free(output);
    }
}


void test_relu(void) {
    float inputs[] = {3.0f, 0.0f, -3.0f};
    float expected_outputs[] = {3.0f, 0.0f, 0.0f};
    int test_cases = sizeof(inputs)/sizeof(inputs[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(inputs[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
    }
}


