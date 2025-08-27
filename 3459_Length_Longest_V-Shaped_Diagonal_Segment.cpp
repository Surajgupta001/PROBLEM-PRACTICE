/*
Length of Longest V-Shaped Diagonal Segment - [LeetCode - 3459(Hard)]
-----------------------------------------------------------------------
You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.

A V-shaped diagonal segment is defined as:

The segment starts with 1.
The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
The segment:
Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
Continues the sequence in the same diagonal direction.
Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.

Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.

Example 1:

Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]

Output: 5

Explanation:

The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).

Example 2:

Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]

Output: 4

Explanation:

The longest V-shaped diagonal segment has a length of 4 and follows these coordinates: (2,3) → (3,2), takes a 90-degree clockwise turn at (3,2), and continues as (2,1) → (1,0).

Example 3:

Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]

Output: 5

Explanation:

The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,0) → (1,1) → (2,2) → (3,3) → (4,4).

Example 4:

Input: grid = [[1]]

Output: 1

Explanation:

The longest V-shaped diagonal segment has a length of 1 and follows these coordinates: (0,0).

Constraints:

n == grid.length
m == grid[i].length
1 <= n, m <= 500
grid[i][j] is either 0, 1 or 2.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> dir = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

int solve(int i, int j, int d, bool canTurn, int val, vector<vector<int>> &grid, vector<vector<vector<vector<int>>>> &dp){
    int m = grid.size();
    int n = grid[0].size();

    int i_ = i + dir[d][0];
    int j_ = j + dir[d][1];

    if(i_ < 0 || i_ >= m || j_ < 0 || j_ >= n || grid[i_][j_] != val) return 0;

    if(dp[i_][j_][d][canTurn] != -1) return dp[i_][j_][d][canTurn];

    int result = 0;
    int keepMoving = 1 + solve(i_, j_, d, canTurn, val == 2 ? 0 : 2, grid, dp);
    result = max(result, keepMoving);

    if(canTurn == true){
        int turnAndMove = max(keepMoving, 1 + solve(i_, j_, (d + 1) % 4, false, val == 2 ? 0 : 2, grid, dp));
        result = max(result, turnAndMove);
    }

    return dp[i_][j_][d][canTurn] = result;
}

int lenOfVDiagonal(vector<vector<int>> &grid){
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<vector<vector<int>>>> dp(m, vector<vector<vector<int>>>(n, vector<vector<int>>(4, vector<int>(2, -1))));

    int result = 0;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 1){
                for(int d = 0; d <= 3; d++){
                    result = max(result, 1 + solve(i, j, d, true, 2, grid, dp));
                }
            }
        }
    }

    return result;
}

int main(){
    vector<vector<int>> grid = {
        {2, 2, 1, 2, 2},
        {2, 0, 2, 2, 0},
        {2, 0, 1, 1, 0},
        {1, 0, 2, 2, 2},
        {2, 0, 0, 2, 2}
    };
    
    cout << lenOfVDiagonal(grid) << endl;
    
    return 0;
}