#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    srand(time(NULL));

    FILE *fp = fopen("heap_random.txt", "w");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        free(a);
        return 1;
    }

    printf("Random elements:\n");

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        fprintf(fp, "%d ", a[i]);
        printf("%d ", a[i]);
    }

    fclose(fp);

    heapSort(a, n);

    fp = fopen("heap_random.txt", "w");

    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", a[i]);

    fclose(fp);

    printf("\n\nSorted elements:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    free(a);

    return 0;
}