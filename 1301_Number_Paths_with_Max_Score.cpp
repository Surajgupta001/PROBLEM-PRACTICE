/*
Number of Paths with Max Score - [Leetcode - 1301(Hard)]
-------------------------------------------------------------
You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.

You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

In case there is no path, return [0, 0].

Example 1:

Input: board = ["E23","2X2","12S"]
Output: [7,1]

Example 2:

Input: board = ["E12","1X1","21S"]
Output: [4,2]

Example 3:

Input: board = ["E11","XXX","11S"]
Output: [0,0]
 

Constraints:

2 <= board.length == board[i].length <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mod = 1e9 + 7;

int getIntFromChar(char ch) {
    return ch != 'S' ? ch - '0' : 0;
}

bool isValid(int i, int j, vector<string>& board) {
    int n = board.size();
    
    return (i >= 0 && i < n && j >= 0 && j < n && board[i][j] != 'X');
}

// Recursion + memoization
pair<int, int> helper(int i, int j, vector<string>& board, vector<vector<pair<int, int>>>& dp) {
    int n = board.size();

    if(board[i][j] == 'E'){
        return {0, 1};
    }

    if(board[i][j] == 'X'){
        return {0, 0};
    }

    if(dp[i][j] != make_pair(-1, -1)){
        return dp[i][j];
    }

    int upScore = 0, upPath = 0;
    int leftScore = 0, leftPath = 0;
    int diagScore = 0, diagPath = 0;

    char ch = board[i][j];

    // UP
    if(isValid(i-1, j, board)){
        pair<int, int> result = helper(i-1, j, board, dp);
        upScore = result.first;
        upPath = result.second;

        if(upPath > 0){
            upScore += getIntFromChar(ch);
        }
    }

    // LEFT
    if(isValid(i, j-1, board)){
        pair<int, int> result = helper(i, j-1, board, dp);
        leftScore = result.first;
        leftPath = result.second;

        if(leftPath > 0){
            leftScore += getIntFromChar(ch);
        }
    }

    // DIAGONAL
    if(isValid(i-1, j-1, board)){
        pair<int, int> result = helper(i-1, j-1, board, dp);
        diagScore = result.first;
        diagPath = result.second;

        if(diagPath > 0){
            diagScore += getIntFromChar(ch);
        }
    }

    // Now Find the the best from all of them
    int bestScore, bestPath;
    
    if(upScore == leftScore && leftScore == diagScore){
        bestScore = upScore;
        bestPath = upPath + leftPath + diagPath;
    } else if(upScore == leftScore){
        bestScore = upScore;
        bestPath = upPath + leftPath;
        if(diagScore > bestScore || (diagScore == bestScore && diagPath > bestPath)){
            bestScore = diagScore;
            bestPath = diagPath;
        }
    } else if(leftScore == diagScore){
        bestScore = leftScore;
        bestPath = leftPath + diagPath;
        if(upScore > bestScore || (upScore == bestScore && upPath > bestPath)){
            bestScore = upScore;
            bestPath = upPath;
        }
    } else if(upScore == diagScore){
        bestScore = upScore;
        bestPath = upPath + diagPath;
        if(leftScore > bestScore || (leftScore == bestScore && leftPath > bestPath)){
            bestScore = leftScore;
            bestPath = leftPath;
        }
    } else {
        if(upScore > leftScore && upScore > diagScore){
            bestScore = upScore;
            bestPath = upPath;
        } else if(leftScore > diagScore){
            bestScore = leftScore;
            bestPath = leftPath;
        } else {
            bestScore = diagScore;
            bestPath = diagPath;
        }
    }

    return dp[i][j] = {bestScore, bestPath % mod};
}

vector<int> pathsWithMaxScore(vector<string>& board) {
    int n = board.size();
    
    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {-1, -1}));
    pair<int, int> result = helper(n-1, n-1, board, dp);

    return {result.first, result.second};
}

// Tabulation
vector<int> pathsWithMaxScore(vector<string>& board) {
    int n = board.size();

    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {0, 0}));

    dp[0][0] = {0, 1};

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(board[i][j] == 'E' || board[i][j] == 'X') continue;
            
            int upScore = 0, upPath = 0;
            int leftScore = 0, leftPath = 0;
            int diagScore = 0, diagPath = 0;

            char ch = board[i][j];

            if(isValid(i-1, j, board)){
                pair<int, int> result = dp[i-1][j];
                upScore = result.first;
                upPath = result.second;

                if(upPath > 0){
                    upScore += getIntFromChar(ch);
                }
            }

            if(isValid(i, j-1, board)){
                pair<int, int> result = dp[i][j-1];
                leftScore = result.first;
                leftPath = result.second;

                if(leftPath > 0){
                    leftScore += getIntFromChar(ch);
                }
            }

            if(isValid(i-1, j-1, board)){
                pair<int, int> result = dp[i-1][j-1];
                diagScore = result.first;
                diagPath = result.second;

                if(diagPath > 0){
                    diagScore += getIntFromChar(ch);
                }
            }

            int bestScore, bestPath;

            if(upScore == leftScore && leftScore == diagScore){
                bestScore = upScore;
                bestPath = upPath + leftPath + diagPath;
            } else if(upScore == leftScore){
                bestScore = upScore;
                bestPath = upPath + leftPath;
                if(diagScore > bestScore || (diagScore == bestScore && diagPath > bestPath)){
                    bestScore = diagScore;
                    bestPath = diagPath;
                }
            } else if(leftScore == diagScore){
                bestScore = leftScore;
                bestPath = leftPath + diagPath;
                if(upScore > bestScore || (upScore == bestScore && upPath > bestPath)){
                    bestScore = upScore;
                    bestPath = upPath;
                }
            } else if(upScore == diagScore){
                bestScore = upScore;
                bestPath = upPath + diagPath;
                if(leftScore > bestScore || (leftScore == bestScore && leftPath > bestPath)){
                    bestScore = leftScore;
                    bestPath = leftPath;
                }
            } else {
                if(upScore > leftScore && upScore > diagScore){
                    bestScore = upScore;
                    bestPath = upPath;
                } else if(leftScore > diagScore){
                    bestScore = leftScore;
                    bestPath = leftPath;
                } else {
                    bestScore = diagScore;
                    bestPath = diagPath;
                }
            }
            dp[i][j] = {bestScore, bestPath % mod};
        }
    }

    auto result = dp[n-1][n-1];
    return {result.first, result.second};
}

int main(){
    vector<string> board = {"E23","2X2","12S"};
    vector<int> result = pathsWithMaxScore(board);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;
    return 0;
}