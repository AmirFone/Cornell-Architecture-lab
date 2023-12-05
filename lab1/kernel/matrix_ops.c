#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 128 //tile was constant for all the tests
#define NUM_THREADS 8// Adjust to your system used 4,6,8 threads
// const char filename[] = "profiling_750x500_thread_4.csv";  // name of the csv file used for profiling
int size =500; // size of the Square matrix used different variations of 50,100,120,200,500,750,1000

float **matmul_multithread(float **MatrixA, float **MatrixB, int RowsMatrixA, int ColsMatrixA, int RowsMatrixB, int ColsMatrixB) {
    //makes it easer to pass the args to threaded function
    typedef struct {
        float **MatrixA;
        float **MatrixB;
        float **MatrixC;
        int RowsMatrixA;
        int ColsMatrixA;
        int ColsMatrixB;
        int TileRowStart;
        int TileRowEnd;
    } MatrixThreadArgs;

    void *matrixMultiplicationTileThread(void *arg) {
        MatrixThreadArgs *threadData = (MatrixThreadArgs *)arg;
        int endTileRow = threadData->TileRowEnd < threadData->RowsMatrixA ? threadData->TileRowEnd : threadData->RowsMatrixA;
        for (int tileRow = threadData->TileRowStart; tileRow < endTileRow; tileRow += TILE_SIZE) {
            for (int tileCol = 0; tileCol < threadData->ColsMatrixB; tileCol += TILE_SIZE) {
                for (int tileDepth = 0; tileDepth < threadData->ColsMatrixA; tileDepth += TILE_SIZE) {
                    for(int row = tileRow; row < tileRow + TILE_SIZE && row < endTileRow; row++) {
                        for(int col = tileCol; col < tileCol + TILE_SIZE && col < threadData->ColsMatrixB; col++) {
                            float accumulator = 0.0;
                            for(int depth = tileDepth; depth < tileDepth + TILE_SIZE && depth < threadData->ColsMatrixA; depth++) {
                                accumulator += threadData->MatrixA[row][depth] * threadData->MatrixB[depth][col];
                            }
                            threadData->MatrixC[row][col] += accumulator;
                        }
                    }
                }
            }
        }
        pthread_exit(NULL);
    }
    
    // compatibility check
    if (ColsMatrixA != RowsMatrixB) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **MatrixC = (float **)malloc(RowsMatrixA * sizeof(float *));
    for (int row = 0; row < RowsMatrixA; row++) {
        MatrixC[row] = (float *)calloc(ColsMatrixB, sizeof(float));
    }

    pthread_t threads[NUM_THREADS];
    MatrixThreadArgs threadArgs[NUM_THREADS];
    int tileRowsPerThread = (RowsMatrixA + NUM_THREADS - 1) / NUM_THREADS;
    for (int threadIndex = 0; threadIndex < NUM_THREADS; threadIndex++) {
        threadArgs[threadIndex].MatrixA = MatrixA;
        threadArgs[threadIndex].MatrixB = MatrixB;
        threadArgs[threadIndex].MatrixC = MatrixC;
        threadArgs[threadIndex].RowsMatrixA = RowsMatrixA;
        threadArgs[threadIndex].ColsMatrixA = ColsMatrixA;
        threadArgs[threadIndex].ColsMatrixB = ColsMatrixB;
        threadArgs[threadIndex].TileRowStart = threadIndex * tileRowsPerThread;
        threadArgs[threadIndex].TileRowEnd = (threadIndex + 1) * tileRowsPerThread;
        if (pthread_create(&threads[threadIndex], NULL, matrixMultiplicationTileThread, (void *)&threadArgs[threadIndex]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int threadIndex = 0; threadIndex < NUM_THREADS; threadIndex++) {
        if (pthread_join(threads[threadIndex], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return MatrixC;
}




//========= code used for Profiling function (do not modify) ==============================

// int main() {
//     srand(time(NULL));
//     int A_rows = size;  
//     int A_cols = size;  
//     int B_rows = size;  
//     int B_cols = size;

//     float **matrixA = (float **)malloc(A_rows * sizeof(float *));
//     for (int i = 0; i < A_rows; i++) {
//         matrixA[i] = (float *)malloc(A_cols * sizeof(float));
//         for (int j = 0; j < A_cols; j++) {

//             matrixA[i][j] = (float)(rand() % 10);
//         }
//     }


//     float **matrixB = (float **)malloc(B_rows * sizeof(float *));
//     for (int i = 0; i < B_rows; i++) {
//         matrixB[i] = (float *)malloc(B_cols * sizeof(float));
//         for (int j = 0; j < B_cols; j++) {

//             matrixB[i][j] = (float)(rand() % 10);
//         }
//     }
    
//     // Running function and timing it and saving that to a csv file
//     // FILE *csvFile = fopen(filename, "w");
//     // if (!csvFile) {
//     //     perror("Failed to open CSV file for writing");
//     //     return 1;
//     // }
//     // fprintf(csvFile, "Iteration,Wall-Clock Time (ms)\n");

//     for (int i = 0; i < 5; i++) {
//         // clock_t start_time = clock();
//         float **result = matmul_multithread(matrixA,matrixB,A_rows, A_cols, B_rows, B_cols);
//         // clock_t end_time = clock();

//         // if (result == NULL) {
//         //     perror("Matrix multiplication error");
//         //     return 1;
//         // }

//         // Calculate the elapsed time in milliseconds
//         // double elapsed_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;

//         // printf("Iteration %d: Wall-Clock Time %.2f ms\n", i, elapsed_time);

//         // fprintf(csvFile, "%d,%.2f\n", i, elapsed_time);

//         // Free result matrix (replace with your cleanup code)
//         free(result);
//     }
//     // fclose(csvFile);
//     return 0;
// }