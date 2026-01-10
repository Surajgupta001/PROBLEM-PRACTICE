/*
Smallest Subtree with all the Deepest Nodes - [Leetcode - 865(Medium)]
------------------------------------------------------------------------
Given the root of a binary tree, the depth of each node is the shortest distance to the root.

Return the smallest subtree such that it contains all the deepest nodes in the original tree.

A node is called the deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest nodes of the tree.
Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.

Example 2:

Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree.

Example 3:

Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest node in the tree is 2, the valid subtrees are the subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the smallest.

Constraints:

The number of nodes in the tree will be in the range [1, 500].
0 <= Node.val <= 500
The values of the nodes in the tree are unique.


NOTE: This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    // Constructor
    TreeNode(int data) {
        this->val = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

TreeNode *LCA(TreeNode *root, unordered_map<int, int> &map, int maxDepth) {
    if (root == nullptr || map[root->val] == maxDepth) return root;

    TreeNode *left = LCA(root->left, map, maxDepth);
    TreeNode *right = LCA(root->right, map, maxDepth);

    if (left && right) return root;

    return left ? left : right;
}

void findDepth(TreeNode *root, int depth, unordered_map<int, int> &map, int &maxDepth) {
    if (!root) return;

    maxDepth = max(maxDepth, depth);
    map[root->val] = depth;
    findDepth(root->left, depth + 1, map, maxDepth);
    findDepth(root->right, depth + 1, map, maxDepth);
}

TreeNode *subtreeWithAllDeepest(TreeNode *root) {
    unordered_map<int, int> map; // node value -> depth because node values are unique
    int maxDepth = 0;
    findDepth(root, 0, map, maxDepth);
    return LCA(root, map, maxDepth);
}

// ========== Efficient Approach ============
pair<int, TreeNode *> solve(TreeNode *root) {
    if (root == NULL) return {0, NULL};

    auto left = solve(root->left);
    auto right = solve(root->right);

    if (left.first == right.first){
        return {left.first + 1, root};
    }
    else if (left.first > right.first){
        return {left.first + 1, left.second};
    }
    else{
        return {right.first + 1, right.second};
    }
}

TreeNode *lcaDeepestLeaves(TreeNode *root) {
    return solve(root).second;
}

int main() {
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode *ans = subtreeWithAllDeepest(root);
    cout << "The value of the smallest subtree with all the deepest nodes is: " << ans->val << endl;

    return 0;
}