#include <stdio.h>

int fibonacci(int n)
{
    int dp[n + 1];

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 0)
        printf("Invalid input\n");
    else if (n == 0)
        printf("Fibonacci number = 0\n");
    else
        printf("Fibonacci number = %d\n", fibonacci(n));

    return 0;
}