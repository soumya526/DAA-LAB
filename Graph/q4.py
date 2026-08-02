import matplotlib.pyplot as plt

# Number of disks
n = list(range(1, 16))

# Total moves = 2^n - 1
moves = [(2**i) - 1 for i in n]

plt.figure(figsize=(8,5))
plt.plot(n, moves, marker='o', linewidth=2)

plt.title("Tower of Hanoi")
plt.xlabel("Number of Disks (n)")
plt.ylabel("Number of Moves (2^n - 1)")
plt.grid(True)

plt.xticks(n)

plt.show()