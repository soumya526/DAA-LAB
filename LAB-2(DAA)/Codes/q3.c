#include <stdio.h>
#include <stdlib.h>

/* Function to sort one array using Bubble Sort */
void sortArray(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* Merge two sorted arrays */
int* merge(int A[], int sizeA, int B[], int sizeB)
{
    int *C;
    int i = 0, j = 0, k = 0;

    C = (int *)malloc((sizeA + sizeB) * sizeof(int));

    while (i < sizeA && j < sizeB)
    {
        if (A[i] <= B[j])
        {
            C[k] = A[i];
            i++;
        }
        else
        {
            C[k] = B[j];
            j++;
        }

        k++;
    }

    /* Copy remaining elements of A */
    while (i < sizeA)
    {
        C[k] = A[i];
        i++;
        k++;
    }

    /* Copy remaining elements of B */
    while (j < sizeB)
    {
        C[k] = B[j];
        j++;
        k++;
    }

    return C;
}

int main()
{
    int k, n;
    int i, j;

    /* --------------------------------
       Step 1: Take k and n
       -------------------------------- */

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);

    /* --------------------------------
       Step 2: Create 2D matrix
       -------------------------------- */

    int **A = (int **)malloc(k * sizeof(int *));

    for (i = 0; i < k; i++)
    {
        A[i] = (int *)malloc(n * sizeof(int));
    }

    /* --------------------------------
       Step 3: Input elements
       -------------------------------- */

    printf("\nEnter %d elements for each array:\n", n);

    for (i = 0; i < k; i++)
    {
        printf("\nArray %d:\n", i + 1);

        for (j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    /* --------------------------------
       Step 4: Sort each array
       -------------------------------- */

    for (i = 0; i < k; i++)
    {
        sortArray(A[i], n);
    }

    /* Display sorted arrays */

    printf("\nSorted arrays:\n");

    for (i = 0; i < k; i++)
    {
        printf("Array %d: ", i + 1);

        for (j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }

        printf("\n");
    }

    /* --------------------------------
       Step 5:
       Method 1 - Sequential merging
       -------------------------------- */

    int *result;

    /* Initially result = first array */

    result = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        result[i] = A[0][i];
    }

    int currentSize = n;

    /*
       Merge:
       
       A1 + A2
       Result + A3
       Result + A4
       ...
       Result + Ak
    */

    for (i = 1; i < k; i++)
    {
        int *temp;

        temp = merge(
            result,
            currentSize,
            A[i],
            n
        );

        free(result);

        result = temp;

        currentSize = currentSize + n;
    }

    /* --------------------------------
       Step 6: Display final result
       -------------------------------- */

    printf("\nFinal merged sorted array:\n");

    for (i = 0; i < currentSize; i++)
    {
        printf("%d ", result[i]);
    }

    printf("\n");

    /* --------------------------------
       Free memory
       -------------------------------- */

    free(result);

    for (i = 0; i < k; i++)
    {
        free(A[i]);
    }

    free(A);

    return 0;
}