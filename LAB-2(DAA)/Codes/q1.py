import pandas as pd
import matplotlib.pyplot as plt

files = [
    "unsorted_array.csv",
    "sorted_array.csv",
    "singly_unsorted.csv",
    "singly_sorted.csv",
    "doubly_unsorted.csv",
    "doubly_sorted.csv"
]

titles = [
    "Unsorted Array",
    "Sorted Array",
    "Singly Linked Unsorted List",
    "Singly Linked Sorted List",
    "Doubly Linked Unsorted List",
    "Doubly Linked Sorted List"
]

for file, title in zip(files, titles):

    data = pd.read_csv(file)

    plt.figure(figsize=(10,6))

    plt.plot(data["n"], data["Search"], marker='o', label="Search")
    plt.plot(data["n"], data["Insert"], marker='o', label="Insert")
    plt.plot(data["n"], data["Delete"], marker='o', label="Delete")
    plt.plot(data["n"], data["Maximum"], marker='o', label="Maximum")
    plt.plot(data["n"], data["Minimum"], marker='o', label="Minimum")
    plt.plot(data["n"], data["Predecessor"], marker='o', label="Predecessor")
    plt.plot(data["n"], data["Successor"], marker='o', label="Successor")

    plt.yscale("log")      # Makes all curves visible
    plt.grid(True)
    plt.title(title)
    plt.xlabel("Input Size (n)")
    plt.ylabel("Theoretical Growth")
    plt.legend()
    plt.tight_layout()

    plt.show()