#include <stdio.h>
#include <stdlib.h>

// Allocate n x n matrix
int **allocateMatrix(int n)
{
    int **matrix = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        matrix[i] = (int *)calloc(n, sizeof(int));

    return matrix;
}

// Free matrix
void freeMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

// Add two matrices
void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices
void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen Matrix Multiplication
void strassen(int **A, int **B, int **C, int n)
{
    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Create submatrices
    int **A11 = allocateMatrix(k);
    int **A12 = allocateMatrix(k);
    int **A21 = allocateMatrix(k);
    int **A22 = allocateMatrix(k);

    int **B11 = allocateMatrix(k);
    int **B12 = allocateMatrix(k);
    int **B21 = allocateMatrix(k);
    int **B22 = allocateMatrix(k);

    // Divide A and B into four parts
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Temporary matrices
    int **M1 = allocateMatrix(k);
    int **M2 = allocateMatrix(k);
    int **M3 = allocateMatrix(k);
    int **M4 = allocateMatrix(k);
    int **M5 = allocateMatrix(k);
    int **M6 = allocateMatrix(k);
    int **M7 = allocateMatrix(k);

    int **T1 = allocateMatrix(k);
    int **T2 = allocateMatrix(k);

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    // M2 = (A21 + A22)B11
    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    // M3 = A11(B12 - B22)
    subtractMatrix(B12, B22, T2, k);
    strassen(A11, T2, M3, k);

    // M4 = A22(B21 - B11)
    subtractMatrix(B21, B11, T2, k);
    strassen(A22, T2, M4, k);

    // M5 = (A11 + A12)B22
    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    // M6 = (A21 - A11)(B11 + B12)
    subtractMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    // M7 = (A12 - A22)(B21 + B22)
    subtractMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    // C11 = M1 + M4 - M5 + M7
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] =
                M1[i][j] + M4[i][j]
                - M5[i][j] + M7[i][j];
        }
    }

    // C12 = M3 + M5
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j + k] = M3[i][j] + M5[i][j];
        }
    }

    // C21 = M2 + M4
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i + k][j] = M2[i][j] + M4[i][j];
        }
    }

    // C22 = M1 - M2 + M3 + M6
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i + k][j + k] =
                M1[i][j] - M2[i][j]
                + M3[i][j] + M6[i][j];
        }
    }

    // Free memory
    freeMatrix(A11, k);
    freeMatrix(A12, k);
    freeMatrix(A21, k);
    freeMatrix(A22, k);

    freeMatrix(B11, k);
    freeMatrix(B12, k);
    freeMatrix(B21, k);
    freeMatrix(B22, k);

    freeMatrix(M1, k);
    freeMatrix(M2, k);
    freeMatrix(M3, k);
    freeMatrix(M4, k);
    freeMatrix(M5, k);
    freeMatrix(M6, k);
    freeMatrix(M7, k);

    freeMatrix(T1, k);
    freeMatrix(T2, k);
}

// Print matrix
void printMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", A[i][j]);

        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter size of matrix: ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("\nEnter elements of Matrix A:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter elements of Matrix B:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    /*
       Strassen's algorithm works most naturally
       when n is a power of 2.

       For simplicity, this implementation expects
       n to be a power of 2.
    */

    if ((n & (n - 1)) != 0)
    {
        printf("\nError: Matrix size must be a power of 2.\n");
        printf("Try sizes such as 2, 4, 8, 16, ...\n");

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);

        return 0;
    }

    strassen(A, B, C, n);

    printf("\nMatrix A:\n");
    printMatrix(A, n);

    printf("\nMatrix B:\n");
    printMatrix(B, n);

    printf("\nResult Matrix (A x B):\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}