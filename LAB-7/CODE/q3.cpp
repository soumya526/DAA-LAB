#include <stdio.h>
#include <limits.h>

#define MAX 64

long long dp[MAX];
int split[MAX];

/* Calculate 2^n */
long long powerOfTwo(int n)
{
    long long result = 1;

    for (int i = 0; i < n; i++)
        result *= 2;

    return result;
}

/*
   Standard 3-peg Tower of Hanoi.

   Moves n disks from source to destination
   using auxiliary peg.
*/
void hanoi3(int n, char source, char auxiliary, char destination)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, destination, auxiliary);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, source, destination);
}

/*
   Reve's Puzzle using 4 pegs.

   source      = source peg
   destination = destination peg
   aux1, aux2  = auxiliary pegs
*/
void hanoi4(int n, char source, char aux1,
            char aux2, char destination)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }

    /*
       Best split obtained from DP.
       k = number of smaller disks moved first.
    */
    int k = split[n];

    /*
       Step 1:
       Move k smaller disks using all 4 pegs.
    */
    hanoi4(k, source, aux2, destination, aux1);

    /*
       Step 2:
       Move remaining n-k disks using 3 pegs.
    */
    hanoi3(n - k, source, aux2, destination);

    /*
       Step 3:
       Move k disks to destination using all 4 pegs.
    */
    hanoi4(k, aux1, source, aux2, destination);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n >= MAX)
    {
        printf("Invalid number of disks.\n");
        return 1;
    }

    /*
       Dynamic Programming
       dp[n] = minimum moves for n disks
    */

    dp[0] = 0;

    if (n >= 1)
    {
        dp[1] = 1;
        split[1] = 0;
    }

    for (int i = 2; i <= n; i++)
    {
        dp[i] = LLONG_MAX;

        for (int k = 1; k < i; k++)
        {
            long long moves =
                2 * dp[k]
                + powerOfTwo(i - k)
                - 1;

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n", dp[n]);

    printf("\nOptimal split:\n");

    for (int i = 2; i <= n; i++)
        printf("n = %d : k = %d\n", i, split[i]);

    printf("\nMoves:\n");

    hanoi4(n, 'A', 'B', 'C', 'D');

    return 0;
}