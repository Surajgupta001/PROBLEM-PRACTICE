/*
Swim in Rising Water - [Leetcode - 778(Hard)]
-----------------------------------------------
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).

It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.

You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.

Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

Example 1:


Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.

Example 2:

Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
 
Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
0 <= grid[i][j] < n2
Each value grid[i][j] is unique.
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> minHeap;
    minHeap.push({grid[0][0], {0, 0}});
    visited[0][0] = true;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int result = 0;

    while (!minHeap.empty()) {
        auto current = minHeap.top();
        minHeap.pop();
        int elevation = current.first;
        int x = current.second.first;
        int y = current.second.second;
        result = max(result, elevation);

        if (x == n - 1 && y == n - 1) {
            return result;
        }

        for (auto& dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (newX >= 0 && newX < n && newY >= 0 && newY < n && !visited[newX][newY]) {
                visited[newX][newY] = true;
                minHeap.push({grid[newX][newY], {newX, newY}});
            }
        }
    }

    return result; // This line should never be reached
}

int main () {
    vector<vector<int>> grid1 = {{0, 2}, {1, 3}};
    cout << "Minimum time to reach bottom right in grid1: " << swimInWater(grid1) << endl; // Output: 3

    vector<vector<int>> grid2 = {
        {0, 1, 2, 3, 4},
        {24, 23, 22, 21, 5},
        {12, 13, 14, 15, 16},
        {11, 17, 18, 19, 20},
        {10, 9, 8, 7, 6}
    };
    cout << "Minimum time to reach bottom right in grid2: " << swimInWater(grid2) << endl; // Output: 16

    return 0;
}