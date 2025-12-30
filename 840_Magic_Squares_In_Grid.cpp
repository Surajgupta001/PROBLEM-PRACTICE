/*
Magic Squares In Grid - [Leetcode - 840(Medium)]
----------------------------------------------------
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.

Given a row x col grid of integers, how many 3 x 3 magic square subgrids are there?

Note: while a magic square can only contain numbers from 1 to 9, grid may contain numbers up to 15.

Example 1:

Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
Output: 1
Explanation: 
The following subgrid is a 3 x 3 magic square:

while this one is not:

In total, there is only one magic square inside the given grid.

Example 2:

Input: grid = [[8]]
Output: 0
 
Constraints:

row == grid.length
col == grid[i].length
1 <= row, col <= 10
0 <= grid[i][j] <= 15
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool isMagicGrid(vector<vector<int>>& grid, int r, int c) {
    unordered_set<int> set;
    // 3x3 grid Element should be from 1 to 9 with no duplicate
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            int num = grid[r+i][c+j];
            if(num < 1 || num > 9 || set.count(num)){
                return false;
            } else {
                set.insert(num);
            }
        }
    }

    // Check Rows sum, Columns sum, Diagonals sum, Anti-Diagonals sum should be equal
    int rowSum = grid[r][c] + grid[r][c+1] + grid[r][c+2];

    for(int i=0; i<3; i++){
        if(grid[r+i][c] + grid[r+i][c+1] + grid[r+i][c+2] != rowSum){ // Row Sum
            return false;
        }
        if(grid[r][c+i] + grid[r+1][c+i] + grid[r+2][c+i] != rowSum){ // Column Sum
            return false;
        }
    }

    // Diagonal Sum
    if(grid[r][c] + grid[r+1][c+1] + grid[r+2][c+2] != rowSum){
        return false;
    }

    // Anti-Diagonal Sum
    if(grid[r][c+2] + grid[r+1][c+1] + grid[r+2][c] != rowSum){
        return false;
    }

    return true;
}

int numMagicSquaresInside(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    int count = 0;
    
    // Limits of 3x3 magic square
    for(int i=0; i<=rows-3; i++){
        for(int j=0; j<=cols-3; j++){
            if(isMagicGrid(grid, i, j)){
                count++;
            }
        }
    }
    return count;
}

int main() {
    vector<vector<int>> grid = {
        {4,3,8,4},
        {9,5,1,9},
        {2,7,6,2}
    };

    cout << "Number of Magic Squares in Grid: " << numMagicSquaresInside(grid) << endl;

    return 0;
}