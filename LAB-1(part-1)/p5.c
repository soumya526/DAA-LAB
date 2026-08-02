#include <stdio.h>

int findPartition(int arr[], int n) {
    int low = 0, high = n - 1;
    int ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1) {
            ans = mid;
            high = mid - 1;   // Search left half
        } else {
            low = mid + 1;    // Search right half
        }
    }

    return ans;
}

int main() {
    int arr[] = {0,0,0,0,0,1,1,1,1,1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int partition = findPartition(arr, n);

    if (partition == -1)
        printf("No 1's found.\n");
    else
        printf("Partition point (first 1) = Index %d\n", partition);

    return 0;
}