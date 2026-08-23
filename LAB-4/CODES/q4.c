#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type;   // +1 = entry, -1 = exit
} Event;

// Compare events according to time
int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main() {
    int n;

    printf("Enter number of persons: ");
    scanf("%d", &n);

    Event events[2 * n];

    printf("Enter entry time and exit time for each person:\n");

    for (int i = 0; i < n; i++) {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        // Entry event
        events[2 * i].time = entry;
        events[2 * i].type = 1;

        // Exit event
        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    // Sort all 2n events
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    // Process events
    for (int i = 0; i < 2 * n; i++) {

        current += events[i].type;

        if (current > maximum) {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum number of people present = %d\n", maximum);
    printf("Time when maximum people were present = %d\n", maxTime);

    return 0;
}