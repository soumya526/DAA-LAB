#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Print array */
void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

/* (i) Find Maximum */
int findMaximum(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

/* (ii) Find First and Second Largest */
void findLargestTwo(int a[], int n)
{
    int largest, second;

    if (a[0] > a[1])
    {
        largest = a[0];
        second = a[1];
    }
    else
    {
        largest = a[1];
        second = a[0];
    }

    for (int i = 2; i < n; i++)
    {
        if (a[i] > largest)
        {
            second = largest;
            largest = a[i];
        }
        else if (a[i] > second && a[i] != largest)
        {
            second = a[i];
        }
    }

    printf("Largest = %d\n", largest);
    printf("Second Largest = %d\n", second);
}

/* (iii) Find Mean */
double findMean(int a[], int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum / n;
}

/* Merge function for Merge Sort */
void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

/* Merge Sort */
void mergeSort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

/* (iv) Find Median */
double findMedian(int a[], int n)
{
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    mergeSort(b, 0, n - 1);

    double median;

    if (n % 2 == 0)
        median = (b[n / 2 - 1] + b[n / 2]) / 2.0;
    else
        median = b[n / 2];

    free(b);

    return median;
}

/* (v) Find Standard Deviation */
double findStandardDeviation(int a[], int n)
{
    double mean = findMean(a, n);
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double difference = a[i] - mean;
        sum += difference * difference;
    }

    return sqrt(sum / n);
}

/* (vi) Find Mode */
int findMode(int a[], int n)
{
    int mode = a[0];
    int maxFrequency = 0;

    for (int i = 0; i < n; i++)
    {
        int frequency = 0;

        for (int j = 0; j < n; j++)
        {
            if (a[j] == a[i])
                frequency++;
        }

        if (frequency > maxFrequency)
        {
            maxFrequency = frequency;
            mode = a[i];
        }
    }

    return mode;
}

/* (vii) Remove Duplicates */
int removeDuplicates(int a[], int n)
{
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int duplicate = 0;

        for (int j = 0; j < newSize; j++)
        {
            if (a[i] == a[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
        {
            a[newSize] = a[i];
            newSize++;
        }
    }

    return newSize;
}

/* (viii) Reverse Array */
void reverseArray(int a[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        int temp = a[left];
        a[left] = a[right];
        a[right] = temp;

        left++;
        right--;
    }
}

/*
   (ix) Partition Array

   Required condition:
   Elements >= pivot appear BEFORE
   elements < pivot.
*/
void partitionArray(int a[], int n, int pivot)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        while (left < n && a[left] >= pivot)
            left++;

        while (right >= 0 && a[right] < pivot)
            right--;

        if (left < right)
        {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;

            left++;
            right--;
        }
    }
}

/* Main function */
int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    printf("Enter %d unsorted integers:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nOriginal Array:\n");
    printArray(a, n);

    /* (i) Maximum */
    printf("\n(i) Maximum Element = %d\n",
           findMaximum(a, n));

    /* (ii) First and Second Largest */
    printf("\n(ii) First and Second Largest:\n");
    findLargestTwo(a, n);

    /* (iii) Mean */
    printf("\n(iii) Mean = %.2lf\n",
           findMean(a, n));

    /* (iv) Median */
    printf("\n(iv) Median = %.2lf\n",
           findMedian(a, n));

    /* (v) Standard Deviation */
    printf("\n(v) Standard Deviation = %.2lf\n",
           findStandardDeviation(a, n));

    /* (vi) Mode */
    printf("\n(vi) Mode = %d\n",
           findMode(a, n));

    /* (vii) Remove Duplicates */
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    int newSize = removeDuplicates(b, n);

    printf("\n(vii) After Removing Duplicates:\n");
    printArray(b, newSize);

    free(b);

    /* (viii) Reverse */
    int *c = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        c[i] = a[i];

    reverseArray(c, n);

    printf("\n(viii) Reversed Array:\n");
    printArray(c, n);

    free(c);

    /* (ix) Partition */
    int pivot;

    printf("\nEnter pivot for partition: ");
    scanf("%d", &pivot);

    int *d = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        d[i] = a[i];

    partitionArray(d, n, pivot);

    printf("\n(ix) Partitioned Array:\n");
    printArray(d, n);

    free(d);
    free(a);

    return 0;
}