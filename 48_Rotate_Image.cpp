/*
Rotate Image - [Leetcode - 48(Medium)]
------------------------------------------
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:

Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Constraints:

n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<vector<int>>& mat) {
    // 1. Take transpose of the matrix
    // 2. Reverse each row of the matrix

    int m = mat.size();
    int n = mat[0].size();

    for(int i=0; i<m; i++){
        for(int j=i; j<n; j++){
            swap(mat[i][j], mat[j][i]);
        }
    }

    for(int i=0; i<m; i++){
        reverse(mat[i].begin(), mat[i].end());
    }
}

int main() {
    vector<vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};
    rotate(mat);
    for(auto row: mat){
        for(auto col: row){
            cout << col << " ";
        }
        cout << endl;
    }
    return 0;
}