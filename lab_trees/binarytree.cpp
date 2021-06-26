/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
    //your code here
}

template <typename T>
void BinaryTree<T>::mirror(Node *& node) {
    if (node == NULL) {
        return;
    }
    Node * tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    mirror(node->right);
    mirror(node->left);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    bool isordered = true;
    if (!root) {
        return isordered;
    }
    InorderTraversal<T> traversal(root);
    int prev_val = (*traversal.begin())->elem;
    for (TreeTraversal<int>::Iterator it = traversal.begin(); it != traversal.end(); ++it) {
        if (prev_val < (*it)->elem) {
            prev_val = (*it)->elem;
            isordered = true;
        } else if (prev_val > (*it)->elem) {
            isordered = false;
            break;
        }
    }
    return isordered;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root, NULL, NULL);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node * node, Node * left, Node * right) const {
    if (node == NULL) {
        return true;
    }
    if (left != NULL && (node->elem > left->elem)) {
        return false;
    }
    if (right != NULL && (node->elem < right->elem)) {
        return false;
    }
    return (isOrderedRecursive(node->left, node, right) && isOrderedRecursive(node->right, left, node));
}