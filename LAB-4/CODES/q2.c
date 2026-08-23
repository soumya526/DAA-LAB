#include <stdio.h>

#define MAX 100

// Merge two sorted parts
void merge(int arr[], int left, int mid, int right) {
    int temp[MAX];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

// Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Binary Search
int binarySearch(int arr[], int n, int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return 1;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int main() {
    int S1[MAX], S2[MAX];
    int n, x;

    printf("Enter size of both sets: ");
    scanf("%d", &n);

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter value of x: ");
    scanf("%d", &x);

    // Sort S2
    mergeSort(S2, 0, n - 1);

    // Check every element of S1
    for (int i = 0; i < n; i++) {
        int required = x - S1[i];

        if (binarySearch(S2, n, required)) {
            printf("\nPair found: %d + %d = %d\n",
                   S1[i], required, x);
            return 0;
        }
    }

    printf("\nNo pair exists whose sum is %d.\n", x);

    return 0;
}