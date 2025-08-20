/*
Count Square Submatrices with All Ones - [Leetcode - 1277(Medium)]
-------------------------------------------------------------------
Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

 

Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:

Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.

Constraints:

1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1
*/ 

/*
============ IMPORTANT POINTS =================
A square submatrix means a contiguous block of cells forming a square (e.g., 1x1, 2x2, 3x3, etc.), and all its elements must be 1.
*/ 

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int countSquares(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int count = 0;

    // For each cell (i, j) in the matrix, calculate the size of the largest square submatrix with all ones that ends at (i, j).

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(matrix[i][j] == 1 && i > 0 && j > 0){
                // This value represents the largest square ending at (i,j)
                int top = matrix[i-1][j];
                int left = matrix[i][j-1];
                int top_left = matrix[i-1][j-1];
                
                matrix[i][j] = min({top, left, top_left}) + 1;
            }
            count += matrix[i][j];
        }
    }
    return count;
}

int main () {
    vector<vector<int>> matrix1 = {
        {0,1,1,1},
        {1,1,1,1},
        {0,1,1,1}
    };
    cout << countSquares(matrix1) << endl;

    vector<vector<int>> matrix2 = {
        {1,0,1},
        {1,1,0},
        {1,1,0}
    };
    cout << countSquares(matrix2) << endl;

    return 0;
}