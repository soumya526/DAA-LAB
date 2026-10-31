#include <stdio.h>
#include <stdlib.h>

// Structure to represent a fuel station
typedef struct {
    int dist;
    int fuel;
} Station;

// Compare function to sort stations by distance from origin
int compareStations(const void *a, const void *b) {
    return ((Station*)a)->dist - ((Station*)b)->dist;
}

// ---- Max-Heap Implementation ----
int heap[100000];
int heap_size = 0;

void push(int val) {
    int i = heap_size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] < val) {
            heap[i] = heap[p];
            i = p;
        } else {
            break;
        }
    }
    heap[i] = val;
}

int pop() {
    if (heap_size == 0) return -1;
    int max_val = heap[0];
    int val = heap[--heap_size];
    int i = 0;
    
    while (i * 2 + 1 < heap_size) {
        int child = i * 2 + 1;
        if (child + 1 < heap_size && heap[child + 1] > heap[child]) {
            child++;
        }
        if (heap[child] > val) {
            heap[i] = heap[child];
            i = child;
        } else {
            break;
        }
    }
    heap[i] = val;
    return max_val;
}

int is_empty() {
    return heap_size == 0;
}
// ---------------------------------

// Function to calculate minimum refueling stops
int minRefuelStops(int target, int startFuel, Station* stations, int numStations) {
    // Sort stations by their distance from the starting point
    qsort(stations, numStations, sizeof(Station), compareStations);
    
    int stops = 0;
    int current_fuel = startFuel;
    int current_pos = 0;
    heap_size = 0; // Reset heap for safety

    // Iterate through all stations, plus a dummy target station
    for (int i = 0; i <= numStations; i++) {
        int next_dist = (i == numStations) ? target : stations[i].dist;
        int next_fuel = (i == numStations) ? 0 : stations[i].fuel;
        
        int distance_to_travel = next_dist - current_pos;
        
        // While we don't have enough fuel to reach the next point
        while (current_fuel < distance_to_travel) {
            if (is_empty()) {
                return -1; // Cannot reach the target
            }
            // Greedily take the maximum fuel from stations we've passed
            current_fuel += pop();
            stops++;
        }
        
        // Travel to the next station
        current_fuel -= distance_to_travel;
        current_pos = next_dist;
        
        // Add current station's fuel to our available options (Max-Heap)
        if (i < numStations) {
            push(next_fuel);
        }
    }
    
    return stops;
}

int main() {
    int target = 100;
    int startFuel = 10;
    
    Station stations[] = {
        {10, 60},
        {20, 30},
        {30, 30},
        {60, 40}
    };
    int numStations = sizeof(stations) / sizeof(stations[0]);
    
    printf("Target Distance: %d\n", target);
    printf("Initial Fuel: %d\n", startFuel);
    
    int result = minRefuelStops(target, startFuel, stations, numStations);
    
    if (result == -1) {
        printf("It is impossible to reach the target.\n");
    } else {
        printf("Minimum number of refueling stops required: %d\n", result);
    }
    
    return 0;
}