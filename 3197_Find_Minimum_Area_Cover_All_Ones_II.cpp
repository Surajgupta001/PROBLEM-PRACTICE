/*
Find the Minimum Area to Cover All Ones II - [Leetcode - 3197(Hard)]
----------------------------------------------------------------------
You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.

Return the minimum possible sum of the area of these rectangles.

Note that the rectangles are allowed to touch.

Example 1:

Input: grid = [[1,0,1],[1,1,1]]

Output: 5

Explanation:

The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
The 1 at (1, 1) is covered by a rectangle of area 1.

Example 2:

Input: grid = [[1,0,1,0],[0,1,0,1]]

Output: 5

Explanation:

The 1's at (0, 0) and (0, 2) are covered by a rectangle of area 3.
The 1 at (1, 1) is covered by a rectangle of area 1.
The 1 at (1, 3) is covered by a rectangle of area 1.

Constraints:

1 <= grid.length, grid[i].length <= 30
grid[i][j] is either 0 or 1.
The input is generated such that there are at least three 1's in grid.
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<vector<int>> rotateClockWise(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> rotatedGrid(n, vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rotatedGrid[j][m - i - 1] = grid[i][j];
        }
    }

    return rotatedGrid;
}

int minimumArea(int startRow, int endRow, int startCol, int endCol, vector<vector<int>> &grid) {
    int m = grid.size();    // Rows
    int n = grid[0].size(); // Columns

    int minRow = m;
    int maxRow = -1;
    int minCol = n;
    int maxCol = -1;

    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            if (grid[i][j] == 1) {
                minRow = min(minRow, i);
                maxRow = max(maxRow, i);
                minCol = min(minCol, j);
                maxCol = max(maxCol, j);
            }
        }
    }
    return (maxRow - minRow + 1) * (maxCol - minCol + 1);
}

// O(m^2 * n^2)
int helper(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    int result = INT_MAX;

    for (int rowSplit = 1; rowSplit < m; rowSplit++) {
        for (int colSplit = 1; colSplit < n; colSplit++) {

            int top = minimumArea(0, rowSplit, 0, n, grid);
            int bottomLeft = minimumArea(rowSplit, m, 0, colSplit, grid);
            int bottomRight = minimumArea(rowSplit, m, colSplit, n, grid);

            result = min(result, top + bottomLeft + bottomRight);

            int topLeft = minimumArea(0, rowSplit, 0, colSplit, grid);
            int topRight = minimumArea(0, rowSplit, colSplit, n, grid);
            int bottom = minimumArea(rowSplit, m, 0, n, grid);

            result = min(result, topLeft + topRight + bottom);
        }
    }

    for (int split1 = 1; split1 < m; split1++) {
        for (int split2 = split1 + 1; split2 < m; split2++) {
            int top = minimumArea(0, split1, 0, n, grid);
            int middle = minimumArea(split1, split2, 0, n, grid);
            int bottom = minimumArea(split2, m, 0, n, grid);

            result = min(result, top + middle + bottom);
        }
    }
    return result;
}

int minimumSum(vector<vector<int>> &grid) {

    int result = helper(grid);

    vector<vector<int>> rotatedGrid = rotateClockWise(grid);

    result = min(result, helper(rotatedGrid));

    return result;
}

int main() {
    vector<vector<int>> grid = {{1, 0, 1}, {1, 1, 1}};

    int result = minimumSum(grid);
    cout << "Minimum sum of areas: " << result << endl;

    return 0;
}