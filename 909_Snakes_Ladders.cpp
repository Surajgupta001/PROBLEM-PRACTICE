/*
Snakes and Ladders - [Leetcode - 909(Medium)]
----------------------------------------------
You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and alternating direction each row.

You start on square 1 of the board. In each move, starting from square curr, do the following:

Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
This choice simulates the result of a standard 6-sided die roll: i.e., there are always at most 6 destinations, regardless of the size of the board.
If next has a snake or ladder, you must move to the destination of that snake or ladder. Otherwise, you move to next.
The game ends when you reach the square n2.
A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination of that snake or ladder is board[r][c]. Squares 1 and n2 are not the starting points of any snake or ladder.

Note that you only take a snake or ladder at most once per dice roll. If the destination to a snake or ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.

For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is 2. You follow the ladder to square 3, but do not follow the subsequent ladder to 4.
Return the least number of dice rolls required to reach the square n2. If it is not possible to reach the square, return -1.

Example 1:

Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
Output: 4
Explanation:
In the beginning, you start at square 1 (at row 5, column 0).
You decide to move to square 2 and must take the ladder to square 15.
You then decide to move to square 17 and must take the snake to square 13.
You then decide to move to square 14 and must take the ladder to square 35.
You then decide to move to square 36, ending the game.
This is the lowest possible number of moves to reach the last square, so return 4.

Example 2:

Input: board = [[-1,-1],[-1,3]]
Output: 1


Constraints:

n == board.length == board[i].length
2 <= n <= 20
board[i][j] is either -1 or in the range [1, n2].
The squares labeled 1 and n2 are not the starting points of any snake or ladder.

/* In the context of the given problem, the term "Boustrophedon style" refers to the way in which the
cells of the board are labeled. In a Boustrophedon style, the labeling starts from the bottom left
corner of the board and alternates direction each row. This means that the labeling progresses from
left to right in the first row, then right to left in the second row, and so on, creating a zigzag
pattern.

Boustrophedon style => The Boustrophedon style is a method of labeling the cells in a grid or matrix
in a zigzag pattern, starting from one corner and alternating the direction of labeling with each
row. In the context of the Snakes and Ladders game, this means that the cells are labeled from
1 to n2 in a way that reflects this zigzag pattern, making it necessary to carefully track the
position of each cell as the game progresses.

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

pair<int, int> getCoordinates(int value, int n) {
    int rowFromTop = (value - 1) / n; // Calculate the row index from the top
    int rowFromBottom = n - 1 - rowFromTop; // Convert to row index from the bottom

    int col = (value - 1) % n; // Calculate the column index
    if(n%2 == 1 && rowFromBottom%2 == 1 || n%2 == 0 && rowFromBottom%2 == 0) {
        col = n - 1 - col; // Adjust column index for zigzag pattern
    }

    return make_pair(rowFromBottom, col); // Return the coordinates as a pair
}

int snakesAndLadders(vector<vector<int>>& board) {
    int n = board.size();
    
    int steps = 0;
    queue<int> qu;

    vector<vector<bool>> visited(n, vector<bool>(n, false));
    visited[n - 1][0] = true; // Start at the bottom-left corner

    qu.push(1); // Start from square 1
    while(!qu.empty()) {
        int N = qu.size();

        while(N--){
            int currElement = qu.front();
            qu.pop();

            if(currElement == n * n) return steps; // Reached the last square

            for(int k = 1; k <= 6; k++) {
                int value = currElement + k; // Calculate the next square based on dice roll
                if(value > n * n) break; // No need to go beyond the last square

                pair<int, int> coordinates = getCoordinates(value, n);
                
                int row = coordinates.first;
                int col = coordinates.second;

                if(visited[row][col] == true) continue; // Already visited this square

                visited[row][col] = true; // Mark this square as visited

                if(board[row][col] == -1){
                    qu.push(value); // No snake or ladder, push the square value
                }
                else {
                    qu.push(board[row][col]); // There is a snake or ladder, push its destination
                }
            }
        }
        steps++; // Increment the number of steps after processing all current squares
    }
    return -1; // If we exit the loop without reaching the last square, return -1
}

int main(){
    vector<vector<int>> board = {
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 35, -1, -1, 13, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 15, -1, -1, -1, -1}};

    cout << "Minimum number of dice rolls required: " << snakesAndLadders(board) << endl;

    return 0;
}