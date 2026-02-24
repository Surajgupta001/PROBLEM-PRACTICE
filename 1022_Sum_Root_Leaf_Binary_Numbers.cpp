/*
Sum of Root To Leaf Binary Numbers - [Leetcode - 1022(Easy)]
---------------------------------------------------------------
You are given the root of a binary tree where each node has a value 0 or 1. Each root-to-leaf path represents a binary number starting with the most significant bit.

For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum of these numbers.

The test cases are generated so that the answer fits in a 32-bits integer.

Example 1:

Input: root = [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

Example 2:

Input: root = [0]
Output: 0

Constraints:

The number of nodes in the tree is in the range [1, 1000].
Node.val is 0 or 1.
*/

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
    public:
    int value;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(int data){
        value = data;
        left = nullptr;
        right = nullptr;
    }
};

int helper(TreeNode *root, int value) {
    if(!root) return 0;

    value = (2 * value) + root->value;

    if(root -> left == nullptr && root -> right == nullptr){
        return value;
    }
    
    return helper(root->left, value) + helper(root->right, value);
}

int sumRootToLeaf(TreeNode* root) {
    return helper(root, 0);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(1);

    cout << sumRootToLeaf(root) << endl; // Output: 22

    return 0;
}