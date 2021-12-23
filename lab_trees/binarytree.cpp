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
    //dont you just flip the first left and right poinnnnters
    recursiveMirror(root);
}
template <typename T>
void BinaryTree<T>::recursiveMirror(Node* curr) {
    if (curr == NULL) {
        return;
    }
    Node* temp  = curr ->right;
    curr -> right = curr -> left;
    curr -> left = temp;
    recursiveMirror(curr -> right);
    recursiveMirror(curr -> left);
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
    //wont let me minus the iterator how do I do it ?
    InorderTraversal<T> node(root);
    Node* compare = *(node.begin()); //this is a node pointer
    for (typename TreeTraversal<T>::Iterator it = node.begin(); it != node.end() ; ++it) {
        if ((compare -> elem) > (*it) -> elem) {
            return false;
        }
        compare = *it;
    }
    return true;
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
    //go left
   //creat a null pointer to pass into helper
   Node* ptr = NULL;
   return recursiveHelper(root, ptr);
}
template <typename T>
bool BinaryTree<T>::recursiveHelper(Node* sub, Node*& prev) const 
{
    if (sub != NULL) {
        if (!recursiveHelper(sub -> left, prev)){
            return false;
        }
        if (prev != NULL && (sub -> elem <= prev -> elem)) {
            return false;
        }
        prev = sub;
        return recursiveHelper(sub-> right, prev);
    }
    return true;
}






