/*
Sudoku Solver - [Leetcode - 37(Hard)]
---------------------------------------
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

Example 1:

Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
It is guaranteed that the input board has only one solution.
*/ 

#include <iostream>
#include <vector>
using namespace std;


bool isValidSudoku(vector<vector<char>>& board, int row, int col, char d) {
    for(int i = 0; i < 9; i++) {
        if(board[i][col] == d) return false;
        if(board[row][i] == d) return false;
    }

    int start_i = row/3 * 3;
    int start_j = col/3 * 3;
    
    for(int k = 0; k < 3; k++) {
        for(int l = 0; l < 3; l++) {
            if(board[start_i+k][start_j+l] == d) return false;
        }
    }
    return true;

}

//2^9
//O(9 ^ 81)
bool backTracking(vector<vector<char>>& board) {
    for(int i = 0; i < 9; i++) { //O(9)
        for(int j = 0; j < 9; j++) { //O(9)
            if(board[i][j] == '.') {
                for(char d = '1'; d <= '9'; d++) { 
                    if(isValidSudoku(board, i, j, d)) {
                        board[i][j] = d;
                        if(backTracking(board) == true) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void solveSudoku(vector<vector<char>>& board) {
    backTracking(board);
}

int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    solveSudoku(board);

    cout << "Solved Sudoku Board:" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != 8) cout << "| "; // Add vertical separators
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << "---------------------" << endl; // Add horizontal separators
        }
    }
    return 0;
}