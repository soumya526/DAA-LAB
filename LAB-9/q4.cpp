#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int distance;
    int fuel;
} Station;

int heap[MAX];
int heapSize = 0;

/* Swap two values */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert fuel into the max-heap */
void insertHeap(int fuel) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] < fuel) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = fuel;
}

/* Remove the maximum fuel amount */
int removeMax() {
    int maxFuel = heap[1];
    int last = heap[heapSize--];

    int i = 1;
    int child;

    while (2 * i <= heapSize) {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            heap[child + 1] > heap[child]) {
            child++;
        }

        if (last >= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return maxFuel;
}

/* Sort stations by distance using insertion sort */
void sortStations(Station stations[], int n) {
    int i, j;
    Station key;

    for (i = 1; i < n; i++) {
        key = stations[i];
        j = i - 1;

        while (j >= 0 &&
               stations[j].distance > key.distance) {
            stations[j + 1] = stations[j];
            j--;
        }

        stations[j + 1] = key;
    }
}

/* Minimum refuelling stops */
int minRefuelStops(int D, int F,
                   Station stations[], int n) {
    int i = 0;
    int stops = 0;
    long long reachable = F;

    heapSize = 0;

    while (reachable < D) {

        /* Add all stations currently reachable */
        while (i < n &&
               stations[i].distance <= reachable) {
            insertHeap(stations[i].fuel);
            i++;
        }

        /* No reachable station can provide more fuel */
        if (heapSize == 0)
            return -1;

        /* Choose the largest available fuel amount */
        reachable += removeMax();
        stops++;
    }

    return stops;
}

int main() {
    int D, F, n, i;
    Station stations[MAX];

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    if (D < 0 || F < 0 || n < 0 || n >= MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter distance and fuel for station %d: ",
               i + 1);

        scanf("%d %d",
              &stations[i].distance,
              &stations[i].fuel);

        if (stations[i].distance < 0 ||
            stations[i].fuel < 0 ||
            stations[i].distance > D) {
            printf("Invalid station data.\n");
            return 1;
        }
    }

    sortStations(stations, n);

    int result = minRefuelStops(D, F, stations, n);

    if (result == -1) {
        printf("\nTarget cannot be reached.\n");
    } else {
        printf("\nMinimum refuelling stops = %d\n", result);
    }

    return 0;
}