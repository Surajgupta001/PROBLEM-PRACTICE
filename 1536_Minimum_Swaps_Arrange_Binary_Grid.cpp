/*
Minimum Swaps to Arrange a Binary Grid  - [Leetcode - 1536(Medium)]
---------------------------------------------------------------------
Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

Example 1:

Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3

Example 2:

Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.

Example 3:

Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0

Constraints:

n == grid.length == grid[i].length
1 <= n <= 200
grid[i][j] is either 0 or 1
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minSwaps(vector<vector<int>> &grid) {
    int n = grid.size();

    vector<int> endZeros(n, 0);
    // endZeros[i] = count of consecutive 0s from the end of ith row

    for(int i = 0; i < n; i++){
        int j = n - 1; // Start from the last column of the current row
        
        int count = 0;
        while(j >= 0 && grid[i][j] == 0){ // Count consecutive zeros from the end of the row
            count++;
            j--;
        }
        
        endZeros[i] = count; // Store the count of consecutive zeros for the current row
    }

    int swaps = 0;
    for(int i = 0; i < n; i++){
        int need = n - 1 - i; // Number of zeros needed for the current row to be valid
        
        int j = i; // FIX: start from current row, not 1
        while(j < n && endZeros[j] < need){
            j++;
        }

        if (j == n) return -1; // No row found with enough zeros, grid cannot be made valid

        swaps += (j - i); // Count the number of swaps needed to move the row with enough zeros to the current position

        while(j > i){ // Move the row with enough zeros up to the current position
            swap(endZeros[j], endZeros[j - 1]);
            j--;
        }
    }

    return swaps;
}

int main() {
    vector<vector<int>> grid1 = {{0, 0, 1}, {1, 1, 0}, {1, 0, 0}};
    cout << minSwaps(grid1) << endl; // Output: 3

    vector<vector<int>> grid2 = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}};
    cout << minSwaps(grid2) << endl; // Output: -1

    vector<vector<int>> grid3 = {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}};
    cout << minSwaps(grid3) << endl; // Output: 0

    return 0;
}