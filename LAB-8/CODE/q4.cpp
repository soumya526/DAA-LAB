#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int A[n], dp[n];

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    int answer = 1;

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }

        answer = max(answer, dp[i]);
    }

    printf("Length of LIS = %d\n", answer);

    return 0;
}