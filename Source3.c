//Andrew Chemaly Parallel HW2

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MATRIX_SIZE 4096
#define NUM_THREADS 8

int A[MATRIX_SIZE][MATRIX_SIZE];
int B[MATRIX_SIZE][MATRIX_SIZE];
int C[MATRIX_SIZE][MATRIX_SIZE];

int main() {
    clock_t start = clock();


    int i, j, k;

    // Initialize matrices
    for (i = 0; i < MATRIX_SIZE; ++i) {
        for (j = 0; j < MATRIX_SIZE; ++j) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }



    // Set number of threads
    omp_set_num_threads(NUM_THREADS);

#pragma omp parallel for private(j, k)
    for (i = 0; i < MATRIX_SIZE; ++i) {
        for (j = 0; j < MATRIX_SIZE; ++j) {
            C[i][j] = 0;
            for (k = 0; k < MATRIX_SIZE; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


    printf("Number of threads: %d\tExecution time:%.3lf sec\n",
        NUM_THREADS, time_spent);

    return 0;
}