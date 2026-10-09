#include <stdio.h>

#define MAX 1000

int heap[MAX];
int heapSize = 0;

/* Swap two elements */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert an element into the max-heap */
void insertHeap(int value) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] < value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

/* Remove the maximum element */
int removeMax() {
    int maximum = heap[1];
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

    return maximum;
}

/* Return the maximum element */
int getMax() {
    return heap[1];
}

int main() {
    int n, i;
    int arr[MAX];
    int minimum = 0;
    int maximum;
    int deviation, minDeviation;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter the array elements:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);

        if (arr[i] <= 0) {
            printf("Elements must be positive.\n");
            return 1;
        }

        /* Make every odd element even */
        if (arr[i] % 2 != 0)
            arr[i] *= 2;

        insertHeap(arr[i]);

        if (i == 0 || arr[i] < minimum)
            minimum = arr[i];
    }

    maximum = getMax();
    minDeviation = maximum - minimum;

    while (heap[1] % 2 == 0) {
        maximum = removeMax();

        /* Divide the largest even element by 2 */
        maximum /= 2;

        if (maximum < minimum)
            minimum = maximum;

        insertHeap(maximum);

        deviation = getMax() - minimum;

        if (deviation < minDeviation)
            minDeviation = deviation;
    }

    printf("Minimum deviation = %d\n", minDeviation);

    return 0;
}