/*
Determine Whether Matrix Can Be Obtained By Rotation - [Leetcode - 1886(Easy)]
-----------------------------------------------------------------------------------
Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.

Example 1:

Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
Output: true
Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.

Example 2:

Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
Output: false
Explanation: It is impossible to make mat equal to target by rotating mat.
Example 3:

Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
Output: true
Explanation: We can rotate mat 90 degrees clockwise two times to make mat equal target.

Constraints:

n == mat.length == target.length
n == mat[i].length == target[i].length
1 <= n <= 10
mat[i][j] and target[i][j] are either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
NOTE    : 90 degree rotation Clockwise
            - Transpose
            - Reverse each row
        : 90 degree rotation Anti-Clockwise
            - Transpose
            - Reverse each column
*/ 

bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
    int n = mat.size();

    for (int i = 0; i < 4; i++){
        // Transpose
        for(int j = 0; j < n; j++){
            for(int k = j; k < n; k++){
                swap(mat[j][k], mat[k][j]);
            }
        }

        // Reverse each row
        for(int j = 0; j < n; j++){
            reverse(mat[j].begin(), mat[j].end());
        }

        if(mat == target){
            return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> mat = {{0,1},{1,0}};
    vector<vector<int>> target = {{1,0},{0,1}};

    cout << findRotation(mat, target) << endl;

    return 0;
}