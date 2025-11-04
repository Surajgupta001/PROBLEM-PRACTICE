/*
Count Unguarded Cells in the Grid - [Leetcode - 2257(Medium)]
---------------------------------------------------------------
You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.

A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.

Example 1:

Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
Output: 7
Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
There are a total of 7 unguarded cells, so we return 7.

Example 2:

Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
Output: 4
Explanation: The unguarded cells are shown in green in the above diagram.
There are a total of 4 unguarded cells, so we return 4.

Constraints:

1 <= m, n <= 10^5
2 <= m * n <= 10^5
1 <= guards.length, walls.length <= 5 * 10^4
2 <= guards.length + walls.length <= m * n
guards[i].length == walls[j].length == 2
0 <= rowi, rowj < m
0 <= coli, colj < n
All the positions in guards and walls are unique.
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Simulation or Iterative
void markGaurded(int row, int col, vector<vector<int>>& grid) {
    // Mark upwards
    for(int i = row - 1; i >= 0; i--){
        if(grid[i][col] == 2 || grid[i][col] == 3){ // If we encounter another guard or wall, stop marking
            break;
        }
        grid[i][col] = 1; // 1 represents guarded cell
    }

    // Mark downwards
    for(int i = row + 1; i < grid.size(); i++){
        if(grid[i][col] == 2 || grid[i][col] == 3){
            break;
        }
        grid[i][col] = 1;
    }

    // Mark leftwards
    for(int j = col - 1; j >= 0; j--){
        if(grid[row][j] == 2 || grid[row][j] == 3){
            break;
        }
        grid[row][j] = 1;
    }

    // Mark rightwards
    for(int j = col + 1; j < grid[0].size(); j++){
        if(grid[row][j] == 2 || grid[row][j] == 3){
            break;
        }
        grid[row][j] = 1;
    }
}

int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
    vector<vector<int>> grid(m, vector<int>(n, 0)); // 0 represents unoccupied cell
    
    // Mark Guards positions
    for(vector<int>& vec : guards){
        int i = vec[0];
        int j = vec[1];
        grid[i][j] = 2; // 2 represents guard
    }
    
    // Mark Walls positions
    for(vector<int>& vec : walls){
        int i = vec[0];
        int j = vec[1];
        grid[i][j] = 3; // 3 represents wall
    }

    for(vector<int>& guard : guards){
        int i = guard[0];
        int j = guard[1];
        markGaurded(i, j, grid); // Mark all the cells which are marked guarded by this guard
    }

    int unguardedCells = 0; // Count of unguarded cells
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 0){
                unguardedCells++;
            }
        }
    }
    
    return unguardedCells;
}

// Approach 2: Recursion (DFS)
vector<int> DR = {-1, 1, 0, 0};
vector<int> DC = {0, 0, -1, 1};

void dfs(int r, int c, int d, vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    int nr = r + DR[d];
    int nc = c + DC[d];

    if (nr < 0 || nc < 0 || nr >= m || nc >= n) return;
    
    if (grid[nr][nc] == 2 || grid[nr][nc] == 3) return; // stop at guard/wall
    if (grid[nr][nc] == 0) grid[nr][nc] = 1;            // mark guarded
    
    dfs(nr, nc, d, grid);                             // continue straight
}

int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
    vector<vector<int>> grid(m, vector<int>(n, 0)); // 0 empty, 1 guarded, 2 guard, 3 wall

    // place guards and walls
    for (auto& g : guards) grid[g[0]][g[1]] = 2;
    for (auto& w : walls)  grid[w[0]][w[1]] = 3;

    // cast 4 rays from each guard
    for (auto& g : guards){
        for (int d = 0; d < 4; ++d){
            dfs(g[0], g[1], d, grid);
        }
    }

    // count unguarded empty cells
    int unguardedCells = 0;
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            if (grid[i][j] == 0){
                unguardedCells++;
            }
        }
    }
    return unguardedCells;
}

int main() {
    // Example usage:
    int m = 4, n = 6;
    
    vector<vector<int>> guards = {{0,0},{1,1},{2,3}};
    vector<vector<int>> walls = {{0,1},{2,2},{1,4}};
    
    int result = countUnguarded(m, n, guards, walls); // Expected output: 7
    cout << "Number of unguarded cells: " << result << endl;
    
    return 0;
}