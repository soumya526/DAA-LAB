#include <stdio.h>

#define MAX 100

int weight[MAX];
int dp[MAX][MAX];
int sum[MAX][MAX];
int split[MAX][MAX];

int min(int a, int b)
{
    return (a < b) ? a : b;
}

/* Construct the optimal alphabetic tree using DP */
void optimalAlphabeticTree(int n)
{
    int i, j, k, len;
    int cost;

    /* Calculate interval weight sums */
    for (i = 0; i < n; i++)
    {
        sum[i][i] = weight[i];

        for (j = i + 1; j < n; j++)
            sum[i][j] = sum[i][j - 1] + weight[j];
    }

    /* A single leaf has zero cost */
    for (i = 0; i < n; i++)
        dp[i][i] = 0;

    /* Consider intervals of increasing length */
    for (len = 2; len <= n; len++)
    {
        for (i = 0; i <= n - len; i++)
        {
            j = i + len - 1;

            dp[i][j] = 1000000000;

            for (k = i; k < j; k++)
            {
                cost = dp[i][k] +
                       dp[k + 1][j] +
                       sum[i][j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum weighted path cost: %d\n",
           dp[0][n - 1]);
}

/* Display the tree structure */
void printTree(int i, int j)
{
    if (i == j)
    {
        printf("L%d(%d)", i + 1, weight[i]);
        return;
    }

    int k = split[i][j];

    printf("(");

    printTree(i, k);

    printf(" , ");

    printTree(k + 1, j);

    printf(")");
}

int main()
{
    int n, i;

    printf("Enter the number of weights: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of weights.\n");
        return 0;
    }

    printf("Enter the weights in their original order:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &weight[i]);

        if (weight[i] <= 0)
        {
            printf("Weights must be positive.\n");
            return 0;
        }
    }

    optimalAlphabeticTree(n);

    printf("Optimal alphabetic tree:\n");
    printTree(0, n - 1);
    printf("\n");

    return 0;
}