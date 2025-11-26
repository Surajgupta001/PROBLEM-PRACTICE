/*
Paths in Matrix Whose Sum Is Divisible by K - [Leetcode - 2435(Medium)]
-------------------------------------------------------------------------
You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.

Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 109 + 7.

Example 1:

Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
Output: 2
Explanation: There are two paths where the sum of the elements on the path is divisible by k.
The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.

Example 2:

Input: grid = [[0,0]], k = 5
Output: 1
Explanation: The path highlighted in red has a sum of 0 + 0 = 0 which is divisible by 5.

Example 3:

Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
Output: 10
Explanation: Every integer is divisible by 1 so the sum of the elements on every possible path is divisible by k.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 5 * 10^4
1 <= m * n <= 5 * 10^4
0 <= grid[i][j] <= 100
1 <= k <= 50
*/

#include <iostream>
#include <vector>
using namespace std;

int mod = 1e9 + 7;

// Recursive + Memoization Approach
int helper(int i, int j, int currSum, vector<vector<int>>& grid, int k, vector<vector<vector<int>>>& dp) {
    int m = grid.size();
    int n = grid[0].size();

    if(i >= m or j >= n) return 0;

    if(i == m - 1 and j == n - 1){
        return (currSum + grid[i][j]) % k == 0 ? 1 : 0;
    }

    if(dp[i][j][currSum] != -1) return dp[i][j][currSum];

    int down = helper(i + 1, j, (currSum + grid[i][j]) % k, grid, k, dp);
    int right = helper(i, j + 1, (currSum + grid[i][j]) % k, grid, k, dp);

    return dp[i][j][currSum] = (down + right) % mod;
}

int numberOfPaths(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, -1)));
    
    return helper(0, 0, 0, grid, k, dp);
}

// Bottom-Up Approach
int numberOfPaths(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    
    vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(k+1, 0)));

    // Base Case
    for(int remainder = 0; remainder <= k-1; remainder++){
        dp[m-1][n-1][remainder] = (remainder + grid[m-1][n-1]) % k == 0;
    }
    
    for(int i = m - 1; i >= 0; i--){
        for(int j = n - 1; j >= 0; j--){
            for(int remainder = 0; remainder <= k - 1; remainder++){
                if (i == m - 1 and j == n - 1) continue;
                int newRemainder = (remainder + grid[i][j]) % k;

                int down = dp[i + 1][j][newRemainder];
                int right = dp[i][j + 1][newRemainder];
                
                dp[i][j][remainder] = (down + right) % mod;
            }
        }
    }
    return dp[0][0][0];
}

int main() {
    vector<vector<int>> grid = {{5,2,4},{3,0,5},{0,7,2}};
    int k = 3;

    cout << numberOfPaths(grid, k) << endl;

    return 0;
}