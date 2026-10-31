#include <stdio.h>

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

    long long dp[V + 1];

    for (int i = 0; i <= V; i++)
        dp[i] = 0;

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coin[i]; j <= V; j++) {
            dp[j] += dp[j - coin[i]];
        }
    }

    printf("Total number of ways = %lld\n", dp[V]);

    return 0;
}