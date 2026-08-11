/*
Maximum Non Negative Product in a Matrix - [Leetcode - 1594(Medium)]
-------------------------------------------------------------------------
You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.

Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.

Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.

Notice that the modulo is performed after getting the maximum product.

Example 1:


Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
Output: -1
Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.

Example 2:

Input: grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
Output: 8
Explanation: Maximum non-negative product is shown (1 * 1 * -2 * -4 * 1 = 8).
Example 3:


Input: grid = [[1,3],[0,-4]]
Output: 0
Explanation: Maximum non-negative product is shown (1 * 0 * -4 = 0).

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 15
-4 <= grid[i][j] <= 4
*/

#include <iostream>
#include <vector>
using namespace std;

#define ll long long
int mod = 1e9 + 7;

pair<ll, ll> helper(int i, int j, vector<vector<int>>& grid, vector<vector<pair<ll, ll>>>& dp) {
    int m = grid.size();
    int n = grid[0].size();

    if(i >= m || j >= n) {
        return {1, 1};
    }

    if(i == m - 1 && j == n - 1) {
        return {grid[i][j], grid[i][j]};
    }

    if (dp[i][j].first != LLONG_MIN && dp[i][j].second != LLONG_MAX) {
        return dp[i][j];
    }

    ll maxValue = LLONG_MIN;
    ll minValue = LLONG_MAX;

    // Down
    if(i + 1 < m){
        pair<ll, ll> down = helper(i + 1, j, grid, dp);
        ll downMax = down.first * grid[i][j];
        ll downMin = down.second * grid[i][j];

        maxValue = max({maxValue, downMax, downMin});
        minValue = min({minValue, downMax, downMin});
    }

    // Right
    if(j + 1 < n){
        pair<ll, ll> right = helper(i, j + 1, grid, dp);
        ll rightMax = right.first * grid[i][j];
        ll rightMin = right.second * grid[i][j];

        maxValue = max({maxValue, rightMax, rightMin});
        minValue = min({minValue, rightMax, rightMin});
    }

    // ====== Another method ===========
    // Down
    // if(i + 1 < m){
    //     auto[downMax, downMin] = helper(i + 1, j, grid);
    //     maxValue = max({maxValue, downMax * grid[i][j], downMin * grid[i][j]});
    //     minValue = min({minValue, downMax * grid[i][j], downMin * grid[i][j]});
    // }

    // // Right
    // if(j + 1 < n){
    //     auto[rightMax, rightMin] = helper(i, j + 1, grid);
    //     maxValue = max({maxValue, rightMax * grid[i][j], rightMin * grid[i][j]});
    //     minValue = min({minValue, rightMax * grid[i][j], rightMin * grid[i][j]});
    // }

    return dp[i][j] = {maxValue, minValue};
}

int maxProductPath(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<pair<ll, ll>>> dp(m, vector<pair<ll, ll>>(n, {LLONG_MIN, LLONG_MAX}));

    pair<ll, ll> result = helper(0, 0, grid, dp);
    ll maxProduct = result.first;

    return (maxProduct < 0) ? -1 : maxProduct % mod;
}

// Bottom UP
int maxProductPath(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<pair<ll, ll>>> dp(m, vector<pair<ll, ll>>(n));
    // dp[i][j] => {maxValue, minValue} from (i,j) to (m-1,n-1)

    dp[0][0] = {grid[0][0], grid[0][0]};

    // Filling the first row
    for(int j = 1; j < n; j++){
        dp[0][j].first = dp[0][j-1].first * grid[0][j];
        dp[0][j].second = dp[0][j-1].second * grid[0][j];
    }

    // Filling the first column
    for(int i = 1; i < m; i++){
        dp[i][0].first = dp[i-1][0].first * grid[i][0];
        dp[i][0].second = dp[i-1][0].second * grid[i][0];
    }

    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            ll upMax = dp[i-1][j].first * grid[i][j];
            ll upMin = dp[i-1][j].second * grid[i][j];

            ll leftMax = dp[i][j-1].first * grid[i][j];
            ll leftMin = dp[i][j-1].second * grid[i][j];

            dp[i][j].first = max({upMax, upMin, leftMax, leftMin});
            dp[i][j].second = min({upMax, upMin, leftMax, leftMin});
        }
    }
    
    pair<ll, ll> result = dp[m-1][n-1];
    
    ll maxProduct = result.first;

    return (maxProduct < 0) ? -1 : maxProduct % mod;
}

int main() {
    vector<vector<int>> grid = {{1, -2, 1}, {1, -2, 1}, {3, -4, 1}};
    cout << maxProductPath(grid) << endl; // Output: 8
    return 0;
}
