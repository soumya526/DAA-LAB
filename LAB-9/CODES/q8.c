#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

int minMeetingRooms(int start[], int end[], int n)
{
    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    int i = 0, j = 0;
    int rooms = 0;
    int maxRooms = 0;

    while (i < n)
    {
        if (start[i] < end[j])
        {
            rooms++;

            if (rooms > maxRooms)
                maxRooms = rooms;

            i++;
        }
        else
        {
            rooms--;
            j++;
        }
    }

    return maxRooms;
}

int main()
{
    int n;

    printf("Enter the number of meetings: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of meetings must be positive.\n");
        return 0;
    }

    int start[n], end[n];

    printf("Enter the start and end times of each meeting:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &start[i], &end[i]);

        if (start[i] >= end[i])
        {
            printf("Invalid meeting interval.\n");
            return 0;
        }
    }

    int result = minMeetingRooms(start, end, n);

    printf("Minimum number of meeting rooms required: %d\n", result);

    return 0;
}