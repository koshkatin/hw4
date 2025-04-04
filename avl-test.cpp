#include "avlbst.h"
#include <set>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    const int numElements = 30;

    std::srand(6768); // Fixed seed for reproducibility

    AVLTree<int, int> tree;
    std::set<int> keys;

    // Generate 30 unique random keys
    while (keys.size() < numElements) {
        int key = std::rand() % 1000;
        keys.insert(key);
    }

    std::cout << "Inserting keys:\n";
    for (int key : keys) {
        int value = std::rand() % 1000;
        tree.insert(std::make_pair(key, value));
        std::cout << "  key: " << key << ", value: " << value << "\n";
        tree.print();
    }

    std::cout << "Inserted " << keys.size() << " unique elements into the AVL Tree.\n";

    return 0;
}