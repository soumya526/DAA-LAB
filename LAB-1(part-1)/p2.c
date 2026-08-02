#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, i;
    int fairHeads = 0, fairTails = 0;
    int biasedHeads = 0, biasedTails = 0;

    printf("Enter the number of coin tosses: ");
    scanf("%d", &n);

    // Seed the random number generator
    srand(time(NULL));

    // ----- Fair Coin Simulation -----
    for (i = 0; i < n; i++) {
        if (rand() % 2 == 0)
            fairHeads++;
        else
            fairTails++;
    }

    // ----- Biased Coin Simulation -----
    // Probability of Head = 0.7, Tail = 0.3
    for (i = 0; i < n; i++) {
        double r = (double)rand() / RAND_MAX;

        if (r < 0.7)
            biasedHeads++;
        else
            biasedTails++;
    }

    // ----- Results -----
    printf("\n===== Fair Coin =====\n");
    printf("Heads = %d\n", fairHeads);
    printf("Tails = %d\n", fairTails);
    printf("Probability of Head = %.4f\n", (double)fairHeads / n);
    printf("Probability of Tail = %.4f\n", (double)fairTails / n);

    printf("\n===== Biased Coin (P(Head)=0.7) =====\n");
    printf("Heads = %d\n", biasedHeads);
    printf("Tails = %d\n", biasedTails);
    printf("Probability of Head = %.4f\n", (double)biasedHeads / n);
    printf("Probability of Tail = %.4f\n", (double)biasedTails / n);

    return 0;
}