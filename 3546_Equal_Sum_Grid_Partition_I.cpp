/*
Equal Sum Grid Partition I - [Leetcode - 3546(Medium)]
---------------------------------------------------------
You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:

Each of the two resulting sections formed by the cut is non-empty.
The sum of the elements in both sections is equal.
Return true if such a partition exists; otherwise return false.

Example 1:

Input: grid = [[1,4],[2,3]]

Output: true

Explanation:

A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.

Example 2:

Input: grid = [[1,3],[2,4]]

Output: false

Explanation:

No horizontal or vertical cut results in two non-empty sections with equal sums. Thus, the answer is false.

Constraints:

1 <= m == grid.length <= 10^5
1 <= n == grid[i].length <= 10^5
2 <= m * n <= 10^5
1 <= grid[i][j] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canPartitionGrid(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<long long> rowSums(m, 0);
    vector<long long> colSums(n, 0);

    long long totalSum = 0;

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            totalSum += grid[i][j];

            // Row = i
            rowSums[i] += grid[i][j];

            // Col = j
            colSums[j] += grid[i][j];
        }
    }

    if(totalSum % 2 != 0) return false;

    // Horizontal Split
    long long upperSum = 0;
    for(int i=0; i<m-1; i++){
        upperSum += rowSums[i];
        if(upperSum == totalSum - upperSum){
            return true;
        }
    }

    // Vertical Split
    long long leftSum = 0;
    for(int j=0; j<n-1; j++){
        leftSum += colSums[j];
        if(leftSum == totalSum - leftSum){
            return true;
        }
    }

    return false;
}

int main () {
    vector<vector<int>> grid1 = {{1,4}, {2,3}};
    vector<vector<int>> grid2 = {{1,3}, {2,4}};

    cout << boolalpha; // Print bool values as true/false
    cout << "Grid 1 can be partitioned: " << canPartitionGrid(grid1) << endl;
    cout << "Grid 2 can be partitioned: " << canPartitionGrid(grid2) << endl;

    return 0;
}