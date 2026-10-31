#include <stdio.h>

#define MAX 1000

int main() {
    int n, i;
    int ratings[MAX];
    int candies[MAX];
    int total = 0;

    printf("Enter the number of children: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of children.\n");
        return 1;
    }

    printf("Enter the ratings of the children:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
        candies[i] = 1;
    }

    /* Left-to-right traversal */
    for (i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    /* Right-to-left traversal */
    for (i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i] < candies[i + 1] + 1) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    /* Calculate total candies */
    for (i = 0; i < n; i++) {
        total += candies[i];
    }

    printf("\nCandy distribution:\n");

    for (i = 0; i < n; i++) {
        printf("%d ", candies[i]);
    }

    printf("\nMinimum total candies required = %d\n", total);

    return 0;
}