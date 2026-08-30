#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int a[], int low, int high)
{
    if (low >= high)
        return;

    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;

            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    int p = i + 1;

    quickSort(a, low, p - 1);
    quickSort(a, p + 1, high);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    srand(time(NULL));

    FILE *fp = fopen("random.txt", "w");

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

    quickSort(a, 0, n - 1);

    fp = fopen("random.txt", "w");

    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", a[i]);

    fclose(fp);

    printf("\n\nSorted elements:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    free(a);

    return 0;
}