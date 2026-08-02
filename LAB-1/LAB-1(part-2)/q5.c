#include <stdio.h>

int main() {
    int r1, c1, r2, c2;
    int A[10][10], B[10][10], sum[10][10], mul[10][10], trans[10][10];

    // Input first matrix
    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input second matrix
    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Matrix Addition
    if (r1 == r2 && c1 == c2) {
        printf("\nMatrix Addition:\n");
        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c1; j++) {
                sum[i][j] = A[i][j] + B[i][j];
                printf("%d ", sum[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("\nAddition not possible (dimensions must be same).\n");
    }

    // Matrix Multiplication
    if (c1 == r2) {
        printf("\nMatrix Multiplication:\n");

        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c2; j++) {
                mul[i][j] = 0;
                for (int k = 0; k < c1; k++) {
                    mul[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c2; j++) {
                printf("%d ", mul[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("\nMultiplication not possible (columns of A must equal rows of B).\n");
    }

    // Transpose of Matrix A
    printf("\nTranspose of Matrix A:\n");
    for (int i = 0; i < c1; i++) {
        for (int j = 0; j < r1; j++) {
            trans[i][j] = A[j][i];
            printf("%d ", trans[i][j]);
        }
        printf("\n");
    }

    return 0;
}