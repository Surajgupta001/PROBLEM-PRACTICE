/*
Set Matrix Zeroes - [Leetcode - 73(Medium)]
--------------------------------------------
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

Example 1:

Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Example 2:

Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 
Constraints:

m == matrix.length
n == matrix[0].length
1 <= m, n <= 200
-2^31 <= matrix[i][j] <= 2^31 - 1
 

Follow up:

A straightforward solution using O(m*n) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Taking Extra Space O(m+n)
// Time Complexity : O(m*n) 
void setZeroes(vector<vector<int>>& matrix) {

    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> row(m, 1); // 1 means not zero
    vector<int> col(n, 1); // 1 means not zero

    // Step 1 : Find the rows and columns that need to be set to zero
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(matrix[i][j] == 0){
                row[i] = 0; // Mark the row
                col[j] = 0; // Mark the column
            }
        }
    }

    // Step 2 : Set the rows to zero
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(row[i] == 0 || col[j] == 0){
                matrix[i][j] = 0; // Set the cell to zero
            }
        }
    } 
}

// Without Taking Extra Space : O(1)
// Time Complexity : O(m*n)
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    bool checkFirstRowZero = false;
    bool checkFirstColZero = false;
    
    // Step 1 : Check if first row and first column need to be set to zero

    // Check if first row has any zero
    for(int j=0; j<n; j++){
        if(matrix[0][j] == 0){
            checkFirstRowZero = true;
            break;
        }
    }

    // Check if first column has any zero
    for(int i=0; i<m; i++){
        if(matrix[i][0] == 0){
            checkFirstColZero = true;
            break;
        }
    }

    // Step 2 : Use first row and first column to mark zeroes
    for(int i=1; i<m; i++){
        for(int j=1; j<n; j++){
            if(matrix[i][j] == 0){
                matrix[i][0] = 0; // Mark the first column
                matrix[0][j] = 0; // Mark the first row
            }
        }
    }


    // Step 3 : Set the cells to zero based on marks in first row and first column
    for(int i=1; i<m; i++){
        for(int j=1; j<n; j++){
            if(matrix[i][0] == 0 || matrix[0][j] == 0){
                matrix[i][j] = 0; // Set the cell to zero
            }
        }
    }

    // Step 4 : Set the first row to zero if needed
    if(checkFirstRowZero){
        for(int j=0; j<n; j++){
            matrix[0][j] = 0; // Set the first row to zero
        }
    }

    // Step 5 : Set the first column to zero if needed
    if(checkFirstColZero){
        for(int i=0; i<m; i++){
            matrix[i][0] = 0; // Set the first column to zero
        }
    }

}

int main () {
    vector<vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
    setZeroes(matrix);
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[0].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}