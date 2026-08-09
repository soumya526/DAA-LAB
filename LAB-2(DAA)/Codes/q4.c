#include <stdio.h>
#include <stdlib.h>

/* -----------------------------------------
   Sort one row using Bubble Sort
   ----------------------------------------- */
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

/* -----------------------------------------
   Merge two sorted arrays
   ----------------------------------------- */
int* merge(int A[], int sizeA, int B[], int sizeB)
{
    int *C;
    int i = 0, j = 0, k = 0;

    C = (int *)malloc((sizeA + sizeB) * sizeof(int));

    while (i < sizeA && j < sizeB)
    {
        if (A[i] <= B[j])
        {
            C[k++] = A[i++];
        }
        else
        {
            C[k++] = B[j++];
        }
    }

    /* Copy remaining elements of A */
    while (i < sizeA)
    {
        C[k++] = A[i++];
    }

    /* Copy remaining elements of B */
    while (j < sizeB)
    {
        C[k++] = B[j++];
    }

    return C;
}

/* -----------------------------------------
   Main
   ----------------------------------------- */
int main()
{
    int k, n;
    int i, j;

    /* -----------------------------------------
       Step 1: Take input
       ----------------------------------------- */

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);

    if (k < 2)
    {
        printf("Number of arrays must be at least 2.\n");
        return 0;
    }

    /* For this implementation k should be power of 2 */
    int tempK = k;

    while (tempK > 1)
    {
        if (tempK % 2 != 0)
        {
            printf("Please enter k as a power of 2 (2, 4, 8, 16...).\n");
            return 0;
        }

        tempK = tempK / 2;
    }

    /* -----------------------------------------
       Step 2: Create 2D matrix
       ----------------------------------------- */

    int **A = (int **)malloc(k * sizeof(int *));

    for (i = 0; i < k; i++)
    {
        A[i] = (int *)malloc(n * sizeof(int));
    }

    /* -----------------------------------------
       Step 3: Input elements
       ----------------------------------------- */

    printf("\nEnter elements of each array:\n");

    for (i = 0; i < k; i++)
    {
        printf("\nArray %d:\n", i + 1);

        for (j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    /* -----------------------------------------
       Step 4: Sort every row
       ----------------------------------------- */

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

    /* -----------------------------------------
       Step 5: Pairwise merging
       ----------------------------------------- */

    int currentK = k;
    int currentSize = n;

    /*
       current contains the arrays at
       the current level.
    */
    int **current = A;

    while (currentK > 1)
    {
        int newK = currentK / 2;

        int **next =
            (int **)malloc(newK * sizeof(int *));

        /*
           Merge arrays in pairs
        */
        for (i = 0; i < currentK; i += 2)
        {
            next[i / 2] = merge(
                current[i],
                currentSize,
                current[i + 1],
                currentSize
            );
        }

        /*
           Do NOT free the original A here.
           We will free it at the end.
           
           For intermediate arrays, free them
           after they have been merged.
        */
        if (current != A)
        {
            for (i = 0; i < currentK; i++)
            {
                free(current[i]);
            }

            free(current);
        }

        current = next;

        currentK = newK;

        currentSize = currentSize * 2;
    }

    /* -----------------------------------------
       Step 6: FINAL SORTED ARRAY
       ----------------------------------------- */

    printf("\n=====================================\n");
    printf("FINAL SORTED ARRAY:\n");
    printf("=====================================\n");

    for (i = 0; i < currentSize; i++)
    {
        printf("%d ", current[0][i]);
    }

    printf("\n");

    printf("\nTotal elements = %d\n", currentSize);

    /* -----------------------------------------
       Step 7: Free memory
       ----------------------------------------- */

    /* Free final merged array */
    free(current[0]);
    free(current);

    /* Free original 2D matrix */
    for (i = 0; i < k; i++)
    {
        free(A[i]);
    }

    free(A);

    return 0;
}