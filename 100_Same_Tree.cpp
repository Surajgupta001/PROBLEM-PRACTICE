/*
Same Tree - [Leetcode - 100(Easy)]
----------------------------------
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

 

Example 1:


Input: p = [1,2,3], q = [1,2,3]
Output: true
Example 2:


Input: p = [1,2], q = [1,null,2]
Output: false
Example 3:


Input: p = [1,2,1], q = [1,1,2]
Output: false
 

Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104
*/ 

#include <iostream>
#include <vector>
using namespace std;

class node{
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

bool isSameTree(node* p, node* q) {
        
    if (not p and not q) return true;
    if (not p or not q) return false;
    return (p->value == q->value) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int main(){
    // Example usage
    node* p = new node(1);
    p->left = new node(2);
    p->right = new node(3);

    node* q = new node(1);
    q->left = new node(2);
    q->right = new node(3);

    if (isSameTree(p, q)) {
        cout << "The trees are the same." << endl;
    }
    else {
        cout << "The trees are not the same." << endl;
    }

    return 0;
}