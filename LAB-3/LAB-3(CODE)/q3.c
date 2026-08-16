#include <stdio.h>

int comparisons = 0;

struct MinMax {
    int min;
    int max;
};

struct MinMax findMinMax(int arr[], int low, int high)
{
    struct MinMax result, left, right;

    // Case 1: Only one element
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // Case 2: Two elements
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    // Divide
    int mid = (low + high) / 2;

    // Conquer
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Combine - find minimum
    comparisons++;

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    // Combine - find maximum
    comparisons++;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct MinMax result = findMinMax(arr, 0, n - 1);

    printf("\nMinimum element = %d\n", result.min);
    printf("Maximum element = %d\n", result.max);
    printf("Number of comparisons = %d\n", comparisons);

    printf("\nMaximum allowed comparisons (3n/2) = %d\n",
           (3 * n) / 2);

    if (comparisons <= (3 * n) / 2)
        printf("Validation: Comparisons are within the required bound.\n");
    else
        printf("Validation: Comparisons exceed the required bound.\n");

    return 0;
}