/*
Recover Binary Search Tree - [Leetcode - 99(Medium)]
----------------------------------------------------
You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Example 1:

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:

Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
 

Constraints:

The number of nodes in the tree is in the range [2, 1000].
-2^31 <= Node.value <= 2^31 - 1
*/ 

#include <iostream>
#include <vector>
using namespace std;

class node{
public:
    int value;
    node *left;
    node *right;

    // Constructor
    node(int data){
        value = data;
        left = NULL;
        right = NULL;
    }
};

void helper(node *root, node*& prevValue, node*& firstValue, node*& secondValue){
    if(root == NULL) return;

    // Traverse the left subtree
    helper(root->left, prevValue, firstValue, secondValue);

    // Check if the current node is out of order
    if(prevValue != NULL && root->value < prevValue->value){
        // If this is the first violation, mark the first and second values
        if(firstValue == NULL){
            firstValue = prevValue;
            secondValue = root;
        }
        else {
            // If this is the second violation, mark the second value
            secondValue = root;
        }
    }

    // Update the previous value to the current node
    prevValue = root;

    // Traverse the right subtree
    helper(root->right, prevValue, firstValue, secondValue);
}

void recoverTree(node* root) {
    node* prevValue = NULL;
    node* firstValue = NULL;
    node* secondValue = NULL;

    // Perform in-order traversal to find the two swapped nodes
    helper(root, prevValue, firstValue, secondValue);

    // Swap the values of the two nodes to recover the BST
    if(firstValue != NULL && secondValue != NULL){
        int temp = firstValue->value;
        firstValue->value = secondValue->value;
        secondValue->value = temp;
    }
}

int main(){
    
    node* root = new node(3);
    root->left = new node(1);
    root->right = new node(4);
    root->right->left = new node(2);

    cout << "Before recovery: " << root->value << endl; // Output: 3
    recoverTree(root);
    cout << "After recovery: " << root->value << endl; // Output: 2

    return 0;
}