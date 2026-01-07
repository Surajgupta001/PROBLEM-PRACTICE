/*
Maximum Product of Splitted Binary Tree - [Leetcode - 1339(Medium)]
---------------------------------------------------------------------
Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.

Note that you need to maximize the answer before taking the mod and not after taking it.

Example 1:

Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)

Example 2:

Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation: Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)

Constraints:

The number of nodes in the tree is in the range [2, 5 * 10^4].
1 <= Node.val <= 10^4
*/

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
    public:
    int val;
    TreeNode *left;
    TreeNode *right;
    
    // Contructors
    TreeNode(int data){
        val = data;
        left = nullptr;
        right = nullptr;
    }
};

const long mod = 1e9 + 7;
long totalSum = 0;
long maxP = 0;

int findTotalSum(TreeNode *root) {
    if (!root) return 0;

    int leftSubtreeSum = findTotalSum(root->left);
    int rightSubtreeSum = findTotalSum(root->right);
    int sum = root->val + leftSubtreeSum + rightSubtreeSum;

    maxP = max(maxP, (totalSum - sum) * sum);

    return sum;
}

int maxProduct(TreeNode *root) {
    if (!root) return 0;

    maxP = 0;

    totalSum = findTotalSum(root);

    findTotalSum(root);

    return maxP % mod;
}

int main () {
    // Example 1: root = [1,2,3,4,5,6], expected output: 110
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    cout << "Maximum Product of Splitted Binary Tree: " << maxProduct(root) << endl;

    return 0;
}