import random
import matplotlib.pyplot as plt

# Generate random array
def generate_random_array(n):
    return [random.randint(0, 999) for _ in range(n)]

# Bubble Sort with Early Termination
def bubble_sort_optimized(arr):
    comparisons = 0
    n = len(arr)

    for i in range(n - 1):
        swapped = False
        for j in range(n - i - 1):
            comparisons += 1
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True

        if not swapped:
            break

    return comparisons

# Normal Bubble Sort
def bubble_sort_normal(arr):
    comparisons = 0
    n = len(arr)

    for i in range(n - 1):
        for j in range(n - i - 1):
            comparisons += 1
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

    return comparisons


sizes = list(range(100, 1001, 100))
optimized = []
normal = []

for n in sizes:
    arr1 = generate_random_array(n)
    arr2 = arr1.copy()

    optimized.append(bubble_sort_optimized(arr1))
    normal.append(bubble_sort_normal(arr2))

# Plotting
plt.figure(figsize=(10,6))

plt.plot(sizes, optimized, marker='o', linewidth=2,
         label='Optimized Bubble Sort')

plt.plot(sizes, normal, marker='s', linewidth=2,
         label='Normal Bubble Sort')

plt.title("Bubble Sort Comparison")
plt.xlabel("Input Size (n)")
plt.ylabel("Number of Comparisons")
plt.grid(True)
plt.legend()

plt.show()