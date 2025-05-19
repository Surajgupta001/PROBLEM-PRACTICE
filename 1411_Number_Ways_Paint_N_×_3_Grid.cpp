/*
Number of Ways to Paint N × 3 Grid - [Leetcode - 1411(Hard)]
-------------------------------------------------------------
You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).

Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 109 + 7.

Example 1:


Input: n = 1
Output: 12
Explanation: There are 12 possible way to paint the grid as shown.
Example 2:

Input: n = 5000
Output: 30228214
 

Constraints:

n == grid.length
1 <= n <= 5000

Similar Problems: 1931 - [Leetcode(Hard)] : Painting a Grid With Three Different Colors => (Genrate Columns States)

Both of them solved using Recursion, DP and Bitmask with DP(Efficient Approach) approach
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int mod = 1e9 + 7;

// Generate all valid row states for 3 columns (no two adjacent same)
void generateRowStates(string curr, char prev, int len, vector<string>& rowStates) {
    if (len == 3) {
        rowStates.push_back(curr);
        return;
    }
    for (char c : {'R', 'Y', 'G'}) {
        if (c == prev) continue;
        generateRowStates(curr + c, c, len + 1, rowStates);
    }
}

// Check if two row states are compatible (no vertical same color)
bool isCompatible(const string& a, const string& b) {
    for (int i = 0; i < 3; ++i){
        if (a[i] == b[i]) return false;
    }
    return true;
}

int helper(int remainingRows, int prevIdx, const vector<string>& rowStates, vector<vector<int>>& dp) {
    
    if (remainingRows == 0) return 1;
    
    if (dp[remainingRows][prevIdx] != -1) return dp[remainingRows][prevIdx];

    int ways = 0;

    const string& prevState = rowStates[prevIdx];
    for (int i = 0; i < rowStates.size(); ++i) {
        if (isCompatible(prevState, rowStates[i])) {
            ways = (ways + helper(remainingRows - 1, i, rowStates, dp)) % mod;
        }
    }
    return dp[remainingRows][prevIdx] = ways;
}

int numOfWays(int n) {
    vector<string> rowStates;
    generateRowStates("", '#', 0, rowStates);

    int totalStates = rowStates.size();
    vector<vector<int>> dp(n, vector<int>(totalStates, -1));

    int result = 0;
    for (int i = 0; i < totalStates; ++i) {
        result = (result + helper(n - 1, i, rowStates, dp)) % mod;
    }
    return result;
}

int main() {
    int n = 1;
    cout << numOfWays(n) << endl; // Output: 12

    n = 5000;
    cout << numOfWays(n) << endl; // Output: 30228214

    return 0;
}