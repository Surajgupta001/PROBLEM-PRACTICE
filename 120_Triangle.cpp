/*
Triangle - [Leetcode - 120(Medium)]
------------------------------------
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

 

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:

Input: triangle = [[-10]]
Output: -10
 

Constraints:

1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-10^4 <= triangle[i][j] <= 10^4
 

Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach - 1 : Recursion + Memoization => TLE
int helper(vector<vector<int>>& triangle, int row, int col, vector<vector<int>>& dp) {
    int n = triangle.size();
    if (row == n - 1) {
        return triangle[row][col];
    }
    if (dp[row][col] != -1) {
        return dp[row][col];
    }

    int minPathSum = triangle[row][col] + min(helper(triangle, row + 1, col, dp), helper(triangle, row + 1, col + 1, dp));

    return dp[row][col] = minPathSum;
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return helper(triangle, 0, 0, dp);
}

// Approach - 2 : Tabulation
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp = triangle; // Copying triangle to dp => space O(n^2)
    // dp[i][j] = minimum path sum from top [0][0] to [i][j] i.e. bottom-up approach

    for (int row = n - 2; row >= 0; row--) {
        for (int col = 0; col <= row; col++) {
            dp[row][col] += min(dp[row + 1][col], dp[row + 1][col + 1]);
        }
    }
    return dp[0][0]; // minimum path sum from top [0][0] to bottom
}

// Approach - 3 : Space Optimization in Tabulation
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> dp = triangle[n - 1]; // Copying last row of triangle to dp => space O(n) = (row + 1)
    // dp[i][j] = minimum path sum from top [0][0] to [i][j] i.e. bottom-up approach

    for (int row = n - 2; row >= 0; row--) {
        for (int col = 0; col <= row; col++) {
            dp[col] = triangle[row][col] + min(dp[col], dp[col + 1]);
        }
    }
    return dp[0]; // minimum path sum from top [0][0] to bottom
}

// Approach - 4 : In-Place Modification of Input Triangle
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    
    for(int row = 1; row < n; row++) {
        for(int col = 0; col <= row; col++) {
            int prev_row_up = triangle[row - 1][min(col, (int)triangle[row - 1].size() - 1)];
            int prev_row_left = triangle[row - 1][col - 1];
            triangle[row][col] += min(prev_row_left, prev_row_up);
        }
    }
    return *min_element(triangle[n - 1].begin(), triangle[n - 1].end());
}

int main() {
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    
    cout << minimumTotal(triangle) << endl; // Output: 11
    
    return 0;
}