#include <stdio.h>

int findDefective(int coins[], int left, int right)
{
    // Only one coin remains
    if (left == right)
        return left;

    // Divide into three nearly equal groups
    int third = (right - left + 1) / 3;

    int mid1 = left + third - 1;
    int mid2 = mid1 + third;

    int sum1 = 0, sum2 = 0;

    // Weight Group 1
    for (int i = left; i <= mid1; i++)
        sum1 += coins[i];

    // Weight Group 2
    for (int i = mid1 + 1; i <= mid2; i++)
        sum2 += coins[i];

    if (sum1 < sum2)
    {
        // Group 1 is lighter
        return findDefective(coins, left, mid1);
    }
    else if (sum2 < sum1)
    {
        // Group 2 is lighter
        return findDefective(coins, mid1 + 1, mid2);
    }
    else
    {
        // Both groups have equal weight.
        // Defective coin is in Group 3.
        return findDefective(coins, mid2 + 1, right);
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of %d coins:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    /*
       Find minimum weight among all coins.
       Since defective coin can only be lighter,
       a coin with smaller weight is the possible defective coin.
    */

    int minWeight = coins[0];

    for (int i = 1; i < n; i++)
    {
        if (coins[i] < minWeight)
            minWeight = coins[i];
    }

    int count = 0;
    int defective = -1;

    for (int i = 0; i < n; i++)
    {
        if (coins[i] == minWeight)
        {
            count++;
            defective = i;
        }
    }

    if (count == 1)
    {
        printf("\nDefective coin found at position %d\n", defective + 1);
        printf("Weight = %d\n", coins[defective]);
    }
    else
    {
        printf("\nNo defective coin found.\n");
    }

    return 0;
}