#include <stdio.h>
#include <limits.h>

unsigned long long collatz_next(unsigned long long n) {

    if (n % 2 == 0)
        return n / 2;

    if (n > (ULLONG_MAX - 1) / 3) {
        printf("Overflow detected for 3n + 1.\n");
        return 0;
    }

    return 3 * n + 1;
}

void analyze(unsigned long long n) {

    unsigned long long start = n;
    unsigned long long maxValue = n;

    unsigned long long steps = 0;

    printf("\nTrajectory for %llu:\n", start);

    printf("%llu", n);

    while (n != 1) {

        n = collatz_next(n);

        if (n == 0)
            return;

        if (n > maxValue)
            maxValue = n;

        printf(" -> %llu", n);

        steps++;
    }

    printf("\nSteps = %llu", steps);
    printf("\nMaximum value reached = %llu\n", maxValue);
}

int main() {

    unsigned long long a, b;

    printf("Enter interval [a,b]: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || b < a) {

        printf("Invalid interval.\n");

        return 1;
    }

    for (unsigned long long n = a; n <= b; n++) {

        analyze(n);

        if (n == ULLONG_MAX)
            break;
    }

    return 0;
}