/*
Minimum Absolute Difference in Sliding Submatrix - [Leetcode - 3567(Medium)]
--------------------------------------------------------------------------------

You are given an m x n integer matrix grid and an integer k.

For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.

Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.

Note: If all elements in the submatrix have the same value, the answer will be 0.

A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.

Example 1:

Input: grid = [[1,8],[3,-2]], k = 2

Output: [[2]]

Explanation:

There is only one possible k x k submatrix: [[1, 8], [3, -2]].
Distinct values in the submatrix are [1, 8, 3, -2].
The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
Example 2:

Input: grid = [[3,-1]], k = 1

Output: [[0,0]]

Explanation:

Both k x k submatrix has only one distinct element.
Thus, the answer is [[0, 0]].
Example 3:

Input: grid = [[1,-2,3],[2,3,5]], k = 2

Output: [[1,2]]

Explanation:

There are two possible k × k submatrix:
Starting at (0, 0): [[1, -2], [2, 3]].
Distinct values in the submatrix are [1, -2, 2, 3].
The minimum absolute difference in the submatrix is |1 - 2| = 1.
Starting at (0, 1): [[-2, 3], [3, 5]].
Distinct values in the submatrix are [-2, 3, 5].
The minimum absolute difference in the submatrix is |3 - 5| = 2.
Thus, the answer is [[1, 2]].
 

Constraints:

1 <= m == grid.length <= 30
1 <= n == grid[i].length <= 30
-10^5 <= grid[i][j] <= 10^5
1 <= k <= min(m, n)
*/

#include <iostream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> result(m-k+1, vector<int>(n-k+1));

    for(int i=0; i<m-k+1; i++){
        for(int j=0; j<n-k+1; j++){
            set<int> value;
            for(int x=i; x<=i+k-1; x++){
                for(int y=j; y<=j+k-1; y++){
                    // process grid[x][y]
                    value.insert(grid[x][y]);
                }
            }
            
            if(value.size() == 1){
                result[i][j] = 0;
                continue;
            }

            int minAbsDiff = INT_MAX;
            auto prevPointer = value.begin();
            auto currPointer = next(prevPointer);

            while(currPointer != value.end()){
                minAbsDiff = min(minAbsDiff, abs(*currPointer - *prevPointer));
                prevPointer = currPointer;
                currPointer++;
            }
            result[i][j] = minAbsDiff;
        }
    }
    return result;
}

int main() {
    vector<vector<int>> grid = {{1, -2, 3}, {2, 3, 5}};
    int k = 2;

    vector<vector<int>> result = minAbsDiff(grid, k);

    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}