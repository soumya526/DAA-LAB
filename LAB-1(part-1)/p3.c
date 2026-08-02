#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}

// Bubble Sort with Early Termination
int bubbleSortOptimized(int arr[], int n) {
    int comparisons = 0;
    int swapped;

    for(int i = 0; i < n - 1; i++) {
        swapped = 0;

        for(int j = 0; j < n - i - 1; j++) {
            comparisons++;

            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    return comparisons;
}

// Bubble Sort without Early Termination
int bubbleSortNormal(int arr[], int n) {
    int comparisons = 0;

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            comparisons++;

            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main() {
    srand(time(NULL));

    printf("Size\tOptimized\tNormal\n");

    for(int n = 100; n <= 1000; n += 100) {

        int arr1[n], arr2[n];

        generateRandomArray(arr1, n);

        for(int i = 0; i < n; i++)
            arr2[i] = arr1[i];

        int c1 = bubbleSortOptimized(arr1, n);
        int c2 = bubbleSortNormal(arr2, n);

        printf("%d\t%d\t\t%d\n", n, c1, c2);
    }

    return 0;
}