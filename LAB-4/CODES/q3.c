#include <stdio.h>

#define MAX 100

// ---------------- MERGE SORT ----------------

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

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ---------------- BINARY SEARCH ----------------

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

// ------------------------------------------------
// Recursively select k-1 elements
// ------------------------------------------------

int findSum(int arr[], int n, int k, int T,
            int start, int count, int sum) {

    // We have selected k-1 elements
    if (count == k - 1) {

        int required = T - sum;

        if (binarySearch(arr, n, required)) {
            printf("Required element: %d\n", required);
            return 1;
        }

        return 0;
    }

    // Choose next element
    for (int i = start; i < n; i++) {

        if (findSum(arr, n, k, T,
                    i + 1,
                    count + 1,
                    sum + arr[i])) {
            return 1;
        }
    }

    return 0;
}

// ---------------- MAIN ----------------

int main() {

    int S[MAX];
    int n, k, T;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements of S:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    // Sort the set
    mergeSort(S, 0, n - 1);

    printf("\nSorted set:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);

    printf("\n");

    // Find k elements whose sum is T
    if (findSum(S, n, k, T, 0, 0, 0))
        printf("\nYES: %d elements can add up to %d.\n", k, T);
    else
        printf("\nNO: No %d elements add up to %d.\n", k, T);

    return 0;
}