/*
Binary Tree Level Order Traversal - [Leetcode - 102(Medium)]
------------------------------------------------------------
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class node {
public:
    int value;
    node* left;
    node* right;

    // Constructor to initialize the node with a value
    node(int data) {
        value = data;
        left = nullptr; // Initialize left child to nullptr
        right = nullptr; // Initialize right child to nullptr
    }
};

vector<vector<int>> levelOrder(node* root) {
    vector<vector<int>> result; // Vector to store the level order traversal
    if (!root) return result; // If the tree is empty, return an empty vector

    queue<node*> qu; // Queue to perform level order traversal
    qu.push(root); // Start with the root node

    while (!qu.empty()) {
        int size = qu.size(); // Get the number of nodes at the current level
        vector<int> level; // Vector to store the values of nodes at the current level

        for (int i = 0; i < size; i++) {
            node* current = qu.front(); // Get the front node in the queue
            qu.pop(); // Remove it from the queue
            level.push_back(current->value); // Add its value to the current level

            // Add left and right children to the queue for next level processing
            if (current->left) qu.push(current->left);
            if (current->right) qu.push(current->right);
        }
        result.push_back(level); // Add the current level to the result
    }
    return result; // Return the final result
}

// Function to print the level order traversal result
void printLevelOrder(const vector<vector<int>>& result) {
    for (const auto& level : result) {
        cout << "[";
        for (size_t i = 0; i < level.size(); i++) {
            cout << level[i];
            if (i < level.size() - 1) cout << ", ";
        }
        cout << "] ";
    }
    cout << endl;
}

int main() {
    // Create a sample binary tree
    node* root = new node(3);
    root->left = new node(9);
    root->right = new node(20);
    root->right->left = new node(15);
    root->right->right = new node(7);

    // Perform level order traversal
    vector<vector<int>> result = levelOrder(root);

    // Print the result
    printLevelOrder(result);

    return 0;
}