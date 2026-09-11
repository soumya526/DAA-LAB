#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;       // +1 = birth, -1 = death
} Event;

/*
    Comparator for qsort.

    Events are sorted by year.

    If two events have the same year,
    DEATH (-1) comes before BIRTH (+1).
*/
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    // Death (-1) before birth (+1)
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of scientists.\n");
        return 1;
    }

    /*
        Each scientist produces two events:
        one birth and one death.
    */
    Event *events =
        (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*
        Input birth and death years.
    */
    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("\nScientist %d\n", i + 1);

        printf("Birth year: ");
        scanf("%d", &birth);

        printf("Death year: ");
        scanf("%d", &death);

        events[2 * i].year = birth;
        events[2 * i].type = +1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    /*
        Sort all events.
    */
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int bestYear = 0;

    /*
        Scan events in chronological order.
    */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == -1)
        {
            // Scientist died
            current--;
        }
        else
        {
            // Scientist was born
            current++;

            /*
                After a birth, check whether
                we have a new maximum.
            */
            if (current > maximum)
            {
                maximum = current;
                bestYear = events[i].year;
            }
        }
    }

    printf("\n----------------------------------\n");
    printf("Maximum scientists alive = %d\n", maximum);
    printf("A time of maximum overlap  = %d\n", bestYear);
    printf("----------------------------------\n");

    free(events);

    return 0;
}