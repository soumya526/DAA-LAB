#include <stdio.h>

int main()
{
    int n;
    int totalCoins;
    int minMoves;

    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &n);

    // Total number of coins:
    // 1 + 2 + ... + n = n(n+1)/2
    totalCoins = n * (n + 1) / 2;

    // Minimum number of moves:
    // floor(totalCoins / 3)
    minMoves = totalCoins / 3;

    printf("\nTotal number of coins = %d\n", totalCoins);
    printf("Minimum number of moves = %d\n", minMoves);

    return 0;
}