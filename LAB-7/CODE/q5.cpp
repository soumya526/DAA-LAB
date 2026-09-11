#include <stdio.h>
#include <stdlib.h>

/*
    Update all possible target positions after the target moves
    one adjacent position.
*/
void moveTarget(int possible[], int n)
{
    int *next = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        if (possible[i])
        {
            // Target can move one position to the left
            if (i - 1 >= 0)
                next[i - 1] = 1;

            // Target can move one position to the right
            if (i + 1 < n)
                next[i + 1] = 1;
        }
    }

    for (int i = 0; i < n; i++)
        possible[i] = next[i];

    free(next);
}

/*
    Check whether any target position is still possible.
*/
int targetExists(int possible[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (possible[i])
            return 1;
    }

    return 0;
}

/*
    Validate a shooting strategy.
*/
int validateStrategy(int n, int shots[], int numberOfShots)
{
    int *possible = (int *)malloc(n * sizeof(int));

    /*
        Initially the target can be in ANY hiding spot.
    */
    for (int i = 0; i < n; i++)
        possible[i] = 1;

    for (int shot = 0; shot < numberOfShots; shot++)
    {
        int position = shots[shot] - 1;

        /*
            Shooter fires at this position.
            If the target is there, it is hit.
            Therefore remove this position from
            the possible target positions.
        */
        possible[position] = 0;

        /*
            If no possible positions remain,
            the target has definitely been hit.
        */
        if (!targetExists(possible, n))
        {
            free(possible);
            return 1;
        }

        /*
            Target moves to an adjacent position
            before the next shot.
        */
        if (shot < numberOfShots - 1)
            moveTarget(possible, n);
    }

    free(possible);

    return 0;
}

/*
    Generate the guaranteed shooting strategy.
*/
void generateStrategy(int n, int *shots, int *count)
{
    *count = 0;

    if (n == 2)
    {
        // Shoot position 1 twice
        shots[(*count)++] = 1;
        shots[(*count)++] = 1;
        return;
    }

    /*
        Forward sweep:
        2, 3, ..., n-1
    */
    for (int i = 2; i <= n - 1; i++)
        shots[(*count)++] = i;

    /*
        Reverse sweep:
        n-1, n-2, ..., 2
    */
    for (int i = n - 1; i >= 2; i--)
        shots[(*count)++] = i;
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 1;
    }

    /*
        Maximum number of shots is 2n-4 for n >= 3.
    */
    int maxShots;

    if (n == 2)
        maxShots = 2;
    else
        maxShots = 2 * n - 4;

    int *shots = (int *)malloc(maxShots * sizeof(int));

    int numberOfShots;

    generateStrategy(n, shots, &numberOfShots);

    printf("\nShooting sequence:\n");

    for (int i = 0; i < numberOfShots; i++)
        printf("%d ", shots[i]);

    printf("\n");

    printf("\nNumber of shots = %d\n", numberOfShots);

    /*
        Validate the strategy.
    */
    if (validateStrategy(n, shots, numberOfShots))
        printf("Strategy VALID: target is guaranteed to be hit.\n");
    else
        printf("Strategy INVALID.\n");

    free(shots);

    return 0;
}