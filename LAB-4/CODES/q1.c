#include <stdio.h>
#include <string.h>

#define MAX 100

struct Item {
    int number;
    char colour;
};

void sortByColour(struct Item a[], int n) {
    struct Item red[MAX], blue[MAX], yellow[MAX];

    int r = 0, b = 0, y = 0;

    // Separate items according to colour
    for (int i = 0; i < n; i++) {
        if (a[i].colour == 'R') {
            red[r++] = a[i];
        }
        else if (a[i].colour == 'B') {
            blue[b++] = a[i];
        }
        else if (a[i].colour == 'Y') {
            yellow[y++] = a[i];
        }
    }

    // Combine: Red -> Blue -> Yellow
    int k = 0;

    for (int i = 0; i < r; i++)
        a[k++] = red[i];

    for (int i = 0; i < b; i++)
        a[k++] = blue[i];

    for (int i = 0; i < y; i++)
        a[k++] = yellow[i];
}


int main() {
    struct Item a[MAX];
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter number and colour (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %c", &a[i].number, &a[i].colour);
    }

    sortByColour(a, n);

    printf("\nSorted by colour:\n");

    for (int i = 0; i < n; i++) {
        printf("(%d, %c) ", a[i].number, a[i].colour);
    }

    printf("\n");

    return 0;
}