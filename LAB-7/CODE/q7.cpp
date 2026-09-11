#include <stdio.h>
#include <limits.h>

#define MAX 100

int m[MAX][MAX];   // m[i][j] = minimum cost
int s[MAX][MAX];   // s[i][j] = position of split

// Print optimal parenthesization
void printOptimalOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalOrder(i, s[i][j]);
    printOptimalOrder(s[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;
    int p[MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    printf("Enter dimensions of matrices:\n");

    /*
       If there are n matrices:
       A1 = p[0] x p[1]
       A2 = p[1] x p[2]
       ...
       An = p[n-1] x p[n]
    */

    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    // Cost of multiplying one matrix is 0
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    // chainLength = number of matrices in the chain
    for (int chainLength = 2; chainLength <= n; chainLength++)
    {
        for (int i = 1; i <= n - chainLength + 1; i++)
        {
            int j = i + chainLength - 1;

            m[i][j] = INT_MAX;

            // Try every possible split
            for (int k = i; k < j; k++)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           m[1][n]);

    printf("Optimal ordering = ");
    printOptimalOrder(1, n);

    printf("\n");

    return 0;
}