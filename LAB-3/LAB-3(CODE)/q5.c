#include <stdio.h>
#include <stdlib.h>

long long additions = 0;
long long multiplications = 0;

// Allocate matrix
int **allocateMatrix(int n)
{
    int **M = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        M[i] = (int *)calloc(n, sizeof(int));

    return M;
}

// Free matrix
void freeMatrix(int **M, int n)
{
    for (int i = 0; i < n; i++)
        free(M[i]);

    free(M);
}

// Add matrices
void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
            additions++;
        }
    }
}

// Subtract matrices
void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
            additions++;
        }
    }
}

// Special matrix multiplication
void specialMultiply(int **A, int **B, int **C, int n)
{
    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        multiplications++;
        return;
    }

    int k = n / 2;

    // Create submatrices
    int **A1 = allocateMatrix(k);
    int **A2 = allocateMatrix(k);

    int **B1 = allocateMatrix(k);
    int **B2 = allocateMatrix(k);

    /*
       A =
       | A1  A2 |
       | A2  A1 |

       B =
       | B1  B2 |
       | B2  B1 |
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    // Temporary matrices
    int **Aplus = allocateMatrix(k);
    int **Aminus = allocateMatrix(k);

    int **Bplus = allocateMatrix(k);
    int **Bminus = allocateMatrix(k);

    int **P = allocateMatrix(k);
    int **Q = allocateMatrix(k);

    // Aplus = A1 + A2
    addMatrix(A1, A2, Aplus, k);

    // Aminus = A1 - A2
    subtractMatrix(A1, A2, Aminus, k);

    // Bplus = B1 + B2
    addMatrix(B1, B2, Bplus, k);

    // Bminus = B1 - B2
    subtractMatrix(B1, B2, Bminus, k);

    /*
       P = (A1 + A2)(B1 + B2)
    */
    specialMultiply(Aplus, Bplus, P, k);

    /*
       Q = (A1 - A2)(B1 - B2)
    */
    specialMultiply(Aminus, Bminus, Q, k);

    /*
       C1 = (P + Q) / 2
       C2 = (P - Q) / 2
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int C1 = P[i][j] + Q[i][j];
            int C2 = P[i][j] - Q[i][j];

            additions += 2;

            C[i][j] = C1 / 2;
            C[i][j + k] = C2 / 2;
            C[i + k][j] = C2 / 2;
            C[i + k][j + k] = C1 / 2;
        }
    }

    // Free memory
    freeMatrix(A1, k);
    freeMatrix(A2, k);
    freeMatrix(B1, k);
    freeMatrix(B2, k);

    freeMatrix(Aplus, k);
    freeMatrix(Aminus, k);
    freeMatrix(Bplus, k);
    freeMatrix(Bminus, k);

    freeMatrix(P, k);
    freeMatrix(Q, k);
}

// Print matrix
void printMatrix(int **M, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", M[i][j]);

        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter n (power of 2): ");
    scanf("%d", &n);

    // Check power of 2
    if (n <= 0 || (n & (n - 1)) != 0)
    {
        printf("Error: n must be a power of 2.\n");
        return 0;
    }

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("\nEnter Matrix A:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter Matrix B:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    specialMultiply(A, B, C, n);

    printf("\nMatrix A:\n");
    printMatrix(A, n);

    printf("\nMatrix B:\n");
    printMatrix(B, n);

    printf("\nResult Matrix A x B:\n");
    printMatrix(C, n);

    printf("\nTotal scalar multiplications = %lld\n",
           multiplications);

    printf("Total additions/subtractions = %lld\n",
           additions);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}