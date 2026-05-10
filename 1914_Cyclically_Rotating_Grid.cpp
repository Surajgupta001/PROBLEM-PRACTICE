/*
Cyclically Rotating a Grid - [Leetcode - 1914(Medium)]
--------------------------------------------------------
You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.

The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:

A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:

Return the matrix after applying k cyclic rotations to it.

Example 1:

Input: grid = [[40,10],[30,20]], k = 1
Output: [[10,20],[40,30]]
Explanation: The figures above represent the grid at every state.

Example 2:

Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
Explanation: The figures above represent the grid at every state.

Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 50
Both m and n are even integers.
1 <= grid[i][j] <= 5000
1 <= k <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    int layers = min(m, n) / 2; //each layer require two rows and two columns

    for (int layer = 0; layer < layers; layer++) {

        vector<int> nums;

        int top = layer;
        int bottom = m - layer - 1;
        int left = layer;
        int right = n - layer - 1;

        // Top row (left -> right)
        for (int j = left; j <= right; j++) {
            nums.push_back(grid[top][j]);
        }

        // Right column (top -> bottom)
        // Skip corners because they are already included in top/bottom rows
        for (int i = top + 1; i <= bottom - 1; i++) {
            nums.push_back(grid[i][right]);
        }

        // Bottom row (right -> left)
        for (int j = right; j >= left; j--) {
            nums.push_back(grid[bottom][j]);
        }

        // Left column (bottom -> top)
        // Skip corners because they are already included in top/bottom rows
        for (int i = bottom - 1; i >= top + 1; i--) {
            nums.push_back(grid[i][left]);
        }

        int len = nums.size();

        int nomralized_k = k % len;

        rotate(begin(nums), begin(nums) + nomralized_k, end(nums));

        int idx = 0;

        for (int j = left; j <= right; j++) {
            grid[top][j] = nums[idx++];
        }

        for (int i = top + 1; i <= bottom - 1; i++) {
            grid[i][right] = nums[idx++];
        }

        for (int j = right; j >= left; j--) {
            grid[bottom][j] = nums[idx++];
        }

        for (int i = bottom - 1; i >= top + 1; i--) {
            grid[i][left] = nums[idx++];
        }
    }

    return grid;
}

int main() {
    vector<vector<int>> grid1 = {{40,10},{30,20}};
    int k1 = 1;
    vector<vector<int>> result1 = rotateGrid(grid1, k1);
    for (const auto& row : result1) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vector<int>> grid2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    int k2 = 2;
    vector<vector<int>> result2 = rotateGrid(grid2, k2);
    for (const auto& row : result2) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}