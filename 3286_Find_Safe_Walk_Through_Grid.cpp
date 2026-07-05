/*
Find a Safe Walk Through a Grid - [Leetcode - 3286(Medium)]
---------------------------------------------------------------

You are given an m x n binary matrix grid and an integer health.

You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).

You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.

Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.

Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.

Example 1:

Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.

Example 2:

Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3

Output: false

Explanation:

A minimum of 4 health points is needed to reach the final cell safely.

Example 3:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.



Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.

 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
2 <= m * n
1 <= health <= m + n
grid[i][j] is either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
using namespace std;

// Approach : O/1 BFS
bool findSafeWalk(vector<vector<int>>& grid, int health) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> result(m, vector<int>(n, INT_MAX));
    // result[i][j] = minimum health required to reach cell (i, j) from (0, 0)

    deque<pair<int, int>> dq;

    result[0][0] = grid[0][0]; // source is [0][0]
    dq.push_back({0, 0});

    while(!dq.empty()){
        int x = dq.front().first;
        int y = dq.front().second;
        dq.pop_front();

        // 4 directions
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        for(auto &dir: directions){
            int newX = x + dir[0];
            int newY = y + dir[1];

            if(newX < 0 || newX >= m || newY < 0 || newY >= n) continue;

            if(result[x][y] + grid[newX][newY] < result[newX][newY]){
                result[newX][newY] = result[x][y] + grid[newX][newY];

                if(grid[newX][newY] == 0){
                    dq.push_front({newX, newY});
                } else {
                    dq.push_back({newX, newY});
                }
            }
        }
    }

    int minHealthRequired = result[m - 1][n - 1];
    return health - minHealthRequired >= 1;
}

int main() {
    vector<vector<int>> grid1 = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    int health1 = 1;
    cout << (findSafeWalk(grid1, health1) ? "true" : "false") << endl; // Output: true

    vector<vector<int>> grid2 = {{0,1,1,0,0,0},{1,0,1,0,0,0},{0,1,1,1,0,1},{0,0,1,0,1,0}};
    int health2 = 3;
    cout << (findSafeWalk(grid2, health2) ? "true" : "false") << endl; // Output: false

    vector<vector<int>> grid3 = {{1,1,1},{1,0,1},{1,1,1}};
    int health3 = 5;
    cout << (findSafeWalk(grid3, health3) ? "true" : "false") << endl; // Output: true

    return 0;
}