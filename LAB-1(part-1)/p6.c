#include <stdio.h>

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int duplicate = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                printf("Duplicate element found: %d\n", arr[i]);
                duplicate = 1;
                break;
            }
        }
        if (duplicate)
            break;
    }

    if (!duplicate)
        printf("All elements are unique.\n");

    return 0;
}