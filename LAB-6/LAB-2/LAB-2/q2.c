#include <stdio.h>
#include <math.h>

#define MAX 50
#define EPS 1e-9

// Print matrix
void printMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%8.2lf ", A[i][j]);

        printf("\n");
    }
}

// (i) Matrix Addition
void addMatrix(double A[MAX][MAX], double B[MAX][MAX],
               double C[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}

// (ii) Matrix Multiplication
void multiplyMatrix(double A[MAX][MAX], double B[MAX][MAX],
                    double C[MAX][MAX], int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

// (iii) Check Zero Matrix
int isZeroMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (fabs(A[i][j]) > EPS)
                return 0;
        }
    }

    return 1;
}

// (iv) Check Symmetric Matrix
int isSymmetric(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (fabs(A[i][j] - A[j][i]) > EPS)
                return 0;
        }
    }

    return 1;
}

// (v) Determinant using Gaussian Elimination
double determinant(double A[MAX][MAX], int n)
{
    double temp[MAX][MAX];
    double det = 1;
    double factor, t;
    int i, j, k, pivot;

    // Copy matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            temp[i][j] = A[i][j];

    for (i = 0; i < n; i++)
    {
        pivot = i;

        // Find pivot
        for (j = i + 1; j < n; j++)
        {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                pivot = j;
        }

        // Singular matrix
        if (fabs(temp[pivot][i]) < EPS)
            return 0;

        // Swap rows
        if (pivot != i)
        {
            for (k = 0; k < n; k++)
            {
                t = temp[i][k];
                temp[i][k] = temp[pivot][k];
                temp[pivot][k] = t;
            }

            det = -det;
        }

        det *= temp[i][i];

        // Eliminate below pivot
        for (j = i + 1; j < n; j++)
        {
            factor = temp[j][i] / temp[i][i];

            for (k = i; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    return det;
}

// (vi) In-place Transpose
void transposeInPlace(double A[MAX][MAX], int n)
{
    int i, j;
    double temp;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

// Find largest off-diagonal element
void findLargest(double A[MAX][MAX], int n, int *p, int *q)
{
    int i, j;
    double max = 0;

    *p = 0;
    *q = 1;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (fabs(A[i][j]) > max)
            {
                max = fabs(A[i][j]);
                *p = i;
                *q = j;
            }
        }
    }
}

// (vii) Eigenvalues and Eigenvectors
// Jacobi method for symmetric matrices
void eigenValuesVectors(double A[MAX][MAX],
                        double eigenValues[MAX],
                        double eigenVectors[MAX][MAX],
                        int n)
{
    int i, j, p, q, iter;
    double theta, c, s, app, aqq, apq;
    double aip, aiq, vip, viq;

    // Initialize eigenvector matrix as identity
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                eigenVectors[i][j] = 1;
            else
                eigenVectors[i][j] = 0;
        }
    }

    // Maximum iterations
    for (iter = 0; iter < 100; iter++)
    {
        findLargest(A, n, &p, &q);

        if (fabs(A[p][q]) < EPS)
            break;

        theta = 0.5 * atan2(2 * A[p][q],
                            A[p][p] - A[q][q]);

        c = cos(theta);
        s = sin(theta);

        app = A[p][p];
        aqq = A[q][q];
        apq = A[p][q];

        A[p][p] = c * c * app
                - 2 * s * c * apq
                + s * s * aqq;

        A[q][q] = s * s * app
                + 2 * s * c * apq
                + c * c * aqq;

        A[p][q] = 0;
        A[q][p] = 0;

        for (i = 0; i < n; i++)
        {
            if (i != p && i != q)
            {
                aip = A[i][p];
                aiq = A[i][q];

                A[i][p] = c * aip - s * aiq;
                A[p][i] = A[i][p];

                A[i][q] = s * aip + c * aiq;
                A[q][i] = A[i][q];
            }
        }

        // Update eigenvectors
        for (i = 0; i < n; i++)
        {
            vip = eigenVectors[i][p];
            viq = eigenVectors[i][q];

            eigenVectors[i][p] = c * vip - s * viq;
            eigenVectors[i][q] = s * vip + c * viq;
        }
    }

    for (i = 0; i < n; i++)
        eigenValues[i] = A[i][i];
}

int main()
{
    int n, i, j;
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    double eigenValues[MAX], eigenVectors[MAX][MAX];
    double det;

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    printf("\nEnter elements of Matrix A:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);
    }

    printf("\nEnter elements of Matrix B:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%lf", &B[i][j]);
    }

    // Matrix Addition
    addMatrix(A, B, C, n);

    printf("\n1. Matrix Addition:\n");
    printMatrix(C, n);

    // Matrix Multiplication
    multiplyMatrix(A, B, C, n);

    printf("\n2. Matrix Multiplication:\n");
    printMatrix(C, n);

    // Zero Matrix
    printf("\n3. Zero Matrix Check: ");

    if (isZeroMatrix(A, n))
        printf("Matrix A is a Zero Matrix\n");
    else
        printf("Matrix A is NOT a Zero Matrix\n");

    // Symmetric Matrix
    printf("\n4. Symmetric Matrix Check: ");

    if (isSymmetric(A, n))
        printf("Matrix A is Symmetric\n");
    else
        printf("Matrix A is NOT Symmetric\n");

    // Determinant
    det = determinant(A, n);

    printf("\n5. Determinant of Matrix A = %.2lf\n", det);

    // In-place Transpose
    transposeInPlace(A, n);

    printf("\n6. Matrix A after In-place Transpose:\n");
    printMatrix(A, n);

    // Eigenvalues and Eigenvectors
    // For Jacobi method, use a symmetric matrix.
    printf("\n7. Eigenvalue and Eigenvector:\n");
    printf("(Jacobi method works for real symmetric matrices.)\n");

    // Transpose A back before eigen calculation
    transposeInPlace(A, n);

    if (isSymmetric(A, n))
    {
        eigenValuesVectors(A, eigenValues,
                           eigenVectors, n);

        printf("\nEigenvalues:\n");

        for (i = 0; i < n; i++)
            printf("%.4lf ", eigenValues[i]);

        printf("\n\nEigenvectors (columns):\n");

        printMatrix(eigenVectors, n);
    }
    else
    {
        printf("Matrix A is not symmetric.\n");
        printf("Use a symmetric matrix for this Jacobi implementation.\n");
    }

    return 0;
}