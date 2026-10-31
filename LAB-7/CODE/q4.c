#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

/*
    Check whether switch i can be toggled.

    Switch 0 = rightmost switch.

    For i = 0:
        always allowed.

    For i > 0:
        switch immediately to the right must be ON
        and all switches further right must be OFF.
*/
int canToggle(unsigned int state, int i)
{
    if (i == 0)
        return 1;

    // Immediate right switch must be ON
    if ((state & (1U << (i - 1))) == 0)
        return 0;

    // All switches further right must be OFF
    for (int j = 0; j < i - 1; j++)
    {
        if (state & (1U << j))
            return 0;
    }

    return 1;
}

/*
    Toggle switch i.
*/
unsigned int toggleSwitch(unsigned int state, int i)
{
    return state ^ (1U << i);
}

/*
    Find minimum number of moves using BFS.
*/
int minimumMoves(int n)
{
    unsigned int totalStates = 1U << n;

    // Initial state: all switches ON
    unsigned int start = totalStates - 1;

    // Final state: all switches OFF
    unsigned int target = 0;

    int *distance = (int *)malloc(
        totalStates * sizeof(int));

    unsigned int *queue = (unsigned int *)malloc(
        totalStates * sizeof(unsigned int));

    if (distance == NULL || queue == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Initialize distances
    for (unsigned int i = 0; i < totalStates; i++)
        distance[i] = -1;

    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    distance[start] = 0;

    while (front < rear)
    {
        unsigned int current = queue[front++];

        if (current == target)
        {
            int answer = distance[current];

            free(distance);
            free(queue);

            return answer;
        }

        // Try toggling every switch
        for (int i = 0; i < n; i++)
        {
            if (canToggle(current, i))
            {
                unsigned int next =
                    toggleSwitch(current, i);

                // Visit state for the first time
                if (distance[next] == -1)
                {
                    distance[next] =
                        distance[current] + 1;

                    queue[rear++] = next;
                }
            }
        }
    }

    free(distance);
    free(queue);

    return -1;
}

/*
    Compact mathematical formula:
    
    M(n) = floor((2^(n+1) - 1) / 3)
*/
unsigned long long formulaMoves(int n)
{
    unsigned long long value = 1ULL << (n + 1);

    return (value - 1) / 3;
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_N)
    {
        printf("Enter n between 1 and %d.\n", MAX_N);
        return 1;
    }

    int bfsAnswer = minimumMoves(n);

    unsigned long long formulaAnswer =
        formulaMoves(n);

    printf("\nMinimum number of moves = %d\n",
           bfsAnswer);

    printf("Formula result             = %llu\n",
           formulaAnswer);

    if (bfsAnswer == formulaAnswer)
        printf("Algorithm validated: Both results match.\n");
    else
        printf("Error: Results do not match.\n");

    return 0;
}