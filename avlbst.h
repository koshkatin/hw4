#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

// enumerate direction
enum Direction { LEFT = -1, RIGHT = 1 };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* avlInsertHelper(AVLNode<Key, Value>* node, const std::pair<const Key, Value>& new_item);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void leftRotate(AVLNode<Key, Value>* node);
    void rightRotate(AVLNode<Key, Value>* node);

    AVLNode<Key, Value>* removeHelper(AVLNode<Key, Value>* root, const Key& key);
    void removeFix(AVLNode<Key, Value>* n, const Direction diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item)
{
    // TODO
    // Use a helper function to insert the node
    AVLNode<Key, Value>* insertedNode = avlInsertHelper(static_cast<AVLNode<Key, Value>*>(this->root_), new_item);
    if (!insertedNode) return; // already existed

    AVLNode<Key, Value>* parent = insertedNode->getParent();
    if (!parent) return; // inserted as root, done

    int8_t b = parent->getBalance();
    Direction direction = (insertedNode == parent->getLeft()) ? LEFT : RIGHT;

    if (b == -1 || b == 1) {
        parent->setBalance(0); 
    } else if (b == 0) {
        parent->setBalance(direction); 
        insertFix(parent, insertedNode); // recurse
    }  
    
}

/**
 * AVL insert Helper
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::avlInsertHelper(AVLNode<Key, Value>* node, const std::pair<const Key, Value>& new_item)
{
    if (node == NULL) {
        // Create a new AVLNode
        AVLNode<Key, Value>* newRoot = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        if (this->root_ == NULL) this->root_ = newRoot;
        return newRoot; 
    }

    if (new_item.first < node->getKey()) {
        if (node->getLeft() == NULL) {
            node->setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, node));
            return node->getLeft();
        } else {
            return avlInsertHelper(node->getLeft(), new_item);
        }
    } else if (new_item.first > node->getKey()) {
        if (node->getRight() == NULL) {
            node->setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, node));
            return node->getRight();
        } else {
            return avlInsertHelper(node->getRight(), new_item);
        }
    } else {
        // Key already exists, update the value
        node->setValue(new_item.second);
        return NULL;
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
    if (p == NULL || p->getParent() == NULL) return;

    AVLNode<Key, Value>* g = p->getParent();

    // determine if p is g's left or right child, set direction to -1/+1 accordingly
    Direction direction = (p == g->getLeft()) ? LEFT : RIGHT; 
    g->updateBalance(direction);

    // g Balance Case 1 : tree is balanced
    if (g->getBalance() == 0) return; 
    
    // g Balance Case 2 : recurse
    else if (g->getBalance() == direction) insertFix(g, p);

    // g Balance Case 3 : tree is imbalanced, do rotations
    else if (g->getBalance() == direction * 2) {  

        // Variables to determine if n is in zig or zag posiotion with respect to g
        AVLNode<Key, Value>* zig = (direction == LEFT) ? p->getLeft() : p->getRight();
        AVLNode<Key, Value>* zag = (direction == LEFT) ? p->getRight() : p->getLeft();

        // zig-zig : left-left OR right-right
        if (n == zig) {  
            if (direction == LEFT) {
                rightRotate(g);
            } else if (direction == RIGHT) {  
                leftRotate(g);
            }
            p->setBalance(0);
            g->setBalance(0);
        } 
        // zig-zag : left-right OR right-left
        else if (n == zag) {
            if (direction == LEFT) {   
                leftRotate(p);
                rightRotate(g);
            } else if (direction == RIGHT) {
                rightRotate(p);
                leftRotate(g);
            }
            // n Balance case 1:
            if (n->getBalance() == direction) {
                g->setBalance(-direction);
                p->setBalance(0);
                n->setBalance(0);
            }
            // n Balance case 2 : 
            else if (n->getBalance() == 0) {
                g->setBalance(0);
                p->setBalance(0);
                n->setBalance(0);
            }
            // n Balance case 3 :
            else if (n->getBalance() == -direction) {
                g->setBalance(0);
                p->setBalance(direction);
                n->setBalance(0);
            }
        }
    }       
}

/**
 * @precondition : node has a right child and grandchild
 * rotate tree left from node
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* nr = node->getRight();
    if (!nr) return;

    AVLNode<Key, Value>* nrl = node->getRight()->getLeft();
    AVLNode<Key, Value>* np = node->getParent();

    // Step 1 : Update nr's parent
    nr->setParent(np);
    if (!np) {
        this->root_ = nr;  // if node was root, update root to node's child
    } else if (node == np->getLeft()) { // node was left child of its parent
        np->setLeft(nr);
    } else {    // node was right child of its parent
        np->setRight(nr);    
    }

    // Step 2 : Update nr's left to node
    nr->setLeft(node);
    node->setParent(nr);

    // Step 3 : Update node's right to nrl
    node->setRight(nrl);   // since nr > node, nrl > node; nrl to nodes right
    if (nrl) {
        nrl->setParent(node); 
    }
}

/**
 * @precondition : node has a left child and grandchild
 * rotate tree right from node
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* nl = node->getLeft(); // Left child of the node
    if (!nl) return; // Ensure the node has a left child

    AVLNode<Key, Value>* nlr = nl->getRight(); // Right child of the left child
    AVLNode<Key, Value>* np = node->getParent(); // Parent of the node

    // Step 1 : Update the parent of nl
    nl->setParent(np);
    if (!np) {
        // If node is the root, update the root pointer
        this->root_ = nl;
    } else if (node == np->getLeft()) {
        // If node is the left child of its parent
        np->setLeft(nl);
    } else {
        // If node is the right child of its parent
        np->setRight(nl);
    }

    // Step 2 : Update nl's right child to node
    nl->setRight(node);
    node->setParent(nl);

    // Step 3 : Update node's left child to nlr
    node->setLeft(nlr);
    if (nlr) {
        nlr->setParent(node);
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* removeNode = removeHelper(static_cast<AVLNode<Key, Value>*>(this->root_), key);
    
    if (!removeNode) return;    // did not find node, do nothing
    
    if (removeNode->getLeft() && removeNode->getRight()) {
        // swap remove node with its predecessor if it exists
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(
            BinarySearchTree<Key, Value>::predecessor(removeNode));
        nodeSwap(removeNode, pred);
    }

    AVLNode<Key, Value>* p = removeNode->getParent();
    AVLNode<Key, Value>* c = (removeNode->getLeft()) ? removeNode->getLeft() : removeNode->getRight();
    Direction diff = LEFT; // default

    if (c) c->setParent(p);

    if (p) {
        diff = (removeNode == p->getLeft()) ? RIGHT : LEFT;
        removeNode == p->getLeft() ? p->setLeft(c) : p->setRight(c);
    }
    else {
        this->root_ = c;
    }

    removeNode->setLeft(NULL);
    removeNode->setRight(NULL);
    removeNode->setParent(NULL);
    delete removeNode;

    removeFix(p, diff);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::removeHelper(AVLNode<Key, Value>* root, const Key& key)
{
    if (!root) return NULL; // tree is empty
    
    if (key == root->getKey()) return root;  // root has key
    
    else if (key < root->getKey()) {
        return removeHelper(root->getLeft(), key);
    }
    else {
        return removeHelper(root->getRight(), key);
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, const Direction diff)
{
    if (!n) return; 
    AVLNode<Key, Value>* p = n->getParent();
    Direction ndiff = LEFT; // default value
    if (p) ndiff = (n == p->getLeft()) ? RIGHT : LEFT;   

    // Case 1 
    if ((n->getBalance() + diff) == diff * 2) {
        AVLNode<Key, Value>* c = (diff == LEFT) ? n->getLeft() : n->getRight();
        
        // case 1a : zig-zig
        if (c->getBalance() == diff) {
            (diff == LEFT) ? rightRotate(n) : leftRotate(n);           
            n->setBalance(0);
            c->setBalance(0);
            removeFix(p, ndiff);
        }
        // case 1b : zig-zig
        else if (c->getBalance() == 0) {
            (diff == LEFT) ? rightRotate(n) : leftRotate(n);  
            n->setBalance(diff);
            c->setBalance(-diff);  
            // Done!     
        }
        // case 1c : zig-zag
        else if (c->getBalance() == -diff) {
            AVLNode<Key, Value>* g = (diff == LEFT) ? c->getRight() : c->getLeft();
            if (diff == LEFT) {
                leftRotate(c);
                rightRotate(n);
            }
            else {  // RIGHT
                rightRotate(c);
                leftRotate(n);
            }

            // Update balances
            if (g->getBalance() == -diff) {
                n->setBalance(0);
                c->setBalance(diff);
                g->setBalance(0);
            } 
            else if (g->getBalance() == 0) {
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else if (g->getBalance() == diff) {
                n->setBalance(-diff);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p, ndiff);
        }
    }
    // Case 2
    else if ((n->getBalance() + diff) == diff) {
        n->setBalance(diff);
        // Done!
    }
    else if ((n->getBalance() + diff) == 0) {
        n->setBalance(0);
        removeFix(p, ndiff); 
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
