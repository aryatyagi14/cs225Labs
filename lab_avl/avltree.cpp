/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    // ->1-> 2->3 
    //store the values that are chnaging

    Node* temp = t -> right;
    t -> right = temp -> left;
    temp -> left = t;
    //update heights
    t -> height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    t = temp;
    t -> height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    
    
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t -> left;
    if (temp != NULL) {
        t -> left = temp -> right;
        temp -> right = t;
    }
    //update heights
    t -> height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    if (temp != NULL) 
    {
        t = temp;
        t -> height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // assume children are balanced so b =-2 or 2
    // check for NULL node
    if (subtree == NULL) return;
    //calculate the b value of the root we are given (left -right)
    int heightLeft = heightOrNeg1(subtree -> left);
    int heightRight = heightOrNeg1(subtree -> right);
    int b = heightRight - heightLeft;
    if (b == -2) {
        //means left is too long and should eb rotatedddddddddd
        //to figure out which way calculate the b value again
        int hLeft = heightOrNeg1(subtree -> left ->left);
        int hRight = heightOrNeg1(subtree -> left -> right);
        int bLeft = hRight - hLeft;
        if (bLeft == -1) {
            //left is longer so its a stick regular rotate
            rotateRight(subtree);
        } else {
            //left is longer, this is an elbow 
            rotateLeftRight(subtree);
        }
    }
    if (b == 2) {
        //meannnnnns the right is longer
        //calculaye the bvalue of the left
        int hLeft = heightOrNeg1(subtree -> right ->left);
        int hRight = heightOrNeg1(subtree -> right -> right);
        int bRight = hRight - hLeft;
        if (bRight == 1) {
            //means its a stick to the right so plain rotate
            rotateLeft(subtree);
        } else {
            //elbow so LR
            rotateRightLeft(subtree);
        }
    }
    //update height
    int max = 1 + std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
    subtree -> height = max;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node(key,value);
    }
    if (key < subtree -> key ) {
        insert(subtree-> left, key, value);
    }
    if (key > subtree -> key) {
        insert(subtree-> right, key, value);
    }
    //here we want to rebalance every node we pass going up(exiting the recursion)
    rebalance(subtree);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    //key is assumed to exist in the tree
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            //just delete the pointer 
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //in order predecessor 
            Node* temp = subtree -> left;
            while (temp -> right != NULL) {
                temp = temp -> right;
            }
            //at this point we are at the greatest node int the subtree
            swap(subtree, temp);
            remove(subtree->left, key);

        } else {
            /* one-child remove */
            // your code here
            //make a ttemmmmp and point that to its child
            Node* temp = subtree;
            if (subtree -> right != NULL) {
                subtree = subtree -> right;
            }
            else {
                subtree = subtree -> left;
            }
            delete temp;
            temp = NULL;
        }
        // your code here
    }
    if (subtree != NULL) {
        rebalance(subtree);
    }
}
