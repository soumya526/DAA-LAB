#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {

    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int price[n + 1];

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &price[i]);

    int dp[n + 1];
    int cut[n + 1];

    dp[0] = 0;
    cut[0] = 0;

    for (int i = 1; i <= n; i++) {

        dp[i] = 0;

        for (int j = 1; j <= i; j++) {

            if (price[j] + dp[i - j] > dp[i]) {

                dp[i] = price[j] + dp[i - j];

                cut[i] = j;
            }
        }
    }

    printf("Maximum revenue = %d\n", dp[n]);

    printf("Pieces used: ");

    int length = n;

    while (length > 0) {

        printf("%d ", cut[length]);

        length = length - cut[length];
    }

    printf("\n");

    return 0;
}