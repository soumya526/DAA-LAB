import numpy as np
import matplotlib.pyplot as plt

# Values of n
n = np.arange(2, 30)

# Functions
f1 = np.ones_like(n)
f2 = np.log2(n)
f3 = 12 * np.sqrt(n)
f4 = 50 * np.sqrt(n)
f5 = n ** 0.51
f6 = (2**32) * n
f7 = n * np.log2(n)
f8 = n**2 - 324
f9 = 100 * n**2 + 6 * n
f10 = 2 * n**3
f11 = n ** (np.log2(n))
f12 = 3 ** n

# Plot
plt.figure(figsize=(14,8))

plt.plot(n, f1, label='1')
plt.plot(n, f2, label='log₂(n)')
plt.plot(n, f3, label='12√n')
plt.plot(n, f4, label='50√n')
plt.plot(n, f5, label='n^0.51')
plt.plot(n, f6, label='2³²·n')
plt.plot(n, f7, label='nlog₂n')
plt.plot(n, f8, label='n²−324')
plt.plot(n, f9, label='100n²+6n')
plt.plot(n, f10, label='2n³')
plt.plot(n, f11, label='n^(log₂n)')
plt.plot(n, f12, label='3ⁿ')

# Log scale is essential because the values differ enormously
plt.yscale('log')

plt.title("Comparison of Asymptotic Growth Functions")
plt.xlabel("n")
plt.ylabel("Function Value (Log Scale)")
plt.grid(True)
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()

plt.show()