/*
Balance a Binary Search Tree - [Leetcode - 1382(Medium)]
--------------------------------------------------------------
Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

Example 1:

Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.

Example 2:

Input: root = [2,1,3]
Output: [2,1,3]

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
1 <= Node.val <= 10^5
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

// Here we use inorder traversal to get the sorted list of values from the BST, and then we build a balanced BST from that sorted list.

void inorderTraversal(TreeNode* root, vector<int>& values) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, values);
    values.push_back(root->value);
    inorderTraversal(root->right, values);
}

TreeNode* buildBalancedBST(const vector<int>& values, int left, int right) {
    if (left > right) {
        return nullptr;
    }

    int mid = left + (right - left) / 2;
    TreeNode* node = new TreeNode(values[mid]);
    node->left = buildBalancedBST(values, left, mid - 1);
    node->right = buildBalancedBST(values, mid + 1, right);
    return node;
}

TreeNode* balanceBST(TreeNode* root) {
    vector<int> values;
    inorderTraversal(root, values);
    return buildBalancedBST(values, 0, values.size() - 1);
}

void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->value << " ";
    printInorder(root->right);
}

int main() {
    // Example usage:
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);

    TreeNode* balancedRoot = balanceBST(root);

    printInorder(balancedRoot);
    cout << endl;

    return 0;
}