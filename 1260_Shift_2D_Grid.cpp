/*
Shift 2D Grid - [Leetcode - 1260(Easy)]
-------------------------------------------
Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.

In one shift operation:

Element at grid[i][j] moves to grid[i][j + 1].
Element at grid[i][n - 1] moves to grid[i + 1][0].
Element at grid[m - 1][n - 1] moves to grid[0][0].
Return the 2D grid after applying shift operation k times.
 

Example 1:

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]

Example 2:

Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
Example 3:

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m <= 50
1 <= n <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100
*/

// REFERENCES: Leetcode : 189 - Rotate Array => Use the same logic to shift the 2D grid by flattening it into a 1D array, performing the shift, and then reshaping it back into a 2D grid. 

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    // Flatten the 2D grid into a 1D vector
    vector<int> flatGrid;
    for (auto& row : grid) {
        flatGrid.insert(flatGrid.end(), row.begin(), row.end());
    }

    // Perform the shift operation on the flattened vector
    k = k % (m * n); // In case k is greater than the total number of elements
    if (k == 0) return grid; // No need to shift if k is 0

    reverse(flatGrid.begin(), flatGrid.end());
    reverse(flatGrid.begin(), flatGrid.begin() + k);
    reverse(flatGrid.begin() + k, flatGrid.end());

    // Reshape the flattened vector back into a 2D grid
    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = flatGrid[i * n + j];
        }
    }

    return result;
}

int main() {
    vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int k = 1;
    vector<vector<int>> shiftedGrid = shiftGrid(grid, k);
    
    for (const auto& row : shiftedGrid) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    return 0;
}