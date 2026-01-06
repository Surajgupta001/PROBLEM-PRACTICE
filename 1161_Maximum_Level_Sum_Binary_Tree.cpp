/*
Maximum Level Sum of a Binary Tree - [Leetcode - 1161(Medium)]
----------------------------------------------------------------
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

Example 1:

Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Example 2:

Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-10^5 <= Node.val <= 10^5
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <map>
using namespace std;

/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
* };
*/

class node {
    public:
    int val;
    node* left;
    node* right;

    // Constructor
    node(int data) {
        val = data;
        left = nullptr;
        right = nullptr;
    }
};

// BFS Approach
int maxLevelSum(node* root) {
    int maxSum = INT_MIN;
    int resultLevel = 0;
    
    queue<node*> qu;
    qu.push(root);

    int currLevel = 1;

    while(!qu.empty()){
        int n = qu.size();
        int sum = 0;

        // Traversing all elements of curr level
        while(n--){
            node* currNode = qu.front();
            qu.pop();

            sum += currNode->val;
            if(currNode->left) qu.push(currNode->left);
            if(currNode->right) qu.push(currNode->right);
        }
        
        if(sum > maxSum){
            maxSum = sum;
            resultLevel = currLevel;
        }

        currLevel++;
    }
    return resultLevel;
}

// DFS Approach(inorder traversal)
map<int,int> levelSumMap; // {level, sum}

void dfs(node* root, int level) {
    if(!root) return;

    levelSumMap[level] += root->val;

    dfs(root->left, level + 1);
    dfs(root->right, level + 1);
}

int maxLevelSum(node* root) {
    levelSumMap.clear();

    dfs(root, 1);

    int maxSum = INT_MIN;
    int resultLevel = 0;

    for(auto &itr : levelSumMap){
        int level = itr.first;
        int sum = itr.second;

        if(sum > maxSum){
            maxSum = sum;
            resultLevel = level;
        }
    }
    return resultLevel;
}

int main() {
    // Example usage:
    node* root = new node(1);
    root->left = new node(7);
    root->right = new node(0);
    root->left->left = new node(7);
    root->left->right = new node(-8);

    cout << "Level with maximum sum: " << maxLevelSum(root) << endl; // Output: 2

    return 0;
}