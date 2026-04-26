/*
Detect Cycles in 2D Grid - [Leetcode - 1559(Medium)]
--------------------------------------------------------------

Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.

Example 1:

Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:

Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

Example 3:

Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
Output: false
 
Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 500
grid consists only of lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
using namespace std;

//Approach-1 (Using DFS)
//T.C : O(m*n)
//S.C : O(m*n)
vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
bool cycleDetectDFS(int r, int c, int prev_r, int prev_c, vector<vector<char>>& grid, vector<vector<bool>>& visited ) {
    int m = grid.size();
    int n = grid[0].size();

    if(visited[r][c]) {
        return true;
    }
    
    visited[r][c] = true;
    
    //explore neighbours
    for(auto &dir : directions) {
        int new_r = r + dir[0]; 
        int new_c = c + dir[1];
        
        if(new_r >= 0 && new_r < m && new_c >= 0 && new_c < n && grid[new_r][new_c] == grid[r][c]) {
                if(new_r == prev_r && new_c == prev_c) continue;
                
                if(cycleDetectDFS(new_r, new_c, r, c, grid, visited)) {
                    return true;
                }
            }
    }
    return false;
}

bool containsCycle(vector<vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(!visited[i][j] && cycleDetectDFS(i, j, i, j, grid, visited)) {
                return true;
            }
        }
    }
    return false;
}

//Approach-2 (Using BFS)
//T.C : O(m*n)
//S.C : O(m*n)
vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
bool cycleDetectBFS(int r, int c, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
    int m = grid.size();
    int n = grid[0].size();
    
    //r, c, prev_r, prev_c
    queue<tuple<int, int, int, int>> que;
    
    que.emplace(r, c, -1, -1);
    
    visited[r][c] = true;
    
    while(!que.empty()) {
        auto [curr_r, curr_c, prev_r, prev_c] = que.front();
        que.pop();
        
        //explore neighbours
        for(auto &dir : directions) {
            int new_r = curr_r + dir[0];
            int new_c = curr_c + dir[1];
            
            if(new_r >= 0 && new_r < m && new_c >= 0 && new_c < n && grid[new_r][new_c] == grid[curr_r][curr_c]) {
                
                if(new_r == prev_r && new_c == prev_c) continue;
                
                if(visited[new_r][new_c]) return true;
                
                visited[new_r][new_c] = true;
                que.push({new_r, new_c, curr_r, curr_c});
            }
        }
    }
    return false;
}

bool containsCycle(vector<vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(!visited[i][j] && cycleDetectBFS(i, j, grid, visited)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<vector<char>> grid1 = {{'a','a','a','a'}, {'a','b','b','a'}, {'a','b','b','a'}, {'a','a','a','a'}};
    vector<vector<char>> grid2 = {{'c','c','c','a'}, {'c','d','c','c'}, {'c','c','e','c'}, {'f','c','c','c'}};
    vector<vector<char>> grid3 = {{'a','b','b'}, {'b','z','b'}, {'b','b','a'}};

    cout << containsCycle(grid1) << endl; // Output: true
    cout << containsCycle(grid2) << endl; // Output: true
    cout << containsCycle(grid3) << endl; // Output: false

    return 0;
}