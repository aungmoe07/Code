#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Struct to represent cargo
struct Cargo {
    string name;
    double weight;
};

//Bubble Sort (Basic)
int bubbleSort(vector<Cargo>& arr) {
    int comparisons = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j].weight < arr[j + 1].weight) { // Descending order
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return comparisons;
}

// QuickSort (Advanced)
int qsComparisons = 0;

int partition(vector<Cargo>& arr, int low, int high) {
    double pivot = arr[high].weight;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        qsComparisons++;
        if (arr[j].weight > pivot) { // Descending order
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Cargo>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void displayCargo(const vector<Cargo>& arr) {
    for (const auto& item : arr) {
        cout << "[" << item.name << ": " << item.weight << "kg] ";
    }
    cout << endl;
}

int main() {
    // 12 Sample Cargo Weights
    vector<Cargo> logisticsData = {
        {"Crate A", 45.5}, {"Crate B", 12.0}, {"Crate C", 78.2},
        {"Crate D", 33.1}, {"Crate E", 90.0}, {"Crate F", 15.5},
        {"Crate G", 55.3}, {"Crate H", 42.1}, {"Crate I", 66.8},
        {"Crate J", 21.4}, {"Crate K", 88.5}, {"Crate L", 10.2}
    };

    vector<Cargo> dataForBubble = logisticsData;
    vector<Cargo> dataForQuick = logisticsData;

    cout << "--- Swift-Load Logistics: Sorting Analysis ---\n" << endl;

    // Run Bubble Sort
    cout << "Running Bubble Sort (Basic)..." << endl;
    int bCount = bubbleSort(dataForBubble);
    displayCargo(dataForBubble);
    cout << "Total Comparisons: " << bCount << "\n" << endl;

    // Run QuickSort
    cout << "Running QuickSort (Advanced)..." << endl;
    quickSort(dataForQuick, 0, dataForQuick.size() - 1);
    displayCargo(dataForQuick);
    cout << "Total Comparisons: " << qsComparisons << "\n" << endl;

    return 0;
}