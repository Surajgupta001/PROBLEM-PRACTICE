/*
Special Positions in a Binary Matrix - [Leetcode - 1582(Easy)]
-----------------------------------------------------------------
Given an m x n binary matrix mat, return the number of special positions in mat.

A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).

Example 1:

Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
Output: 1
Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.

Example 2:

Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
Explanation: (0, 0), (1, 1) and (2, 2) are special positions.

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 100
mat[i][j] is either 0 or 1.
*/

#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach
int numSpecial(vector<vector<int>> &mat){
    int count = 0;
    
    int m = mat.size();
    int n = mat[0].size();

    for(int row=0; row<m; row++){
        for(int col=0; col<n; col++){
            if(mat[row][col] == 0) continue;
            bool special = true;
            // Check column
            for (int r = 0; r<m; r++){
                if(r != row && mat[r][col] == 1){
                    special = false;
                    break;
                }
            }
            // Check row
            for (int c = 0; c<n; c++){
                if(c != col && mat[row][c] == 1){
                    special = false;
                    break;
                }
            }
            if(special) count++;
        }
    }
    return count;
}

// Optimal Approach
int numSpecial(vector<vector<int>> &mat) {
    int m = mat.size();
    int n = mat[0].size();

    vector<int> rowCount(m, 0); // How many 1's in each row
    vector<int> colCount(n, 0); // How many 1's in each column

    // Count the number of 1's in each row and column
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(mat[i][j] == 1){
                rowCount[i]++;
                colCount[j]++;
            }
        }
    }

    int count = 0;
    for(int row=0; row<m; row++){
        for(int col=0; col<n; col++){
            if(mat[row][col] == 1 && rowCount[row] == 1 && colCount[col] == 1){
                count++;
            }
        }
    }
    return count;
}

int main(){
    vector<vector<int>> mat1 = {{1, 0, 0}, {0, 0, 1}, {1, 0, 0}};
    cout << numSpecial(mat1) << endl; // Output: 1

    vector<vector<int>> mat2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    cout << numSpecial(mat2) << endl; // Output: 3

    return 0;
}