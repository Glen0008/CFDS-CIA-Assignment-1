# Importing necessary libraries
import random
import time
import os
import psutil
from memory_profiler import memory_usage

# Defining functions

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    merged = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
    merged += left[i:]
    merged += right[j:]
    return merged

# Calculating metrics:

def run_merge_sort():
    size = 100000  # You can increase to 1_000_000 for a bigger test
    arr = [random.randint(0, 1000000) for _ in range(size)]

    # Start CPU time tracking
    process = psutil.Process(os.getpid())
    cpu_start = process.cpu_times().user

    # Start wall-clock time
    start_time = time.time()

    # Run the merge sort
    sorted_arr = merge_sort(arr)

    # End wall-clock time
    end_time = time.time()

    # End CPU time tracking
    cpu_end = process.cpu_times().user

    print(f"Wall-clock time taken: {end_time - start_time:.4f} seconds")
    print(f"CPU time taken: {cpu_end - cpu_start:.4f} seconds")

if __name__ == "__main__":
    mem_usage = memory_usage(run_merge_sort)
    print(f"Peak memory usage: {max(mem_usage):.2f} MiB")

# With additional profiling using psutil, we recorded both wall-clock and CPU time for the Python Merge Sort implementation.
#  The CPU time was closely aligned with the wall-clock time (~1.73 seconds), showing efficient CPU utilization.
#  Peak memory usage remained consistent (~56.15 MiB), and the Python code remained highly readable and beginner-friendly.
