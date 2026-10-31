#include <stdio.h>
#include <string.h>

#define MAX 1000
#define CHARSET 256

int main() {
    char str[MAX], result[MAX];
    int freq[CHARSET] = {0};
    int used[CHARSET] = {0};
    int n, k, i, j;
    int remaining, best;
    int lastPos[CHARSET];

    printf("Enter the string: ");
    scanf("%999s", str);

    printf("Enter K: ");
    scanf("%d", &k);

    n = strlen(str);

    if (k < 0) {
        printf("Invalid value of K.\n");
        return 1;
    }

    if (k <= 1) {
        printf("Reorganised string: %s\n", str);
        return 0;
    }

    for (i = 0; i < CHARSET; i++) {
        lastPos[i] = -k;
    }

    for (i = 0; i < n; i++) {
        freq[(unsigned char)str[i]]++;
    }

    remaining = n;

    for (i = 0; i < n; i++) {
        best = -1;

        /* Select the most frequent eligible character */
        for (j = 0; j < CHARSET; j++) {
            if (freq[j] > 0 &&
                i - lastPos[j] >= k) {

                if (best == -1 ||
                    freq[j] > freq[best]) {
                    best = j;
                }
            }
        }

        if (best == -1) {
            printf("Not possible\n");
            return 0;
        }

        result[i] = (char)best;
        freq[best]--;
        lastPos[best] = i;
        remaining--;
    }

    result[n] = '\0';

    printf("Reorganised string: %s\n", result);

    return 0;
}