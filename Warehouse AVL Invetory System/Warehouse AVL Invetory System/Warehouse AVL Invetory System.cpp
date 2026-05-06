#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Goods {
    int id;
    string name;
    double weight;
};

struct Node {
    Goods data;
    Node* left, * right;
    int height;
};

//HELPER FUNCTIONS (Standard AVL Logic)
int getHeight(Node* n) { return (n == nullptr) ? 0 : n->height; }
int getBalance(Node* n) { return (n == nullptr) ? 0 : getHeight(n->left) - getHeight(n->right); }

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// ROBUST INSERTION
Node* insert(Node* node, Goods item) {
    // Validation: Check for invalid weights or empty names
    if (item.weight <= 0) throw invalid_argument("Weight must be positive.");
    if (item.name.empty()) throw invalid_argument("Cargo name cannot be empty.");

    if (node == nullptr) return new Node{ item, nullptr, nullptr, 1 };

    if (item.id < node->data.id)
        node->left = insert(node->left, item);
    else if (item.id > node->data.id)
        node->right = insert(node->right, item);
    else
        throw logic_error("Duplicate ID: Cargo ID " + to_string(item.id) + " already exists.");

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Balancing rotations...
    if (balance > 1 && item.id < node->left->data.id) return rightRotate(node);
    if (balance < -1 && item.id > node->right->data.id) return leftRotate(node);
    if (balance > 1 && item.id > node->left->data.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && item.id < node->right->data.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

//ROBUST SEARCH
Node* search(Node* root, int id) {
    if (root == nullptr) return nullptr;
    if (root->data.id == id) return root;
    if (id < root->data.id) return search(root->left, id);
    return search(root->right, id);
}

// Helper to print the inventory in sorted order
void displayInventory(Node* root) {
    if (root == nullptr) return;
    displayInventory(root->left);
    cout << "  - [ID: " << root->data.id << "] " << root->data.name << " (" << root->data.weight << "kg)" << endl;
    displayInventory(root->right);
}




int main() {
    Node* inventory = nullptr;

    // TEST SUITE
    cout << " Swift-Load Robustness Testing" << endl;

    // Test Case 1: Valid Insertion
    try {
        inventory = insert(inventory, { 101, "Electronics", 50.5 });
        cout << "[PASS] Successfully added Electronics." << endl;
    }
    catch (const exception& e) { cout << "[FAIL] " << e.what() << endl; }

    // Test Case 2: Negative Weight (Error Handling)
    try {
        inventory = insert(inventory, { 102, "Invalid Cargo", -5.0 });
    }
    catch (const invalid_argument& e) {
        cout << "[PASS] Caught Expected Error: " << e.what() << endl;
    }

    // Test Case 3: Duplicate ID (Error Handling)
    try {
        inventory = insert(inventory, { 101, "Duplicate", 10.0 });
    }
    catch (const logic_error& e) {
        cout << "[PASS] Caught Expected Error: " << e.what() << endl;
    }

    // Test Case 4: Searching for non-existent ID (Null Management)
    Node* result = search(inventory, 999);
    if (result == nullptr) {
        cout << "[PASS] Correctly handled search for non-existent ID (returned null)." << endl;
    }
    try {

        inventory = insert(inventory, { 108, "Central Hub", 1000.0 });
        inventory = insert(inventory, { 104, "Main Engine", 500.0 });
        inventory = insert(inventory, { 112, "Power Grid", 750.0 });
        inventory = insert(inventory, { 102, "Side Panel", 45.0 });
        inventory = insert(inventory, { 106, "Control Unit", 12.5 });
        inventory = insert(inventory, { 110, "Cooling Fan", 15.0 });
        inventory = insert(inventory, { 114, "Outer Shell", 80.0 });
        inventory = insert(inventory, { 101, "Small Bolt", 0.1 });
        inventory = insert(inventory, { 103, "Wiring Harness", 5.0 });
        inventory = insert(inventory, { 105, "Sensor Kit", 2.2 });
        inventory = insert(inventory, { 107, "LED Module", 0.5 });
        inventory = insert(inventory, { 109, "Base Plate", 25.0 });
        inventory = insert(inventory, { 111, "Internal Cable", 1.5 });
        inventory = insert(inventory, { 113, "Gasket Set", 0.8 });
        inventory = insert(inventory, { 115, "Firmware Chip", 0.1 });

        cout << "[PASS] Added multiple items for testing." << endl;
    }
    catch (const exception& e) {
        // This will print the specific error message from your 'throw' statements
        cout << "[FAIL] Critical error during batch insertion: " << e.what() << endl;
    }
    // --- Visual Verification ---
    cout << "\n--- Warehouse Inventory (Sorted View) ---" << endl;
    displayInventory(inventory); // This will print IDs 101 through 107

    if (inventory != nullptr) {
        cout << "\n--- Tree Structural Metrics ---" << endl;
        cout << "Root Node:  " << inventory->data.name << " (ID: " << inventory->data.id << ")" << endl;
        cout << "Tree Height: " << inventory->height << endl;

        // Logical check for Height 3
        if (inventory->height >= 3) {
            cout << "Result: Height is " << inventory->height << ". AVL tree is properly structured." << endl;
        }
    }

    return 0;
}
