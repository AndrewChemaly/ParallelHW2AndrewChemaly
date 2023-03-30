
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** allocate_matrix(int size)
{
    double* vals = (double*)malloc(size * size * sizeof(double));

    double** ptrs = (double**)malloc(size * sizeof(double*));

    int i;
    for (i = 0; i < size; ++i) {
        ptrs[i] = &vals[i * size];
    }

    return ptrs;
}

void init_matrix(double** matrix, int size)
{
    int i, j;

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            matrix[i][j] = 1.0;
        }
    }
}

void print_matrix(double** matrix, int size)
{
    int i, j;

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size - 1; ++j) {
            printf("%lf, ", matrix[i][j]);
        }
        printf("%lf", matrix[i][j]);
        putchar('\n');
    }
}

int main(int argc, char* argv[])
{
    clock_t start = clock();
    double** matrix1, ** matrix2, ** matrix3;
    int size, i, j, k;
    double sum = 0;
    double exectime;

    if (argc != 2) {
        fprintf(stderr, "%s <matrix size>\n", argv[0]);
        return -1;
    }

    size = atoi(argv[1]);

    matrix1 = allocate_matrix(size);
    matrix2 = allocate_matrix(size);
    matrix3 = allocate_matrix(size);

    init_matrix(matrix1, size);
    init_matrix(matrix2, size);

    if (size <= 10) {
        printf("Matrix 1:\n");
        print_matrix(matrix1, size);
        printf("Matrix 2:\n");
        print_matrix(matrix2, size);
    }

    for (i = 0; i < size; ++i) { 
        for (j = 0; j < size; ++j) { 
            sum = 0; 
 
            for (k = 0; k < size; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            matrix3[i][j] = sum;
        }
    }

    if (size <= 10) {
        printf("Matrix 3:\n");
        print_matrix(matrix3, size);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


    printf("Sequential Execution time:%.3lf sec\n",
        time_spent);
    return 0;
}