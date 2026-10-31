#include <stdio.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, V;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coin[n];

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coin[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    int dp[V + 1];

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {

            if (coin[j] <= i && dp[i - coin[j]] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin[j]] + 1);
            }
        }
    }

    if (dp[V] == INT_MAX)
        printf("Amount cannot be formed.\n");
    else
        printf("Minimum number of coins = %d\n", dp[V]);

    return 0;
}