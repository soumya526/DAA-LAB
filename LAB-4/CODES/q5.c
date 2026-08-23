#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

// Compare intervals by starting time
int compare(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->start - i2->start;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval intervals[n];
    Interval result[n];

    // Input
    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);
    }

    // Step 1: Sort intervals by starting time
    qsort(intervals, n, sizeof(Interval), compare);

    // Step 2: Merge overlapping intervals
    int count = 0;

    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    for (int i = 1; i < n; i++) {

        // Overlapping intervals
        if (intervals[i].start <= currentEnd) {

            if (intervals[i].end > currentEnd)
                currentEnd = intervals[i].end;
        }

        // Non-overlapping interval
        else {
            result[count].start = currentStart;
            result[count].end = currentEnd;
            count++;

            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    // Store the final interval
    result[count].start = currentStart;
    result[count].end = currentEnd;
    count++;

    // Output
    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n",
               result[i].start,
               result[i].end);
    }

    return 0;
}