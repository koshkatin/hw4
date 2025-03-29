void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair) {
    Node<Key, Value>* current = root_;
    Node<Key, Value>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (keyValuePair.first < current->getKey()) {
            current = current->getLeft();
        } else if (keyValuePair.first > current->getKey()) {
            current = current->getRight();
        } else {
            // Key already exists, update the value
            current->setValue(keyValuePair.second);
            return;
        }
    }

    // Insert the new node
    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    if (parent == nullptr) {
        root_ = newNode; // Tree was empty
    } else if (keyValuePair.first < parent->getKey()) {
        parent->setLeft(newNode);
    } else {
        parent->setRight(newNode);
    }
}