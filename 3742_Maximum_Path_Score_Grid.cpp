/*
Maximum Path Score in a Grid - [Leetcode - 3742]
----------------------------------------------------------

You are given an m x n grid where each cell contains one of the values 0, 1, or 2. You are also given an integer k.

You start from the top-left corner (0, 0) and want to reach the bottom-right corner (m - 1, n - 1) by moving only right or down.

Each cell contributes a specific score and incurs an associated cost, according to their cell values:

0: adds 0 to your score and costs 0.
1: adds 1 to your score and costs 1.
2: adds 2 to your score and costs 1. ​​​​​​​
Return the maximum score achievable without exceeding a total cost of k, or -1 if no valid path exists.

Note: If you reach the last cell but the total cost exceeds k, the path is invalid.

Example 1:

Input: grid = [[0, 1],[2, 0]], k = 1

Output: 2

Explanation:​​​​​​​

The optimal path is:

Cell	grid[i][j]	Score	Total
Score	Cost	Total
Cost
(0, 0)	0	0	0	0	0
(1, 0)	2	2	2	1	1
(1, 1)	0	0	2	0	1
Thus, the maximum possible score is 2.

Example 2:

Input: grid = [[0, 1],[1, 2]], k = 1

Output: -1

Explanation:

There is no path that reaches cell (1, 1)​​​​​​​ without exceeding cost k. Thus, the answer is -1.

Constraints:

1 <= m, n <= 200
0 <= k <= 10^3​​​​​​​
​​​​​​​grid[0][0] == 0
0 <= grid[i][j] <= 2
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Approach: Recursive Dynamic Programming with Memoization
int helper(vector<vector<int>>& grid, int k, int i, int j, int cost, vector<vector<vector<int>>>& dp) {
    int m = grid.size();
    int n = grid[0].size();

    // Base Case : If we have reached the bottom-right corner
    if(i >= m or j >= n){
        return INT_MIN; // Return a very small value to indicate an invalid path
    }

    int newCost = cost + (grid[i][j] > 0);

    if(newCost > k){
        return INT_MIN; // Return a very small value to indicate an invalid path
    }

    if(i == m - 1 and j == n - 1){
        return grid[i][j]; // Return the score of the last cell
    }

    if(dp[i][j][newCost] != -1){
        return dp[i][j][newCost]; // Return the cached result
    }

    // Recursive calls for right and down movements
    int rightScore = helper(grid, k, i, j + 1, newCost, dp);
    int downScore = helper(grid, k, i + 1, j, newCost, dp);

    // Calculate the maximum score from the current cell
    int maxScore = max(rightScore, downScore);

    if (maxScore == INT_MIN){
        dp[i][j][newCost] = INT_MIN; // Cache the result for invalid paths
    } else {
        dp[i][j][newCost] = grid[i][j] + maxScore; // Cache the result for valid paths
    }

    return dp[i][j][newCost];
    
}

int maxPathScore(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    // dp[i][j][c] will store the maximum score at cell (i, j) with cost c
    vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(k + 1, -1)));

    int result = helper(grid, k, 0, 0, 0, dp);

    return result == INT_MIN ? -1 : result;
}

// Approach 2: Bottom-Up Dynamic Programming
int maxPathScore(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    // dp[i][j][c] will store the maximum score at cell (i, j) with cost c
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, INT_MIN)));

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            for(int cost=k; cost>=0; cost--){

                int newCost = cost + (grid[i][j] > 0);

                if(newCost > k){
                    continue; // Skip if the new cost exceeds k
                }

                if(i == m-1 and j == n-1){
                    dp[i][j][cost] = grid[i][j]; // Base case for the last cell
                    continue;
                }

                int downScore = INT_MIN;
                int rightScore = INT_MIN;

                if(i+1 < m){
                    downScore = dp[i+1][j][newCost]; // Score from the cell below
                }

                if(j+1 < n){
                    rightScore = dp[i][j+1][newCost]; // Score from the cell to the right
                }

                int maxScore = max(downScore, rightScore);
                
                if(maxScore != INT_MIN){
                    dp[i][j][cost] = grid[i][j] + maxScore;
                }
            }
        }
    }
    return dp[0][0][0] == INT_MIN ? -1 : dp[0][0][0];
}

int main() {
    vector<vector<int>> grid1 = {{0, 1}, {2, 0}};
    int k1 = 1;
    cout << "Maximum Path Score (Example 1): " << maxPathScore(grid1, k1) << endl; // Output: 2

    vector<vector<int>> grid2 = {{0, 1}, {1, 2}};
    int k2 = 1;
    cout << "Maximum Path Score (Example 2): " << maxPathScore(grid2, k2) << endl; // Output: -1

    return 0;
}