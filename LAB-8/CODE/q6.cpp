#include <stdio.h>
#include <string.h>

int min3(int a, int b, int c) {
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

int main() {

    char A[100], B[100];

    printf("Enter first string: ");
    scanf("%s", A);

    printf("Enter second string: ");
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],       // deletion
                    dp[i][j - 1],       // insertion
                    dp[i - 1][j - 1]    // substitution
                );
            }
        }
    }

    printf("Minimum edit distance = %d\n", dp[m][n]);

    printf("\nTraceback operations:\n");

    int i = m;
    int j = n;

    while (i > 0 || j > 0) {

        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1]) {

            printf("Keep '%c'\n", A[i - 1]);

            i--;
            j--;
        }

        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1) {

            printf("Substitute '%c' -> '%c'\n",
                   A[i - 1], B[j - 1]);

            i--;
            j--;
        }

        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1) {

            printf("Delete '%c'\n", A[i - 1]);

            i--;
        }

        else {

            printf("Insert '%c'\n", B[j - 1]);

            j--;
        }
    }

    return 0;
}