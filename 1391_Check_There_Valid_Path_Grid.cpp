/*
Check if There is a Valid Path in a Grid - [Leetcode - 1391(Medium)]
-------------------------------------------------------------------------
You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:

1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.

You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

Notice that you are not allowed to change any street.

Return true if there is a valid path in the grid or false otherwise.

Example 1:


Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).

Example 2:

Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)

Example 3:

Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6
*/


#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, vector<pair<int, int>>> directions = {
    {1, {{0, -1}, {0, 1}}}, // left, right
    {2, {{-1, 0}, {1, 0}}}, // up, down
    {3, {{0, -1}, {1, 0}}}, // left, down
    {4, {{0, 1}, {1, 0}}}, // right, down
    {5, {{0, -1}, {-1, 0}}}, // left, up
    {6, {{0, 1}, {-1, 0}}} // right, up
};

bool dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j){
    int m = grid.size();
    int n = grid[0].size();

    if (i == m - 1 && j == n - 1) {
        return true;
    }

    visited[i][j] = true;

    for (auto& dir : directions[grid[i][j]]) {
        int newX = i + dir.first;
        int newY = j + dir.second;

        if (newX >= 0 && newX < m && newY >= 0 && newY < n && !visited[newX][newY]) {
            // Check if the next cell has a valid connection back to the current cell
            for (auto& nextDir : directions[grid[newX][newY]]) {
                if (newX + nextDir.first == i && newY + nextDir.second == j) {
                    if (dfs(grid, visited, newX, newY)) {
                        return true;
                    }
                }
            }
        }
    }

    visited[i][j] = false; // Backtrack
    return false;
}

bool hasValidPath(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<bool>> visited(m, vector<bool>(n, false));

    return dfs(grid, visited, 0, 0);
}

int main() {
    vector<vector<int>> grid1 = {{2, 4, 3}, {6, 5, 2}};
    vector<vector<int>> grid2 = {{1, 2, 1}, {1, 2, 1}};
    vector<vector<int>> grid3 = {{1, 1, 2}};

    cout << boolalpha; // Print bool values as true/false
    cout << "Grid 1: " << hasValidPath(grid1) << endl; // Expected: true
    cout << "Grid 2: " << hasValidPath(grid2) << endl; // Expected: false
    cout << "Grid 3: " << hasValidPath(grid3) << endl; // Expected: false

    return 0;
}