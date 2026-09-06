#include <stdio.h>
#include <stdlib.h>

long long totalCost = 0;
long long reversalCount = 0;

/* Reverse p[i...j] */
void reversePart(int p[], int i, int j)
{
    int temp;
    int length = j - i + 1;

    if (i >= j)
        return;

    while (i < j)
    {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }

    /* Cost of reversal = length */
    totalCost += length;
    reversalCount++;
}

/*
   Rotate three consecutive blocks:

   A B C  ->  C A B

   using three reversals.

   This is useful for moving a selected block
   without using arbitrary swaps.
*/
void rotateBlocks(int p[], int l, int m, int r)
{
    /*
        A = [l ... m]
        B = [m+1 ... r]

        A B -> B A
    */

    if (l > m || m >= r)
        return;

    reversePart(p, l, m);
    reversePart(p, m + 1, r);
    reversePart(p, l, r);
}

/*
   Simple reversal-based sorting inside a segment.

   The divide-and-conquer structure restricts
   the segment being processed.
*/
void divideSort(int p[], int left, int right)
{
    int mid;
    int i, j;
    int minPos;

    if (left >= right)
        return;

    mid = (left + right) / 2;

    /*
       Divide
    */
    divideSort(p, left, mid);
    divideSort(p, mid + 1, right);

    /*
       Combine:
       Select the smallest element that belongs
       to the current segment and place it at
       the correct position using reversal.
    */

    for (i = left; i <= right; i++)
    {
        if (p[i] != i + 1)
        {
            minPos = i;

            for (j = i + 1; j <= right; j++)
            {
                if (p[j] == i + 1)
                {
                    minPos = j;
                    break;
                }
            }

            if (minPos != i)
                reversePart(p, i, minPos);
        }
    }
}

/* Print permutation */
void printArray(int p[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}

int main()
{
    int n, i;
    int *p;

    printf("Enter n: ");
    scanf("%d", &n);

    p = (int *)malloc(n * sizeof(int));

    printf("Enter permutation:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation:\n");
    printArray(p, n);

    totalCost = 0;
    reversalCount = 0;

    divideSort(p, 0, n - 1);

    printf("\nSorted permutation:\n");
    printArray(p, n);

    printf("\nNumber of reversals = %lld\n",
           reversalCount);

    printf("Total reversal cost = %lld\n",
           totalCost);

    printf("\nTheoretical target: O(n log^2 n)\n");

    free(p);

    return 0;
}