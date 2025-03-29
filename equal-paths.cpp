#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream> // for std::max

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int equalHelper(Node * root, bool& equal);

bool equalPaths(Node * root)
{
    // Add your code below
    if (!root) return true;

    bool equal = true;
    equalHelper(root, equal);
    return equal;
}

int equalHelper(Node * root, bool& equal)
{
    if (!root) return 0; 

    int leftResult = equalHelper(root->left, equal);
    int rightResult = equalHelper(root->right, equal);

    if (leftResult != 0 && rightResult != 0 && leftResult != rightResult) {
        equal = false;
    }

    return 1 + std::max(leftResult, rightResult);
}


// // You may add any prototypes of helper functions here
// int equalHelper(Node * root);

// bool equalPaths(Node * root)
// {
//     // Add your code below
//     if (!root) return true;
//     int maxLeft = equalHelper(root->left);
//     int maxRight = equalHelper(root->right);

//     if (maxRight != 0 && maxLeft != 0 && maxLeft != maxRight) return false; 
    
//     return equalPaths(root->left) && equalPaths(root->right);
// }

// int equalHelper(Node * root)
// {
//     if (!root) return 0; 
//     int leftHeight = equalHelper(root->left);
//     int rightHeight = equalHelper(root->right);

//     // find the max height
//     int maxHeight;
//     if (leftHeight >= rightHeight) maxHeight = leftHeight;
//     else maxHeight = rightHeight;

//     return 1 + maxHeight;
// }

