#include <stdio.h>

#define MAX 100

struct Item {
    int id;
    float value;
    float weight;
    float decay;
    float density;
};

int main() {
    struct Item items[MAX], temp;
    int n, i, j;

    float W, remaining, totalValue = 0;
    float fraction, time = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%f", &W);

    for (i = 0; i < n; i++) {
        items[i].id = i + 1;

        printf("\nEnter value, weight and decay rate of item %d: ",
               i + 1);

        scanf("%f %f %f",
              &items[i].value,
              &items[i].weight,
              &items[i].decay);

        if (items[i].weight <= 0 || items[i].decay <= 0) {
            printf("Weight and decay rate must be positive.\n");
            return 1;
        }

        items[i].density =
            items[i].value / items[i].weight;
    }

    remaining = W;

    printf("\nGreedy Selection Order:\n");

    while (remaining > 0) {
        int best = -1;
        float bestDensity = 0;

        /*
         * Find the item having the highest
         * positive effective density.
         */
        for (i = 0; i < n; i++) {
            if (items[i].weight <= 0)
                continue;

            float currentDensity =
                items[i].density - items[i].decay * time;

            if (currentDensity > bestDensity) {
                bestDensity = currentDensity;
                best = i;
            }
        }

        if (best == -1)
            break;

        /*
         * Select the maximum possible fraction.
         */
        if (items[best].weight <= remaining) {
            fraction = 1.0;
        } else {
            fraction = remaining / items[best].weight;
        }

        float selectedWeight =
            fraction * items[best].weight;

        float selectedValue =
            selectedWeight * bestDensity;

        printf("Item %d: Fraction = %.2f, "
               "Weight = %.2f, Density = %.2f\n",
               items[best].id,
               fraction,
               selectedWeight,
               bestDensity);

        totalValue += selectedValue;
        remaining -= selectedWeight;

        /*
         * Remove the selected portion.
         * A partially selected item may be selected again.
         */
        items[best].weight -= selectedWeight;

        time += 1.0;
    }

    printf("\nTotal weight used = %.2f\n", W - remaining);
    printf("Total effective value = %.2f\n", totalValue);

    return 0;
}