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

vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// DFS to check if we can reach (n-1, n-1) from (0, 0) at given time
bool possibleToReach(vector<vector<int>>& grid, int i, int j, int time, vector<vector<bool>>& visited){
    int n = grid.size();

    // Base Cases
    if(i < 0 || i >= n || j < 0 || j >= n || grid[i][j] > time || visited[i][j] == true){
        return false;
    }

    visited[i][j] = true; // Mark cell as visited
    if(i == n - 1 && j == n - 1){ // Reached destination
        return true;
    }

    for(auto& dir : directions){
        int newX = i + dir[0]; // New row
        int newY = j + dir[1]; // New column

        if(possibleToReach(grid, newX, newY, time, visited)){ // Explore in all 4 directions
            return true;
        }
    }

    return false;
}

// Approach - 1: Binary Search On Answer
int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();

    int low = grid[0][0]; // Minimum time to reach (0, 0)
    int high = n * n - 1; // Maximum time to reach (n-1, n-1)

    int result = 0;

    while(low <= high){
        int mid = low + (high - low) / 2; // Mid time to check if we can reach (n-1, n-1)

        vector<vector<bool>> visited(n, vector<bool>(n, false)); // To keep track of visited cells
        if(possibleToReach(grid, 0, 0, mid, visited)){
            result = mid; // Update result if we can reach (n-1, n-1) at time mid
            high = mid - 1; // Try to find a smaller time
        }
        else {
            low = mid + 1; // Try to find a larger time
        }
    }
    return result;
}

// Approach - 2: Dijkstra's Algorithm (Using Min-Heap)
int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false)); // To keep track of visited cells
    
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> minHeap; // Min-Heap to store {elevation, {x, y}}
    
    minHeap.push({grid[0][0], {0, 0}}); // Start from (0, 0)
    
    visited[0][0] = true; // Mark (0, 0) as visited
    
    int result = 0;

    while (!minHeap.empty()) {
        auto current = minHeap.top(); // Get the cell with the minimum elevation
        minHeap.pop(); // Remove the cell from the heap
        
        int elevation = current.first; // Current elevation
        
        int x = current.second.first; // Current row
        int y = current.second.second; // Current column
        
        result = max(result, elevation); // Update result with the maximum elevation encountered so far

        if (x == n - 1 && y == n - 1) { // Reached destination
            return result;
        }

        for (auto& dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            // Check if the new cell is within bounds and not visited
            if (newX >= 0 && newX < n && newY >= 0 && newY < n && !visited[newX][newY]) {
                visited[newX][newY] = true; // Mark new cell as visited
                minHeap.push({grid[newX][newY], {newX, newY}}); // Push new cell into the heap
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