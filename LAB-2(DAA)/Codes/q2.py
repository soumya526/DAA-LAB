import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("merge_growth.csv")

plt.figure(figsize=(8,6))

plt.plot(data["n"],
         data["MergeSort"],
         marker='o',
         label="Merge Sort")

plt.plot(data["n"],
         data["ModifiedMergeSort"],
         marker='s',
         label="Modified Merge Sort")

plt.title("Merge Sort vs Modified Merge Sort")

plt.xlabel("Input Size (n)")
plt.ylabel("Growth")

plt.grid(True)

plt.legend()

plt.tight_layout()

plt.show()