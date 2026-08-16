#include <stdio.h>

void selectionSort(int A[], int n)
{
    int i, j, min, temp;
    int comparisons = 0;

    // Outer loop: first n-1 elements
    for (i = 0; i < n - 1; i++)
    {
        min = i;

        // Find minimum element in A[i...n-1]
        for (j = i + 1; j < n; j++)
        {
            comparisons++;

            if (A[j] < A[min])
            {
                min = j;
            }
        }

        // Exchange A[i] and A[min]
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }

    printf("\nNumber of comparisons = %d\n", comparisons);
}

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("\nOriginal array:\n");
    printArray(A, n);

    selectionSort(A, n);

    printf("\nSorted array:\n");
    printArray(A, n);

    printf("\nTheoretical number of comparisons = %d\n",
           n * (n - 1) / 2);

    printf("Best-case complexity  = Theta(n^2)\n");
    printf("Worst-case complexity = Theta(n^2)\n");

    return 0;
}