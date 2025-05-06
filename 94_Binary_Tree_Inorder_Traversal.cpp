/*
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:

Input: root = [1,null,2,3]

Output: [1,3,2]

Explanation:
    
    1
        \
        2
        /
    3
Example 2:

Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]

Output: [4,2,6,5,7,1,3,9,8]

Explanation:
    
        1
        / \
        2   3
       / \   \
      4   5   8
         / \ / \
        6  7 9


Example 3:

Input: root = []

Output: []

Example 4:

Input: root = [1]

Output: [1]

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

*/ 

#include <iostream>
#include <vector>
using namespace std;

class node {
    public:
    int value;
    node *left;
    node *right;

    // Constructor
    node(int data){
        value = data;
        left = nullptr;
        right = nullptr;
    }
};

vector<int> inorderTraversal(node* root) {
    vector<int> result;
    if(root == nullptr) return result; // Base case: if the tree is empty, return an empty vector

    
    vector<int> left = inorderTraversal(root -> left);
    result.insert(result.end(), left.begin(), left.end());

    result.push_back(root -> value);

    vector<int> right = inorderTraversal(root->right);
    result.insert(result.end(), right.begin(), right.end());

    return result;
}

int main() {
    // Create a sample binary tree
    node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->right = new node(8);
    root->left->right->left = new node(6);
    root->left->right->right = new node(7);
    root->right->right->left = new node(9);

    vector<int> result = inorderTraversal(root);

    cout << "Inorder Traversal: ";
    for(int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}