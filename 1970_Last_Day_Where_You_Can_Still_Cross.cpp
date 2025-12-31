/*
Last Day Where You Can Still Cross - [Leetcode - 1970(Hard)]
----------------------------------------------------------------
There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col representing the number of rows and columns in the matrix, respectively.

Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) will be covered with water (i.e., changed to 1).

You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal directions (left, right, up, and down).

Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.

Example 1:

Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
Output: 2
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 2.

Example 2:

Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
Output: 1
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 1.

Example 3:

Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
Output: 3
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 3.

Constraints:

2 <= row, col <= 2 * 10^4
4 <= row * col <= 2 * 10^4
cells.length == row * col
1 <= ri <= row
1 <= ci <= col
All the values of cells are unique.
*/ 

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

// BFS/DFS => Brute Force => TLE
int latestDayToCross(int row, int col, vector<vector<int>>& cells) {

}

// ======================================================================================
// Binary Search + DFS => Optimized Approach

bool dfs(int i, int j, vector<vector<int>>& grid, int row, int col) {
    if(i < 0 || j < 0 || i >= row || j >= col || grid[i][j] == 1){
        return false;
    }

    if(i == row - 1){  // Reached the last row
        return true;
    }

    grid[i][j] = 1; // Mark as visited

    for(auto& dir : directions){
        int new_i = i + dir[0];
        int new_j = j + dir[1];

        if(dfs(new_i, new_j, grid, row, col)){
            return true;
        }
    }

    return false;
}

bool canCross(int row, int col, vector<vector<int>>& cells, int mid) {
    vector<vector<int>> grid(row, vector<int>(col, 0));

    for(int i=0; i<=mid; i++){
        int x = cells[i][0] - 1; // 0-based indexing
        int y = cells[i][1] - 1; // 0-based indexing

        grid[x][y] = 1; // Mark as water
    }

    for(int j=0; j<col; j++){
        if(grid[0][j] == 0 && dfs(0, j, grid, row, col)){
            return true;
        }
    }

    return false;
}

int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
    int low = 0;
    int high = cells.size() - 1;

    int lastDay = 0;

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(canCross(row, col, cells, mid)){
            lastDay = mid + 1; // +1 for 1-based indexing
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return lastDay;
}

// ==========================================================================================
// Binary Search + BFS => Optimized Approach
bool bfs(int i, int j, vector<vector<int>>& grid, int row, int col) {
    queue<pair<int, int>> qu;
    qu.push({i, j});
    grid[i][j] = 1; // Mark as visited

    while(!qu.empty()){
        auto temp = qu.front();
        qu.pop();

        int x = temp.first;
        int y = temp.second;

        if(x == row - 1){ // Reached the last row
            return true;
        }

        for(auto &dir : directions){
            int new_x = x + dir[0];
            int new_y = y + dir[1];

            if(new_x >= 0 && new_y >= 0 && new_x < row && new_y < col && grid[new_x][new_y] == 0){
                qu.push({new_x, new_y});
                grid[new_x][new_y] = 1; // Mark as visited
            }
        }
    }
    return false;
}

bool canCross(int row, int col, vector<vector<int>>& cells, int mid) {
    vector<vector<int>> grid(row, vector<int>(col, 0));

    for(int i=0; i<=mid; i++){
        int x = cells[i][0] - 1; // 0-based indexing
        int y = cells[i][1] - 1; // 0-based indexing

        grid[x][y] = 1; // Mark as water
    }

    for(int j=0; j<col; j++){
        if(grid[0][j] == 0 && bfs(0, j, grid, row, col)){
            return true;
        }
    }

    return false;
}

int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
    int low = 0;
    int high = cells.size() - 1;

    int lastDay = 0;

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(canCross(row, col, cells, mid)){
            lastDay = mid + 1; // +1 for 1-based indexing
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return lastDay;
}

// ===============================================================================================
// Union-Find => Optimized Approach
int find(vector<int>& parent, int x) {
    if(parent[x] != x){
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

void Union(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = find(parent, a);
    b = find(parent, b);

    if(a == b) return;
    if(rank[a] < rank[b]){
        parent[a] = b;
    } else if(rank[a] > rank[b]){
        parent[b] = a;
    } else {
        parent[b] = a;
        rank[a]++;
    }
}

int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
    int top = row * col;
    int bottom = row * col + 1;

    vector<int> parent(row * col + 2);
    vector<int> rank(row * col + 2, 0);

    for(int i=0; i<parent.size(); i++){
        parent[i] = i;
    }

    vector<vector<int>> grid(row, vector<int>(col, 0));

    for(int day = cells.size()-1; day >= 0; day--){
        int x = cells[day][0] - 1; // 0-based indexing
        int y = cells[day][1] - 1; // 0-based indexing

        grid[x][y] = 1; // Mark as water
        int cellIndex = x * col + y;

        for(auto& dir : directions){
            int new_x = x + dir[0];
            int new_y = y + dir[1];

            if(new_x >= 0 && new_y >= 0 && new_x < row && new_y < col && grid[new_x][new_y] == 1){
                int neighborIndex = new_x * col + new_y;
                Union(parent, rank, cellIndex, neighborIndex);
            }
        }

        if(x == 0){
            Union(parent, rank, cellIndex, top);
        }

        if(x == row - 1){
            Union(parent, rank, cellIndex, bottom);
        }

        if(find(parent, top) == find(parent, bottom)){
            return day;
        }
    }
    return 0;
}

int main() {
    int row = 2;
    int col = 2;
    vector<vector<int>> cells = {{1,1},{2,1},{1,2},{2,2}};

    cout << "Last Day Where You Can Still Cross: " << latestDayToCross(row, col, cells) << endl;

    return 0;
}