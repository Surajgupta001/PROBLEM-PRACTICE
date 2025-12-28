/*
Count Negative Numbers in a Sorted Matrix - [Leetcode - 1351(Easy)]
---------------------------------------------------------------------
Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise, return the number of negative numbers in grid.

Example 1:

Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.
Example 2:

Input: grid = [[3,2],[1,0]]
Output: 0
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100
-100 <= grid[i][j] <= 100

*/ 

#include <iostream>
#include <vector>
using namespace std;

int countNegatives(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    int count = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] < 0) {
                count += (n - j); //All elements after jth index will also be negative
                break;
            }
        }
    }

    return count;
}

int main() {
    vector<vector<int>> grid = {
        {4,3,2,-1},
        {3,2,1,-1},
        {1,1,-1,-2},
        {-1,-1,-2,-3}
    };

    cout << "Number of negative numbers in the matrix: " << countNegatives(grid) << endl;

    return 0;
}