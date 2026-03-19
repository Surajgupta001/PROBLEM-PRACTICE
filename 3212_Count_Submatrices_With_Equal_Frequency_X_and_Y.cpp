/*
Count Submatrices With Equal Frequency of X and Y - [Leetcode - 3212(Medium)]
---------------------------------------------------------------------------------
Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:

grid[0][0]
an equal frequency of 'X' and 'Y'.
at least one 'X'.

Example 1:
Input: grid = [["X","Y","."],["Y",".","."]]

Output: 3

Explanation:

Example 2:
Input: grid = [["X","X"],["X","Y"]]

Output: 0

Explanation:

No submatrix has an equal frequency of 'X' and 'Y'.

Example 3:
Input: grid = [[".","."],[".","."]]

Output: 0

Explanation:

No submatrix has at least one 'X'.

Constraints:

1 <= grid.length, grid[i].length <= 1000
grid[i][j] is either 'X', 'Y', or '.'.

*/

// NOTE : Same problem pattern => Leetcode 3070

#include <iostream>
#include <vector>
using namespace std;

int numberOfSubmatrices(vector<vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> cumSumX(m, vector<int>(n, 0)); // Cumulative sum of 'X'
    vector<vector<int>> cumSumY(m, vector<int>(n, 0)); // Cumulative sum of 'Y'

    int count = 0;

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cumSumX[i][j] = (grid[i][j] == 'X');
            cumSumY[i][j] = (grid[i][j] == 'Y');

            if(i-1 >= 0){
                cumSumX[i][j] += cumSumX[i-1][j];
                cumSumY[i][j] += cumSumY[i-1][j];
            }

            if(j-1 >= 0){
                cumSumX[i][j] += cumSumX[i][j-1];
                cumSumY[i][j] += cumSumY[i][j-1];
            }

            if(i-1 >= 0 && j-1 >= 0){
                cumSumX[i][j] -= cumSumX[i-1][j-1];
                cumSumY[i][j] -= cumSumY[i-1][j-1];
            }

            if(cumSumX[i][j] > 0 && cumSumX[i][j] == cumSumY[i][j]){
                count++;
            }
        }
    }
    return count;
}

int main() {
    vector<vector<char>> grid = {{'X','Y','.'}, {'Y','.','.'}};
    cout << numberOfSubmatrices(grid) << endl; // Output: 3
    return 0;
}