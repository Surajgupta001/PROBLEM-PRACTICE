/*
Minimum Cost Path with Teleportations - [Leetcode - 3651(Hard)]
------------------------------------------------------------------
You are given a m x n 2D integer array grid and an integer k. You start at the top-left cell (0, 0) and your goal is to reach the bottom‐right cell (m - 1, n - 1).

There are two types of moves available:

Normal move: You can move right or down from your current cell (i, j), i.e. you can move to (i, j + 1) (right) or (i + 1, j) (down). The cost is the value of the destination cell.

Teleportation: You can teleport from any cell (i, j), to any cell (x, y) such that grid[x][y] <= grid[i][j]; the cost of this move is 0. You may teleport at most k times.

Return the minimum total cost to reach cell (m - 1, n - 1) from (0, 0).

Example 1:

Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2

Output: 7

Explanation:

Initially we are at (0, 0) and cost is 0.

Current Position	Move	New Position	Total Cost
(0, 0)	Move Down	(1, 0)	0 + 2 = 2
(1, 0)	Move Right	(1, 1)	2 + 5 = 7
(1, 1)	Teleport to (2, 2)	(2, 2)	7 + 0 = 7
The minimum cost to reach bottom-right cell is 7.

Example 2:

Input: grid = [[1,2],[2,3],[3,4]], k = 1

Output: 9

Explanation:

Initially we are at (0, 0) and cost is 0.

Current Position	Move	New Position	Total Cost
(0, 0)	Move Down	(1, 0)	0 + 2 = 2
(1, 0)	Move Right	(1, 1)	2 + 3 = 5
(1, 1)	Move Down	(2, 1)	5 + 4 = 9
The minimum cost to reach bottom-right cell is 9.

Constraints:

2 <= m, n <= 80
m == grid.length
n == grid[i].length
0 <= grid[i][j] <= 10^4
0 <= k <= 10
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;


//Approach-1 (Recursion + Memoization)
//T.C : O(m^2 * n^2 * k)
//S.C : O(m*n*k)

// dp[i][j][tPort] = min cost from (i,j) with tPort teleports already used
int solve(int i, int j, int tPort, vector<vector<int>>& grid, vector<vector<vector<int>>> dp) {
    int m = grid.size();
    int n = grid[0].size();
    int K = dp[0][0].size() - 1;

    // Reached destination
    if (i == m - 1 && j == n - 1) return 0;
    
    if (dp[i][j][tPort] != -1) return dp[i][j][tPort];
    
    int result = 1e9; //Large value
    int curVal = grid[i][j];
    
    // Move Right
    if (j + 1 < n) {
        int next = solve(i, j + 1, tPort, grid, dp);
        result = min(result, grid[i][j + 1] + next);
    }
    
    // Move Down
    if (i + 1 < m) {
        int next = solve(i + 1, j, tPort, grid, dp);
        result = min(result, grid[i + 1][j] + next);
    }
    
    // Teleport
    if (tPort < K) {
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if ((x != i || y != j) && grid[x][y] <= curVal) {
                    result = min(result, solve(x, y, tPort + 1, grid, dp)); // cost = 0
                }
            }
        }
    }

    return dp[i][j][tPort] = result;
}

int minCost(vector<vector<int>>& grid, int k) {
    int K = k;
    int m = grid.size();
    int n = grid[0].size();
    
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(K + 1, -1)));
    
    return solve(0, 0, 0, grid, dp);
}

//Approach-2 (Bottom Up)
//T.C : O(m^2 * n^2 * k)
//S.C : O(m*n*k)
int minCost(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    const int INF = 1e9;

    // t[i][j][tPort] = min cost from (i,j) with tPort teleports already used
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, INF)));

    // Base case: destination
    for (int tPort = 0; tPort <= k; tPort++) {
        dp[m - 1][n - 1][tPort] = 0;
    }

    // Fill teleport layers from back to front
    for (int tPort = k; tPort >= 0; tPort--) {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (i == m - 1 && j == n - 1) continue;

                int result = 1e9;

                // Right
                if (j + 1 < n) {
                    result = min(result, grid[i][j + 1] + dp[i][j + 1][tPort]);
                }

                // Down
                if (i + 1 < m) {
                    result = min(result, grid[i + 1][j] + dp[i + 1][j][tPort]);
                }

                // Teleport
                if (tPort < k) {
                    for (int x = 0; x < m; x++) {
                        for (int y = 0; y < n; y++) {
                            if ((x != i || y != j) && grid[x][y] <= grid[i][j]) {
                                result = min(result, dp[x][y][tPort + 1]);
                            }
                        }
                    }
                }

                dp[i][j][tPort] = result;
            }
        }
    }

    return dp[0][0][0];
}

//Approach-3 (Bottom Up with Layered DP for optimization)
//T.C : O(m*n*k)
//S.C : O(m*n*k)

// Layered Dynamic Programming => It's just a DP technique in which we solve the same problem multiple times each time allowing one more unit of a limited resource (here Teleportations).

int minCost(vector<vector<int>>& grid, int k){
    int m = grid.size();
    int n = grid[0].size();
    
    vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
    dp[m-1][n-1] = 0; // Base case: destination cell cost is 0
    
    int maxVal = 0;
    
    for(auto &row : grid){
        for(int &val : row) {
            maxVal = max(maxVal, val);
        }
    }
    
    vector<int> teleportCost(maxVal+1, INT_MAX);
    
    for(int t = 0; t <= k; t++){
        for(int i = m-1; i >= 0; i--){
            for(int j = n-1; j >= 0; j--){
                if(i+1 < m){ // Down Move
                    dp[i][j] = min(dp[i][j], grid[i+1][j] + dp[i+1][j]);
                }
                
                if(j+1 < n){ // Right Move
                    dp[i][j] = min(dp[i][j], grid[i][j+1] + dp[i][j+1]);
                }

                if(t > 0) { // Teleportation
                    dp[i][j] = min(dp[i][j], teleportCost[grid[i][j]]);
                }
            }
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                // Update teleportCost for current grid value
                teleportCost[grid[i][j]] = min(teleportCost[grid[i][j]], dp[i][j]);
            }
        }

        for(int i = 1; i < teleportCost.size(); i++){
            // Propagate minimum costs to higher values
            teleportCost[i] = min(teleportCost[i], teleportCost[i-1]);
        }
    }
    return dp[0][0];
}

int main() {
    vector<vector<int>> grid1 = {{1,3,3},{2,5,4},{4,3,5}};
    int k1 = 2;
    cout << "Minimum Cost Path with Teleportations (Example 1): " << minCost(grid1, k1) << endl; // Output: 7

    vector<vector<int>> grid2 = {{1,2},{2,3},{3,4}};
    int k2 = 1;
    cout << "Minimum Cost Path with Teleportations (Example 2): " << minCost(grid2, k2) << endl; // Output: 9

    return 0;
}