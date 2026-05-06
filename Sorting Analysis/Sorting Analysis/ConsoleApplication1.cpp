#include <iostream>
#include <vector>
#include <string>
#include <chrono>   // For high-precision timing
#include <iomanip>

using namespace std;
using namespace std::chrono;


struct Cargo {
    string name;
    double weight;
};

// Global counters for QuickSort metrics
int qsComparisons = 0;
int qsSwaps = 0;

// --- Bubble Sort (Basic) ---
pair<int, int> bubbleSort(vector<Cargo>& arr) {
    int comparisons = 0;
    int swaps = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j].weight < arr[j + 1].weight) { // Descending order
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
    return { comparisons, swaps };
}

// --- QuickSort (Advanced) ---
int partition(vector<Cargo>& arr, int low, int high) {
    double pivot = arr[high].weight;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        qsComparisons++;
        if (arr[j].weight > pivot) { // Descending order
            i++;
            swap(arr[i], arr[j]);
            qsSwaps++;
        }
    }
    swap(arr[i + 1], arr[high]);
    qsSwaps++;
    return (i + 1);
}

void quickSort(vector<Cargo>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<Cargo> logisticsData = {
        {"Crate A", 45.5}, {"Crate B", 12.0}, {"Crate C", 78.2},
        {"Crate D", 33.1}, {"Crate E", 90.0}, {"Crate F", 15.5},
        {"Crate G", 55.3}, {"Crate H", 42.1}, {"Crate I", 66.8},
        {"Crate J", 21.4}, {"Crate K", 88.5}, {"Crate L", 10.2}
    };

    // Calculate Static Memory (Size of the data structure)
    size_t dataMemory = logisticsData.size() * sizeof(Cargo);

    cout << "--- Swift-Load Logistics: Sorting Performance Analysis ---\n" << endl;
    cout << "Total Items: " << logisticsData.size() << endl;
    cout << "Static Memory Used by Data: " << dataMemory << " bytes\n" << endl;

    // --- Bubble Sort Execution ---
    vector<Cargo> dataForBubble = logisticsData;
    auto startB = high_resolution_clock::now();
    pair<int, int> bMetrics = bubbleSort(dataForBubble);
    auto stopB = high_resolution_clock::now();
    auto durationB = duration_cast<nanoseconds>(stopB - startB);

    cout << "[ALGORITHM: BUBBLE SORT]" << endl;
    cout << "Comparisons: " << bMetrics.first << endl;
    cout << "Swaps:       " << bMetrics.second << endl;
    cout << "Time Taken:  " << durationB.count() << " nanoseconds" << endl;
    cout << "Auxiliary Memory (Stack): O(1) - Constant" << endl;
    cout << "------------------------------------------" << endl;

    // --- QuickSort Execution ---
    vector<Cargo> dataForQuick = logisticsData;
    auto startQ = high_resolution_clock::now();
    quickSort(dataForQuick, 0, dataForQuick.size() - 1);
    auto stopQ = high_resolution_clock::now();
    auto durationQ = duration_cast<nanoseconds>(stopQ - startQ);

    cout << "[ALGORITHM: QUICKSORT]" << endl;
    cout << "Comparisons: " << qsComparisons << endl;
    cout << "Swaps:       " << qsSwaps << endl;
    cout << "Time Taken:  " << durationQ.count() << " nanoseconds" << endl;
    cout << "Auxiliary Memory (Stack): O(log n) - Recursive Space" << endl;
    cout << "------------------------------------------" << endl;

    return 0;
}
