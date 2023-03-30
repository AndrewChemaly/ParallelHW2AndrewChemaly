//Andrew Chemaly Parallel HW2
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MATRIX_SIZE 4096
#define NUM_THREADS 8
#define BLOCK_SIZE (MATRIX_SIZE / NUM_THREADS)

typedef struct {
    int start_row;
    int end_row;
} thread_data;

int A[MATRIX_SIZE][MATRIX_SIZE];
int B[MATRIX_SIZE][MATRIX_SIZE];
int C[MATRIX_SIZE][MATRIX_SIZE];

void* matrix_multiply(void* arg) {  
    thread_data* data = (thread_data*)arg;
    int i, j, k;

    for (i = data->start_row; i < data->end_row; ++i) {
        for (j = 0; j < MATRIX_SIZE; ++j) {
            C[i][j] = 0;    
            for (k = 0; k < MATRIX_SIZE; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return NULL;
}

int main() {
    clock_t start = clock();

    int i, j;
    pthread_t threads[NUM_THREADS];
    thread_data thread_data_array[NUM_THREADS];

    // Initialize matrices
    for (i = 0; i < MATRIX_SIZE; ++i) {
        for (j = 0; j < MATRIX_SIZE; ++j) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }



    // Create threads
    for (i = 0; i < NUM_THREADS; ++i) {
        thread_data_array[i].start_row = i * BLOCK_SIZE;
        thread_data_array[i].end_row = (i + 1) * BLOCK_SIZE;

        pthread_create(&threads[i], NULL, matrix_multiply, &thread_data_array[i]);
    }

    // Join threads
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


    printf("Number of threads: %d\tExecution time:%.3lf sec\n",
        NUM_THREADS, time_spent);
    return 0;
}