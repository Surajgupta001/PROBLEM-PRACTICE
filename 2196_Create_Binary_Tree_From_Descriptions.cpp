/*
Create Binary Tree From Descriptions - [Leetcode - 2196(Medium)]
------------------------------------------------------------------------

You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,

If isLefti == 1, then childi is the left child of parenti.
If isLefti == 0, then childi is the right child of parenti.
Construct the binary tree described by descriptions and return its root.

The test cases will be generated such that the binary tree is valid.

Example 1:

Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
Output: [50,20,80,15,17,19]
Explanation: The root node is the node with value 50 since it has no parent.
The resulting binary tree is shown in the diagram.

Example 2:

Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
Output: [1,2,null,null,3,4]
Explanation: The root node is the node with value 1 since it has no parent.
The resulting binary tree is shown in the diagram.

Constraints:

1 <= descriptions.length <= 10^4
descriptions[i].length == 3
1 <= parenti, childi <= 10^5
0 <= isLefti <= 1
The binary tree described by descriptions is valid.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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

TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
    unordered_map<int, TreeNode*> nodeMap; // Map to store created nodes
    unordered_set<int> childrenSet; // Set to track child nodes; they never be the root of the tree
    
    for(vector<int>& desc : descriptions){
        int parent = desc[0];
        int child = desc[1];
        int isLeft = desc[2];

        // check if the parent node is already created, if not create it
        if(nodeMap.count(parent) == 0){
            nodeMap[parent] = new TreeNode(parent);
        }

        // Similarly, check if the child node is already created, if not create it
        if(nodeMap.count(child) == 0){
            nodeMap[child] = new TreeNode(child);
        }

        // Check if the child node is left or right and connect it to the parent node accordingly
        if(isLeft == 1){
            nodeMap[parent]->left = nodeMap[child];
        } else {
            nodeMap[parent]->right = nodeMap[child];
        }

        // Add the child node to the set of children
        childrenSet.insert(child);
    }

    // Find the root node, which is the one that is not present in the children set
    for(auto& desc : descriptions){
        int parent = desc[0];
        if(childrenSet.count(parent) == 0){
            return nodeMap[parent]; // Return the root node
        }
    }

    return nullptr; // Return nullptr if no root is found (should not happen in a valid tree)
}

int main() {
    vector<vector<int>> descriptions = {{20,15,1},{20,17,0},{50,20,1},{50,80,0},{80,19,1}};
    TreeNode* root = createBinaryTree(descriptions);
    // The tree is created successfully. You can add code to print the tree or verify its structure.
    return 0;
}