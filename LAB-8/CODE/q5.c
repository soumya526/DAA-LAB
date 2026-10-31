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

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        dp[i] = A[i];
    }

    int answer = A[0];

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i]) {
                dp[i] = max(dp[i],
                            dp[j] + A[i]);
            }
        }

        answer = max(answer, dp[i]);
    }

    printf("Maximum sum = %d\n", answer);

    return 0;
}