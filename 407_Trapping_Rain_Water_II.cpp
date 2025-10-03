/*
Trapping Rain Water II - [Leetcode - 407(Hard)]
------------------------------------------------
Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.

Example 1:


Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
Output: 4
Explanation: After the rain, water is trapped between the blocks.
We have two small ponds 1 and 3 units trapped.
The total volume of water trapped is 4.

Example 2:

Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
Output: 10
 
Constraints:

m == heightMap.length
n == heightMap[i].length
1 <= m, n <= 200
0 <= heightMap[i][j] <= 2 * 104
 
*/ 

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // left, right, up, down

int trapRainWater(vector<vector<int>>& heightMap) {
    int m = heightMap.size();
   int n = heightMap[0].size();

   // Min-heap to store the boundary cells with their heights and coordinates - {height, {row, col}}
    priority_queue< pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> > boundaryCells;

    // 2D vector to keep track of visited cells
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    // Left most column and Right most column (0, n-1)
    for(int row=0; row<m; row++){
        // Iterate over the two columns only
        for(auto col : {0, n-1}){
            // Push the boundary cell into the min-heap because they can't trap water themselves
            boundaryCells.push({heightMap[row][col], {row, col}});

            // Mark the cell as visited
            visited[row][col] = true;
        }
    }

    // Top most row and Bottom most row (0, m-1)
    for(int col=0; col<n; col++){
        // Iterate over the two rows only
        for(auto row : {0, m-1}){
            // Push the boundary cell into the min-heap because they can't trap water themselves
            boundaryCells.push({heightMap[row][col], {row, col}});

            // Mark the cell as visited
            visited[row][col] = true;
        }
    }

    int water = 0; // To store the total trapped water

    // T.C : O(m * n * log(m * n))
    // S.C : O(m * n)
    while(not boundaryCells.empty()){
        // Get the cell with the minimum height from the boundary
        auto cell = boundaryCells.top(); // {height, {row, col}}
        boundaryCells.pop(); // Remove the cell from the min-heap ; O(log(m*n))

        int height = cell.first; // Height of the current boundary cell
        int row = cell.second.first; // Row index of the current boundary cell
        int col = cell.second.second; // Column index of the current boundary cell

        // Find neighbors of the current cell
        for(vector<int> dir : directions){
            // Calculate the coordinates of the neighbor cell
            int newRow = row + dir[0]; // New row index
            int newCol = col + dir[1]; // New column index

            // Check if the neighbor is within bounds and not visited
            if(newRow >= 0 and newRow < m and newCol >= 0 and newCol < n and not visited[newRow][newCol]){
                // If the neighbor cell is lower than the current boundary height, it can trap water
                water += max(0, height - heightMap[newRow][newCol]); // Calculate trapped water at the neighbor cell
                
                // Push the neighbor cell into the min-heap with the updated height (max of its own height and current boundary height)
                boundaryCells.push({max(heightMap[newRow][newCol], height), {newRow, newCol}});
                
                // Mark the neighbor cell as visited
                visited[newRow][newCol] = true;
            }
        }
    }
    return water;
}

int main() {
    vector<vector<int>> heightMap = {
        {1,4,3,1,3,2},
        {3,2,1,3,2,4},
        {2,3,3,2,3,1}
    };

    cout << "Total trapped water: " << trapRainWater(heightMap) << endl; // Output: 4

    return 0;
}