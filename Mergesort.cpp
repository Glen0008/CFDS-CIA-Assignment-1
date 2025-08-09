#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <sys/resource.h> // for getrusage
using namespace std;

// Merge function for MergeSort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// MergeSort recursive function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to get memory usage in MB
double getMemoryUsageMB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss / 1024.0; // Convert KB to MB
}

int main() {
    int n = 100000; // Array size
    vector<int> arr(n);

    // Fill with random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    // Get starting memory
    double startMemory = getMemoryUsageMB();

    // Start measuring wall-clock time
    auto start = chrono::high_resolution_clock::now();

    // Start measuring CPU time
    clock_t cpuStart = clock();

    // Run MergeSort
    mergeSort(arr, 0, arr.size() - 1);

    // Stop measuring CPU time
    clock_t cpuEnd = clock();

    // Stop measuring wall-clock time
    auto end = chrono::high_resolution_clock::now();

    // Get ending memory
    double endMemory = getMemoryUsageMB();

    // Calculate execution time in seconds
    chrono::duration<double> elapsed = end - start;
    double executionTime = elapsed.count();

    // Calculate CPU time in seconds
    double cpuTime = double(cpuEnd - cpuStart) / CLOCKS_PER_SEC;

    // Calculate memory usage difference
    double memoryUsed = endMemory - startMemory;

    // Output metrics
    cout << "Execution Time (Wall Clock): " << executionTime << " seconds\n";
    cout << "CPU Time: " << cpuTime << " seconds\n";
    cout << "Memory Used: " << memoryUsed << " MB\n";

    return 0;
}


/*C++ provided the fastest execution in our test, completing merge sort in under 1 second.
 Memory usage was minimal (about 0.625 MB), and the language’s control over memory and data structures helped keep performance optimal.
*/