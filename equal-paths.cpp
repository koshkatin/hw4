#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int subtreeHeight(Node * root);

bool equalPaths(Node * root)
{
    // Add your code below
    if (!root) return true;
    int maxLeft = subtreeHeight(root->left);
    int maxRight = subtreeHeight(root->right);

    if (maxRight != 0 && maxLeft != 0 && maxLeft != maxRight) return false; 
    
    return equalPaths(root->left) && equalPaths(root->right);
}

int subtreeHeight(Node * root)
{
    if (!root) return 0; 
    int leftHeight = subtreeHeight(root->left);
    int rightHeight = subtreeHeight(root->right);

    // find the max height
    int maxHeight;
    if (leftHeight >= rightHeight) maxHeight = leftHeight;
    else maxHeight = rightHeight;

    return 1 + maxHeight;
}

