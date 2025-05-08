/*
Unique Binary Search Trees II - [Leetcode - 95(Medium)]
--------------------------------------------------------
Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.

Example 1:


Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
Example 2:

Input: n = 1
Output: [[1]]
 

Constraints:

1 <= n <= 8
*/

#include <iostream>
#include <vector>
using namespace std;

class node {
public:
    int value;
    node* left;
    node* right;

    // Constructor to initialize the node with a value
    node(int data){
        value = data;
        left = nullptr; // Initialize left child to nullptr
        right = nullptr; // Initialize right child to nullptr
    }
};

vector<node*> helper(int start, int end) {
    vector<node*> trees; // Vector to store the generated trees

    // Base case: if start > end, return a vector with nullptr
    if (start > end) {
        trees.push_back(nullptr);
        return trees;
    }

    // Loop through all values from start to end
    for (int i = start; i <= end; i++) {
        // Generate all left and right subtrees recursively
        vector<node*> leftSubtrees = helper(start, i - 1);
        vector<node*> rightSubtrees = helper(i + 1, end);

        // Combine each left and right subtree with the current root node
        for (node* left : leftSubtrees) {
            for (node* right : rightSubtrees) {
                node* root = new node(i); // Create a new root node with value i
                root->left = left; // Set the left child
                root->right = right; // Set the right child
                trees.push_back(root); // Add the tree to the vector
            }
        }
    }
    return trees; // Return the vector of generated trees
}

vector<node*> generateTrees(int n) {
    if (n == 0) return {}; // If n is 0, return an empty vector

    return helper(1, n); // Call the helper function with start = 1 and end = n
}

int main(){
    // print all the trees in a vector of node pointers

    vector<node *> trees = generateTrees(3); // Generate trees with n = 3

    // Print the number of unique BSTs generated
    cout << "Number of unique BSTs: " << trees.size() << endl;

    // Print the values of the root nodes of each tree
    for (int i = 0; i < trees.size(); i++){
        cout << "Tree " << i + 1 << "(root): " << trees[i]->value << endl;
    }

    return 0; // Return 0 to indicate successful execution
}