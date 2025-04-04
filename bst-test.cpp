#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // // Binary Search Tree tests
    // BinarySearchTree<char,int> bt;

    // // Insert a bunch of nodes into the Binary Search Tree
    // bt.insert(std::make_pair('f', 6));
    // bt.insert(std::make_pair('d', 4));
    // bt.insert(std::make_pair('j', 10));
    // bt.insert(std::make_pair('b', 2));
    // bt.insert(std::make_pair('e', 5));
    // bt.insert(std::make_pair('g', 7));
    // bt.insert(std::make_pair('k', 11));
    // bt.insert(std::make_pair('a', 1));
    // bt.insert(std::make_pair('c', 3));
    // bt.insert(std::make_pair('i', 9));
    // bt.insert(std::make_pair('h', 8));

    // bt.print();

    // cout << "Binary Search Tree contents (in-order traversal):" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // // Test find
    // if(bt.find('g') != bt.end()) {
    //     cout << "Found g" << endl;
    // }
    // else {
    //     cout << "Did not find g" << endl;
    // }

    // // Test remove
    // cout << "Erasing g" << endl;
    // bt.remove('g');
    // bt.print();

    //-------------------------------------------
    
    // AVL Tree Tests
    AVLTree<char,int> at;

    // Insert a bunch of nodes into the AVL Tree
    at.insert(std::make_pair('f', 6));
    at.insert(std::make_pair('d', 4));
    at.insert(std::make_pair('j', 10));
    at.insert(std::make_pair('b', 2));
    at.insert(std::make_pair('e', 5));
    at.insert(std::make_pair('g', 7));
    at.insert(std::make_pair('k', 11));
    at.insert(std::make_pair('a', 1));
    at.insert(std::make_pair('c', 3));
    at.insert(std::make_pair('i', 9));
    at.insert(std::make_pair('h', 8));

    cout << "\nAVLTree contents (in-order traversal):" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    // Test find
    if(at.find('g') != at.end()) {
        cout << "Found g" << endl;
    }
    else {
        cout << "Did not find g" << endl;
    }
    at.print();

    // Test remove
    cout << "Erasing g" << endl;
    at.remove('g');
    at.print();

    //------------------------------------------

    // // AVL Tree Tests
    // AVLTree<int,int> at;

    // // Insert a bunch of nodes into the AVL Tree
    // at.insert(std::make_pair(2, 6));
    // at.print();
    // at.insert(std::make_pair(1, 4));
    // at.print();
    // at.insert(std::make_pair(0, 2));
    // at.print();

    // cout << "\nAVLTree contents (in-order traversal):" << endl;
    // for(AVLTree<int,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }


    // // Test find
    // if(at.find(1) != at.end()) {
    //     cout << "Found 1" << endl;
    // }
    // else {
    //     cout << "Did not find 1" << endl;
    // }

    // // Test remove
    // cout << "Erasing g" << endl;
    // at.remove(1);

    

    return 0;
}
