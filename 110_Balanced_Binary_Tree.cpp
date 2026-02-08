/*
Balanced Binary Tree - [Leetcode - 110(Easy)]
-----------------------------------------------
Given a binary tree, determine if it is height-balanced.

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: true

Example 2:

Input: root = [1,2,2,3,3,null,null,4,4]
Output: false

Example 3:

Input: root = []
Output: true

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-10^4 <= Node.val <= 10^4
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TreeNode {
    public:
    int value;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(int data) {
        value = data;
        left = nullptr;
        right = nullptr;
    }
};

int height(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

bool isBalanced(TreeNode* root) {
    if (root == nullptr) {
        return true; // An empty tree is balanced
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Check if the current node is balanced and recursively check left and right subtrees
    return abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

int main () {
    // Example usage:
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    cout << boolalpha << isBalanced(root) << endl; // Output: true

    return 0;
}