/*
98. Validate Binary Search Tree - [Leetcode - 96(Medium)]
---------------------------------------------------------
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

(i).   The left subtree of a node contains only nodes with keys less than the node's key.
(ii).  The right subtree of a node contains only nodes with keys greater than the node's key.
(iii). Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
*/

#include <iostream>
#include <vector>
#include <climits>
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

int helper(node* root, long long minValue, long long maxValue) {
    // Step 1. Base Case : If the root is null, then return 1, indicating that the subTree is Valid.
    if (root == NULL) return 1;

    // Step 2. Value Check: If the root node's value is less than or equal to min or greater than or equal to max, the function returns 0, indicating that the subtree is not valid.
    if (root->value <= minValue || root->value >= maxValue) return 0;
    
    /* Step 3.
    Recursive Calls: The function makes recursive calls to itself for the left and right subtrees. The min and max values are updated accordingly:
    => For the left subtree, min remains the same, and max is updated to the root node's value.
    => For the right subtree, min is updated to the root node's value, and max remains the same.
    */

    // Step 4. Retrun value
    return helper(root->left, minValue, root->value) && helper(root->right, root->value, maxValue);
}

bool isValidBST(node* root) {
    return helper(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    // Create a sample binary tree
    node *root = new node(5);
    root->left = new node(1);
    root->right = new node(4);
    root->right->left = new node(3);
    root->right->right = new node(6);


    // Check if the binary tree is a valid BST
    if (isValidBST(root)) {
        cout << "The binary tree is a valid BST." << endl;
    }
    else {
        cout << "The binary tree is not a valid BST." << endl;
    }

    return 0;
}