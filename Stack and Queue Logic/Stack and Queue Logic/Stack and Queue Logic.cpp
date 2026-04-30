#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

// Data Structure for Cargo
struct Cargo {
	string id;
	string description;
};

// Data Structure for Truck
struct Truck {
	string licensePlate;
	string driverName;
};

void demostrateLogisticsFlow() {
	// 1. Queue: Truck Sequencing (FIFO)
	// Represents trucks waiting at the loadinng bay
	queue<Truck> loadingBay;

	loadingBay.push({ "SL-001", "John Doe" });
	loadingBay.push({ "SL-002", "Jane Smith" });
	loadingBay.push({ "SL-003", "Bob Wilson" });

	cout << "1. Truck Queue (FIFO)" << endl;
	while (!loadingBay.empty()) {
		Truck current = loadingBay.front();
		cout << "Processing Truck: " << current.licensePlate << " | Driver: " << current.driverName << endl;

		// 2. Stack: Cargo Loading (LIFO)
		// As we process each truck, we load it with cargo
		stack<Cargo> truckBed;
		cout << "   > Loading Cargo: [Box A], [Box B], [Box C]" << endl;
		truckBed.push({ "A1", "Electronics" });
		truckBed.push({ "B1", "Medical Supplies" });
		truckBed.push({ "C1", "Perishables" });

		cout << " > Unloading sequence at destination (LIFO):" << endl;
		while (!truckBed.empty()) {
			Cargo item = truckBed.top();
			cout << " ' - Unloaded: " << item.description << " (" << item.id << ")" << endl;
			truckBed.pop();
		}

		loadingBay.pop(); // Truck leaves the bay
		cout << "Truck " << current.licensePlate << " dispatched.\n" << endl;
	}
}

int main() {
	cout << " Swift-Load Logisitics: Operational Simulation\n" << endl;
	demostrateLogisticsFlow();
	return 0;
}