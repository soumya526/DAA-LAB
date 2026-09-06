#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI acos(-1)

/* Recursive FFT */
void fft(double complex a[], int n, int invert)
{
    if (n == 1)
        return;

    /* Divide into even and odd elements */
    double complex *even =
        malloc((n / 2) * sizeof(double complex));

    double complex *odd =
        malloc((n / 2) * sizeof(double complex));

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    /* Recursive calls */
    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    /* Combine */
    double angle = 2 * PI / n;

    if (!invert)
        angle = -angle;

    double complex w = 1;
    double complex wn = cos(angle) + I * sin(angle);

    for (int k = 0; k < n / 2; k++)
    {
        double complex t = w * odd[k];

        a[k] = even[k] + t;
        a[k + n / 2] = even[k] - t;

        w *= wn;
    }

    free(even);
    free(odd);
}

/* Inverse FFT */
void inverseFFT(double complex a[], int n)
{
    fft(a, n, 1);

    for (int i = 0; i < n; i++)
        a[i] /= n;
}

/* Find next power of 2 */
int nextPowerOfTwo(int x)
{
    int n = 1;

    while (n < x)
        n *= 2;

    return n;
}

/* Convolution */
void convolution(double A[], int m,
                 double B[], int n)
{
    int resultSize = m + n - 1;

    /* FFT size */
    int N = nextPowerOfTwo(resultSize);

    double complex *FA =
        calloc(N, sizeof(double complex));

    double complex *FB =
        calloc(N, sizeof(double complex));

    /* Copy input vectors */
    for (int i = 0; i < m; i++)
        FA[i] = A[i];

    for (int i = 0; i < n; i++)
        FB[i] = B[i];

    /* FFT */
    fft(FA, N, 0);
    fft(FB, N, 0);

    /* Pointwise multiplication */
    for (int i = 0; i < N; i++)
        FA[i] = FA[i] * FB[i];

    /* Inverse FFT */
    inverseFFT(FA, N);

    /* Print result */
    printf("\nConvolution:\n");

    for (int i = 0; i < resultSize; i++)
    {
        printf("%.2lf ", creal(FA[i]));
    }

    printf("\n");

    free(FA);
    free(FB);
}

int main()
{
    int m, n;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    if (n < m)
    {
        printf("Error: n must be >= m.\n");
        return 0;
    }

    double *A = malloc(m * sizeof(double));
    double *B = malloc(n * sizeof(double));

    printf("\nEnter elements of A:\n");

    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("\nEnter elements of B:\n");

    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    convolution(A, m, B, n);

    free(A);
    free(B);

    return 0;
}