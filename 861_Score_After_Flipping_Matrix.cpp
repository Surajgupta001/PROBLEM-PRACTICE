/*
861. Score After Flipping Matrix - [Leetcode - 861(Medium)]
-----------------------------------------------------------

You are given an m x n binary matrix grid.

A move consists of choosing any row or column and toggling each value in that row or column (i.e., changing all 0's to 1's, and all 1's to 0's).

Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score after making any number of moves (including zero moves).

Example 1:

Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39

Example 2:

Input: grid = [[0]]
Output: 1

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 20
grid[i][j] is either 0 or 1.
*/ 

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Approch 1: Greedy Algorithm (Flipping input matrix)
// Time Complexity: O(m*n) where m is the number of rows and n is the number of columns in the grid
int matrixScore(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    //set first column value in each row
    for(int i = 0; i < m; i++) {
        if(grid[i][0] == 0) {
            //flip that row
            for(int j = 0; j < n; j++) {
                grid[i][j] = 1 - grid[i][j]; //flipping the value 0 to 1 and 1 to 0
            }

        }
    }

    for(int j = 1; j < n; j++) {
        
        int countZero = 0;
        for(int i = 0; i < m; i++) {
            if(grid[i][j] == 0) {
                countZero++;
            }
        }

        int countOne = m - countZero;
        if(countZero > countOne) {
            //flipping that column
            for(int i = 0; i < m; i++) {
                grid[i][j] = 1 - grid[i][j];
            }
        }

    }

    int score = 0;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            
            int value = grid[i][j] * pow(2, n-j-1); // grid[i][j] << (n-j-1);
            score += value;
        }
    }
    
    return score;
}


// Approch 2: Without flipping input matrix
int matrixScore(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    //MSB -> 2^n-1
    int score = pow(2, n-1) * m;

    for(int j = 1; j < n; j++) {

        int countSameBits = 0; // count of 1s
        for(int i = 0; i < m; i++) {
            if(grid[i][j] == grid[i][0]) {
                countSameBits++;
            }
        }

        int countOnes  = countSameBits;
        int countZeros = m - countOnes;

        int ones = max(countOnes, countZeros);

        score += (pow(2, n-j-1) * ones);         
    }

    return score;
}

int main(){
    vector<vector<int>> grid = {{0,0,1,1},{1,0,1,0},{1,1,0,0}};
    cout << "Maximum score after flipping: " << matrixScore(grid) << endl;  
        
    return 0;
}