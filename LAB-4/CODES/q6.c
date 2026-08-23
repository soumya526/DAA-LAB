#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int point;
    int type;       // +1 = start, -1 = end
} Event;

// Sort events by point.
// If points are equal, START (+1) comes before END (-1)
// because endpoints are included in intervals.
int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    return e2->type - e1->type;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event events[2 * n];

    printf("Enter left and right endpoints:\n");

    for (int i = 0; i < n; i++) {
        int l, r;

        scanf("%d %d", &l, &r);

        // Starting event
        events[2 * i].point = l;
        events[2 * i].type = +1;

        // Ending event
        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int maxPoint = 0;

    // Sweep through all events
    for (int i = 0; i < 2 * n; i++) {

        current += events[i].type;

        if (current > maximum) {
            maximum = current;
            maxPoint = events[i].point;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", maxPoint);
    printf("Maximum number of intervals = %d\n", maximum);

    return 0;
}