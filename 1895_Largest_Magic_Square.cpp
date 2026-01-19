/*
Largest Magic Square - [Leetcode - 1895(Medium)]
---------------------------------------------------
A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.

Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found within this grid.

Example 1:


Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
Output: 3
Explanation: The largest magic square has a size of 3.
Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
- Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
- Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
- Diagonal sums: 5+4+3 = 6+4+2 = 12

Example 2:

Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
Output: 2
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j] <= 10^6
*/ 

#include <iostream>
#include <vector>
using namespace std;

int largestMagicSquare(vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();

    // Prefix Sum for Rows
    vector<vector<int>> rowPrefixSum(row, vector<int>(col + 1, 0));
    for(int i = 0; i < row; i++){
        rowPrefixSum[i][0] = grid[i][0]; // First column initialization
        for(int j = 1; j < col; j++){
            rowPrefixSum[i][j] = rowPrefixSum[i][j - 1] + grid[i][j];
        }
    }

    // Prefix Sum for Columns
    vector<vector<int>> colPrefixSum(col, vector<int>(row + 1, 0));
    for(int j = 0; j < col; j++){
        colPrefixSum[j][0] = grid[0][j]; // First row initialization
        for(int i = 1; i < row; i++){
            colPrefixSum[j][i] = colPrefixSum[j][i - 1] + grid[i][j];
        }
    }

    // Try all possible square sizes from each cell
    for(int side = min(row, col); side >= 2; side--){
        for(int i = 0; (i + side - 1) < row; i++){
            for(int j = 0; (j + side - 1) < col; j++){
                int targetSum = rowPrefixSum[i][j + side - 1] - (j > 0 ? rowPrefixSum[i][j - 1] : 0);

                bool isMagic = true;

                // Check all rows
                for(int r = i; r < i + side; r++){
                    int currentRowSum = rowPrefixSum[r][j + side - 1] - (j > 0 ? rowPrefixSum[r][j - 1] : 0);
                    if(currentRowSum != targetSum){
                        isMagic = false;
                        break;
                    }
                }
                if(!isMagic) continue;

                // Check all columns
                for(int c = j; c < j + side; c++){
                    int currentColSum = colPrefixSum[c][i + side - 1] - (i > 0 ? colPrefixSum[c][i - 1] : 0);
                    if(currentColSum != targetSum){
                        isMagic = false;
                        break;
                    }
                }
                if(!isMagic) continue;

                // Check main diagonal
                int mainDiagonalSum = 0;
                int antiDiagonalSum = 0;
                for(int k = 0; k < side; k++){
                    mainDiagonalSum += grid[i + k][j + k];
                    antiDiagonalSum += grid[i + k][j + side - 1 - k];
                }

                if(mainDiagonalSum != targetSum || antiDiagonalSum != targetSum){
                    isMagic = false;
                }
                if(isMagic) return side;
            }
        }
    }
    return 1; // Every 1x1 grid is a magic square
}

int main() {
    vector<vector<int>> grid1 = {
        {7, 1, 4, 5, 6},
        {2, 5, 1, 6, 4},
        {1, 5, 4, 3, 2},
        {1, 2, 7, 3, 4}
    };
    cout << "Largest Magic Square Size (Example 1): " << largestMagicSquare(grid1) << endl;

    vector<vector<int>> grid2 = {
        {5, 1, 3, 1},
        {9, 3, 3, 1},
        {1, 3, 3, 8}
    };
    cout << "Largest Magic Square Size (Example 2): " << largestMagicSquare(grid2) << endl;

    return 0;
}