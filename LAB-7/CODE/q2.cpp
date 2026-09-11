#include <stdio.h>
#include <stdlib.h>

#define INF 999999

// Function to find maximum of two numbers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to find minimum of two numbers
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// Egg Dropping using Dynamic Programming
int eggDrop(int eggs, int floors)
{
    int **dp;

    // Allocate DP table
    dp = (int **)malloc((eggs + 1) * sizeof(int *));

    for (int i = 0; i <= eggs; i++)
        dp[i] = (int *)malloc((floors + 1) * sizeof(int));

    // Base cases
    // 0 floors require 0 drops
    for (int e = 1; e <= eggs; e++)
        dp[e][0] = 0;

    // 1 floor requires 1 drop
    for (int e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    // With 1 egg, we have to test every floor
    for (int f = 0; f <= floors; f++)
        dp[1][f] = f;

    // Fill DP table
    for (int e = 2; e <= eggs; e++)
    {
        for (int f = 2; f <= floors; f++)
        {
            dp[e][f] = INF;

            // Try dropping from every possible floor
            for (int x = 1; x <= f; x++)
            {
                int breaks = dp[e - 1][x - 1];
                int survives = dp[e][f - x];

                int worst = max(breaks, survives);

                int attempts = 1 + worst;

                dp[e][f] = min(dp[e][f], attempts);
            }
        }
    }

    int answer = dp[eggs][floors];

    // Free memory
    for (int i = 0; i <= eggs; i++)
        free(dp[i]);

    free(dp);

    return answer;
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    int result = eggDrop(E, F);

    printf("\nMinimum number of droppings = %d\n", result);

    return 0;
}