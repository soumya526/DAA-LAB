#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 2001

char str[MAX_N][MAX_LEN];

/* Calculate suffix-prefix overlap */
int overlap(char a[], char b[])
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    int max = (lenA < lenB) ? lenA : lenB;

    for (int k = max; k > 0; k--)
    {
        if (strncmp(a + lenA - k, b, k) == 0)
            return k;
    }

    return 0;
}

/* Check whether a string occurs inside another string */
int contains(char a[], char b[])
{
    return strstr(a, b) != NULL;
}

/* Remove duplicates and strings contained in other strings */
void removeRedundant(int *n)
{
    int keep[MAX_N];

    for (int i = 0; i < *n; i++)
        keep[i] = 1;

    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            if (i == j)
                continue;

            if (contains(str[j], str[i]))
            {
                /* Keep only one copy of duplicate strings */
                if (strcmp(str[i], str[j]) == 0)
                {
                    if (i < j)
                        keep[j] = 0;
                    else
                        keep[i] = 0;
                }
                else
                {
                    keep[i] = 0;
                }

                break;
            }
        }
    }

    int count = 0;

    for (int i = 0; i < *n; i++)
    {
        if (keep[i])
        {
            if (count != i)
                strcpy(str[count], str[i]);

            count++;
        }
    }

    *n = count;
}

/* Greedy superstring construction */
void greedySuperstring(int n)
{
    while (n > 1)
    {
        int maxOverlap = -1;
        int first = 0, second = 1;

        /* Find the pair with maximum overlap */
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                int current = overlap(str[i], str[j]);

                if (current > maxOverlap)
                {
                    maxOverlap = current;
                    first = i;
                    second = j;
                }
            }
        }

        int lenFirst = strlen(str[first]);

        /* Append only the non-overlapping part */
        strcat(str[first], str[second] + maxOverlap);

        /* Remove the second string */
        for (int i = second; i < n - 1; i++)
            strcpy(str[i], str[i + 1]);

        n--;
    }

    printf("\nGreedy superstring: %s\n", str[0]);
    printf("Length of superstring: %zu\n", strlen(str[0]));
}

int main()
{
    int n;

    printf("Enter the number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_N)
    {
        printf("Invalid number of strings.\n");
        return 0;
    }

    printf("Enter the strings without spaces:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%2000s", str[i]);
    }

    removeRedundant(&n);

    greedySuperstring(n);

    return 0;
}