/*
Matrix Similarity After Cyclic Shifts - [Leetcode - 2946(Easy)]
-----------------------------------------------------------------
You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.

The following proccess happens k times:

Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.


Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.


Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.

Example 1:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4

Output: false

Explanation:

In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).

Example 2:

Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2

Output: true

Explanation:

Example 3:

Input: mat = [[2,2],[2,2]], k = 3

Output: true

Explanation:

As all the values are equal in the matrix, even after performing cyclic shifts the matrix will remain the same.

Constraints:

1 <= mat.length <= 25
1 <= mat[i].length <= 25
1 <= mat[i][j] <= 25
1 <= k <= 50
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
NOTE:
    int m = mat.size(); // number of rows
    int n = mat[0].size(); // number of columns

    1. Left Rotation k times : rotate(mat[i].begin(), mat[i].begin() + (k % n), mat[i].end());
    2. Right Rotation k times : rotate(mat[i].rbegin(), mat[i].rbegin() + (k % n), mat[i].rend());
*/ 

// Approach 1: Using STL rotate function
// Time Complexity: O(m*n) where m is the number of rows and n is the number of columns
// Space Complexity: O(1)
bool areSimilar(vector<vector<int>>& mat, int k) {
    int m = mat.size();
    int n = mat[0].size();
    
    // 1. Save the original matrix to compare later
    vector<vector<int>> original = mat;

    for(int i = 0; i < m; i++) {
        if(i % 2 == 0) {
            // 2. Left shift by k
            rotate(mat[i].begin(), mat[i].begin() + (k % n), mat[i].end());
        } else {
            // 3. Right shift by k (using rbegin)
            rotate(mat[i].rbegin(), mat[i].rbegin() + (k % n), mat[i].rend());
        }
    }
    
    // 4. Check if the modified matrix equals the original
    return mat == original; 
}

// Approach 2: Manual cyclic shift without using STL
// Time Complexity: O(m*n) where m is the number of rows and n is the number of columns
// Space Complexity: O(1)
bool areSimilar(vector<vector<int>>& mat, int k) {
    int m = mat.size();
    int n = mat[0].size();

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            int new_j;
            if(i % 2 == 0){
                // Left shift
                new_j = (j + k) % n;
            } else {
                // Right shift
                new_j = (j - k + n) % n; // Adding n to handle negative index
            }
            if(mat[i][j] != mat[i][new_j]){
                return false; // If any element doesn't match, return false
            }
        }
    }
    return true; // All elements match, return true
}

int main() {
    vector<vector<int>> mat1 = {{1,2,3},{4,5,6},{7,8,9}};
    int k1 = 4;
    cout << areSimilar(mat1, k1) << endl; // Output: false

    vector<vector<int>> mat2 = {{1,2,1,2},{5,5,5,5},{6,3,6,3}};
    int k2 = 2;
    cout << areSimilar(mat2, k2) << endl; // Output: true

    vector<vector<int>> mat3 = {{2,2},{2,2}};
    int k3 = 3;
    cout << areSimilar(mat3, k3) << endl; // Output: true

    return 0;
}