/*
Maximum Score From Grid Operations - [Leetcode - 32225]
------------------------------------------------------------
You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.

The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.

Return the maximum score that can be achieved after some number of operations.

Example 1:

Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]

Output: 11

Explanation:

In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.

Example 2:

Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]

Output: 94

Explanation:


We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. The score of the resulting grid is grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4] which is equal to 94.

Constraints:

1 <= n == grid.length <= 100
n == grid[i].length
0 <= grid[i][j] <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Approach-1 (Brute Force) - TLE
//T.C : O((n+1)^n * n^2))
//S.C : O(n)
long long computeScore(vector<int>& h, vector<vector<int>>& grid, int n) {
    long long score = 0;
    
    for (int j = 0; j < n; j++) {
        for (int i = h[j] + 1; i < n; i++) {
            
            bool hasBlackNeighbor = false;

            if (j - 1 >= 0 && i <= h[j - 1]) hasBlackNeighbor = true;
            if (j + 1 < n && i <= h[j + 1]) hasBlackNeighbor = true;
            if (hasBlackNeighbor) score += grid[i][j];
        }
    }
    return score;
}

void helper(int col, vector<int>& h, vector<vector<int>>& grid, int n, long long& result) {
    if (col == n) {
        result = max(result, computeScore(h, grid, n));
        return;
    }

    // allow -1 (no operation)
    for (int height = -1; height < n; height++) {
        h[col] = height;
        helper(col + 1, h, grid, n, result);
    }
}

long long maximumScore(vector<vector<int>>& grid) {
    int n = grid.size();

    vector<int> h(n);
    
    long long result = 0;
    
    helper(0, h, grid, n, result);
    
    return result;
}

//Approach-2 (Brute Force with improved computeScore)
//T.C : O((n+1)^n * n))
//S.C : O(n^2)
long long computeScore(vector<int>& h, vector<vector<long long>>& colPrefSum, int n) {
    long long score = 0;
    
    for (int col = 0; col < n; col++) {
        int left = (col - 1 >= 0 ? h[col - 1] : -1);
        int right = (col + 1 < n ? h[col + 1] : -1);
        
        int upper = max(left, right); // highest black neighbor
        int lower = h[col];           // current column height
        
        if (upper > lower) {
            score += colPrefSum[upper + 1][col + 1] - colPrefSum[lower + 1][col + 1];
        }
    }

    return score;
}

void helper(int col, vector<int>& h, vector<vector<long long>>& colPrefSum, int n, long long& result) {
    if (col == n) {
        result = max(result, computeScore(h, colPrefSum, n));
        return;
    }

    for (int height = -1; height < n; height++) {
        h[col] = height;
        helper(col + 1, h, colPrefSum, n, result);
    }
}

long long maximumScore(vector<vector<int>>& grid) {
    int n = grid.size();
  
    vector<vector<long long>> colPrefSum(n + 1, vector<long long>(n + 1, 0));
    for (int col = 1; col <= n; col++) {
        for (int row = 1; row <= n; row++) {
            colPrefSum[row][col] = colPrefSum[row - 1][col] + grid[row - 1][col-1];
        }
    }

    vector<int> h(n);
    
    long long result = 0;
    
    helper(0, h, colPrefSum, n, result);
    
    return result;
}

//Approach-3 (Most optimal)
//T.C : O(n^3)
//S.C : O(n^2)
long long helper(bool prevTaken, int prevHeight, int col, vector<vector<int>>& grid, vector<vector<long long>>& colPrefSum, vector<vector<vector<long long>>>& dp) {
    int n = grid.size();
    
    if(col == n) {
        return 0;
    }
    
    long long result = 0;
    
    if(dp[prevTaken][prevHeight][col] != -1) {
        return dp[prevTaken][prevHeight][col];
    } 
    
    for(int height = 0; height <= n; height++) {
        long long prevColScore = 0;
        long long currColScore = 0;
        
        if(!prevTaken && col-1 >= 0 && height > prevHeight) {
            prevColScore += colPrefSum[height][col] - colPrefSum[prevHeight][col];
        }
        
        if(prevHeight > height) {
            currColScore += colPrefSum[prevHeight][col+1] - colPrefSum[height][col+1];
        }
        
        long long currColScoreTaken    = currColScore + prevColScore + helper(true, height, col+1, grid, colPrefSum, dp);
        long long currColScoreNotTaken = prevColScore + helper(false, height, col+1, grid, colPrefSum, dp);
        
        result = max({result, currColScoreTaken, currColScoreNotTaken});
    }

    return dp[prevTaken][prevHeight][col] = result;
}

long long maximumScore(vector<vector<int>>& grid) {
    int n = grid.size();
    
    vector<vector<vector<long long>>> dp(2, vector<vector<long long>>(n + 1, vector<long long>(n + 1, -1)));
    vector<vector<long long>> colPrefSum(n + 1, vector<long long>(n + 1, 0));
    
    for(int col = 1; col <= n; col++) {
        for(int row = 1; row <= n; row++) {
            colPrefSum[row][col] = colPrefSum[row-1][col] + grid[row-1][col-1];
        }
    }
    
    return helper(false, 0, 0, grid, colPrefSum, dp);
}

int main (){
        
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> grid = {{0,0,0,0,0},{0,0,3,0,0},{0,1,0,0,0},{5,0,0,3,0},{0,0,0,0,2}};
    
    cout << maximumScore(grid) << "\n";
    
    return 0;
}