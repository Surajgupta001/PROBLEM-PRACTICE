/*
Pacific Atlantic Water Flow - [Leetcode - 417(Medium)]
-------------------------------------------------------
There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.



Example 1:


Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
Example 2:

Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.


Constraints:

m == heights.length
n == heights[r].length
1 <= m, n <= 200
0 <= heights[r][c] <= 10^5
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Defining the direction of BFS
vector<vector<int>> dir = {{1,0}, {-1,0}, {0,1}, {0,-1}}; // i, j -> i+1, j -> i-1, j -> i, j-1 -> i, j+1

vector<vector<bool>> bfs(queue<pair<int, int>>& qu, vector<vector<int>>& h, int rows, int cols){
    vector<vector<bool>> visited(rows, vector<bool>(cols, false)); // To keep track of visited cells
    while(not qu.empty()){
        auto cell = qu.front();
        qu.pop();
        
        int i = cell.first;
        int j = cell.second;
        
        visited[i][j] = true;
        
        for(int d=0; d<4; d++){
            int newRow = i + dir[d][0];
            int newCol = j + dir[d][1];
            
            if(newRow < 0 or newCol < 0 or newRow >= rows or newCol >= cols) continue; // You exited the grid
            
            if(visited[newRow][newCol]) continue; // You already visited this cell
            
            if(h[newRow][newCol] < h[i][j]) continue; // h[newRow][newCol] -> neighbours, h[i][j] -> currentCell
            
            qu.push({newRow, newCol}); // then only push the cell into the queue
        }
    }
    return visited;
}

// Function to find all cells that can flow to both the Pacific and Atlantic oceans
vector<vector<int>> pacificAtlantic(vector<vector<int>>& height){
    
    int rows = height.size();
    int cols = height[0].size();
    
    // Initialize queues for Pacific and Atlantic BFS
    queue<pair<int, int>> pacificBFS;
    queue<pair<int, int>> atlanticBFS;
    
    // Steps of Multi-Source BFS
    for(int i=0;i<rows;i++){
        pacificBFS.push({i, 0});
        atlanticBFS.push({i, cols-1});
    }
    
    // Add all cells on the Pacific border to the Pacific BFS queue
    for(int j=1;j<cols;j++) pacificBFS.push({0, j});
    for(int j=0;j<cols;j++) atlanticBFS.push({rows-1, j});

    // Perform BFS from both queues
    vector<vector<bool>>pacific = bfs(pacificBFS, height, rows, cols);
    vector<vector<bool>>atlantic = bfs(atlanticBFS, height, rows, cols);

    // Find all cells that can flow to both oceans
    vector<vector<int>> ans;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(pacific[i][j] and atlantic[i][j]){ // Check if the cell can flow to both oceans
                ans.push_back({i,j}); // then push it to the answer vector
            }
        }
    }
    return ans;
}

int main() {
    
    vector<vector<int>> height = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
    };

    vector<vector<int>> result = pacificAtlantic(height);
    cout << "Cells that can flow to both oceans:" << endl;
    for(auto& cell : result){
        cout<<"["<<cell[0]<<", "<<cell[1]<<"]"<< endl;
    }

    return 0;
}