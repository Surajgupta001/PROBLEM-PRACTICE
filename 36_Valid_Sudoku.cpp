/*
Valid Sudoku - [Leetcode - 36(Medium)]
----------------------------------------
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example 1:

Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
Example 2:

Input: board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
 
Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool isValidSubBox(vector<vector<char>>& board, int startRow, int endRow, int startCol, int endCol) {
    unordered_set<char> set;
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            char curr = board[i][j];
            if (curr != '.' && set.count(curr)) return false;
            set.insert(curr);
        }
    }
    return true;
}

// Approach 1: Brute Force
bool isValidSudoku(vector<vector<char>>& board) {
    // Step 1: Validate Rows
    for(int row=0; row<9; row++){
        unordered_set<char> set;
        for(int col=0; col<9; col++){
            if(board[row][col] == '.') continue;
            if(set.count(board[row][col])) return false;
            set.insert(board[row][col]);
        }
    }

    // Step 2: Validate Columns
    for(int col=0; col<9; col++){
        unordered_set<char> set;
        for(int row=0; row<9; row++){
            if(board[row][col] == '.') continue;
            if(set.count(board[row][col])) return false;
            set.insert(board[row][col]);
        }
    }

    // Step 3: Validate 3x3 Sub-boxes
    for(int startRow = 0; startRow<9; startRow+=3){
        int endRow = startRow + 2;
        for(int startCol = 0; startCol<9; startCol+=3){
            int endCol = startCol + 2;
            // startRow, EndRow, StartCol, EndCol
            if(!isValidSubBox(board, startRow, endRow, startCol, endCol)) return false;
        }
    }

    return true;
}

// Approach 2: Optimized
bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<string> set;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j] == '.') continue;
            string row = string(1, board[i][j]) + "_row" + to_string(i);
            string col = string(1, board[i][j]) + "_col" + to_string(j);
            string box = string(1, board[i][j]) + "_box" + to_string(i/3) + to_string(j/3);
            if(set.count(row) || set.count(col) || set.count(box)) return false;
            set.insert(row);
            set.insert(col);
            set.insert(box);
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    cout << boolalpha << isValidSudoku(board) << endl;

    return 0;
}