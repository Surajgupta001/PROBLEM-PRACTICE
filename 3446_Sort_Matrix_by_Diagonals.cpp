/*
Sort Matrix by Diagonals - [Leetcode - 3446]
---------------------------------------------
You are given an n x n square matrix of integers grid. Return the matrix such that:

The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
The diagonals in the top-right triangle are sorted in non-decreasing order.

Example 1:

Input: grid = [[1,7,3],[9,8,2],[4,5,6]]

Output: [[8,2,3],[9,6,7],[4,5,1]]

Explanation:

The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:

[1, 8, 6] becomes [8, 6, 1].
[9, 5] and [4] remain unchanged.
The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:

[7, 2] becomes [2, 7].
[3] remains unchanged.
Example 2:

Input: grid = [[0,1],[1,2]]

Output: [[2,1],[1,0]]

Explanation:

The diagonals with a black arrow must be non-increasing, so [0, 2] is changed to [2, 0]. The other diagonals are already in the correct order.

Example 3:

Input: grid = [[1]]

Output: [[1]]

Explanation:

Diagonals with exactly one element are already in order, so no changes are needed.

 

Constraints:

grid.length == grid[i].length == n
1 <= n <= 10
-105 <= grid[i][j] <= 105
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    unordered_map<int, vector<int>> mp;
    
    //(i-j) -> diagonal elements
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int diag = i-j;
            mp[diag].push_back(grid[i][j]);       
        }
    }

    for(auto &itr : mp) {
        if(itr.first >= 0) { //Key
            sort(begin(itr.second), end(itr.second));
        }
        else {
            sort(rbegin(itr.second), rend(itr.second));
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int diag = i-j;
            grid[i][j] = mp[diag].back();
            mp[diag].pop_back();      
        }
    }
    return grid;
}

int main() {
    vector<vector<int>> grid = {{1,7,3},{9,8,2},{4,5,6}};
    vector<vector<int>> result = sortMatrix(grid);
    for(const auto& row : result) {
        for(int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}