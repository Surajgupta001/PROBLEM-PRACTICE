/*
Minimum Falling Path Sum - [Leetcode - 931(Medium)]
-----------------------------------------------------
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

Example 1:


Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.

Example 2:

Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.
 
Constraints:

n == matrix.length == matrix[i].length
1 <= n <= 100
-100 <= matrix[i][j] <= 100
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// // Approach - 1: Memoization
// int helper(vector<vector<int>>& matrix, int row, int col, vector<vector<int>>& dp){
//     int m = matrix.size();

//     if (row == m - 1) return dp[row][col] = matrix[row][col];
//     if (dp[row][col] != INT_MAX) return dp[row][col];

//     int minSum = INT_MAX;

//     /*
//     if (row + 1 < m && col - 1 >= 0) {
//         minSum = min(minSum, helper(matrix, row + 1, col - 1, dp)); // down-left
//     }

//     if (row + 1 < m) {
//         minSum = min(minSum, helper(matrix, row + 1, col, dp)); // down
//     }
    
//     if (row + 1 < m && col + 1 < m) {
//         minSum = min(minSum, helper(matrix, row + 1, col + 1, dp)); // down-right
//     }
//     */ 

//     // Slight optimization to avoid recomputation
//     for(int shift = -1; shift <= 1; shift++){
//         if(row+1<m && col+shift<m && col+shift>=0){
//             minSum = min(minSum, helper(matrix, row + 1, col + shift, dp));
//         }
//     }

//     return dp[row][col] = minSum + matrix[row][col];
// }

// int minFallingPathSum(vector<vector<int>>& matrix) {
//     int m = matrix.size();
//     vector<vector<int>> dp(m, vector<int>(m, INT_MAX));

//     int row = 0;
//     int result = INT_MAX;
//     for (int col = 0; col < m; col++) {
//         result = min(result, helper(matrix, row, col, dp));
//     }
//     return result;
// }

// Approach - 2 : Bottom-Up DP => Efficient more than memoization
int minFallingPathSum(vector<vector<int>>& matrix){
    int m = matrix.size();
    vector<vector<int>> dp(m, vector<int>(m));

    // Populate the first row
    for(int col = 0; col < m; col++){
        dp[0][col] = matrix[0][col];
    }

    for(int row = 1; row < m; row++){
        for(int col = 0; col < m; col++){
            int a = INT_MAX;
            int b = INT_MAX;

            if(col - 1 >= 0){
                a = dp[row-1][col-1];
            }
            if(col + 1 < m){
                b = dp[row-1][col+1];
            }
            dp[row][col] = matrix[row][col] + min({a, b, dp[row-1][col]});
        }
    }
    
    int result = INT_MAX;
    int lastRow = m - 1;

    for(int col = 0; col < m; col++){
        result = min(result, dp[lastRow][col]);
    }

    return result;
}

// Slight Improvement on Approach - 2 : Space Optimization
int minFallingPathSum(vector<vector<int>>& matrix){
    int n = matrix.size();
    if (n == 0) return 0;

    vector<int> dp = matrix[0];     // best sums to reach row 0
    vector<int> next(n);

    for (int row = 1; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            int best = dp[col];                    // up
            if (col > 0)      best = min(best, dp[col - 1]); // up-left
            if (col + 1 < n)  best = min(best, dp[col + 1]); // up-right
            next[col] = matrix[row][col] + best;
        }
        dp.swap(next);
    }
    return *min_element(dp.begin(), dp.end());
}

int main() {
    vector<vector<int>> matrix = {{2,1,3},{6,5,4},{7,8,9}};
    cout << "Minimum Falling Path Sum: " << minFallingPathSum(matrix) << endl;

    return 0;
}