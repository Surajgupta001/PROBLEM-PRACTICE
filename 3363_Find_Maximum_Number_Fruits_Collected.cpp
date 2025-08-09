/*
Find the Maximum Number of Fruits Collected -[Leetcode -3363(HARD)]
--------------------------------------------------------------------
There is a game dungeon comprised of n x n rooms arranged in a grid.

You are given a 2D array fruits of size n x n, where fruits[i][j] represents the number of fruits in the room (i, j). Three children will play in the game dungeon, with initial positions at the corner rooms (0, 0), (0, n - 1), and (n - 1, 0).

The children will make exactly n - 1 moves according to the following rules to reach the room (n - 1, n - 1):

The child starting from (0, 0) must move from their current room (i, j) to one of the rooms (i + 1, j + 1), (i + 1, j), and (i, j + 1) if the target room exists.
The child starting from (0, n - 1) must move from their current room (i, j) to one of the rooms (i + 1, j - 1), (i + 1, j), and (i + 1, j + 1) if the target room exists.
The child starting from (n - 1, 0) must move from their current room (i, j) to one of the rooms (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the target room exists.
When a child enters a room, they will collect all the fruits there. If two or more children enter the same room, only one child will collect the fruits, and the room will be emptied after they leave.

Return the maximum number of fruits the children can collect from the dungeon.

Example 1:

Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]

Output: 100

Explanation:

In this example:

The 1st child (green) moves on the path (0,0) -> (1,1) -> (2,2) -> (3, 3).
The 2nd child (red) moves on the path (0,3) -> (1,2) -> (2,3) -> (3, 3).
The 3rd child (blue) moves on the path (3,0) -> (3,1) -> (3,2) -> (3, 3).
In total they collect 1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100 fruits.

Example 2:

Input: fruits = [[1,1],[1,1]]

Output: 4

Explanation:

In this example:

The 1st child moves on the path (0,0) -> (1,1).
The 2nd child moves on the path (0,1) -> (1,1).
The 3rd child moves on the path (1,0) -> (1,1).
In total they collect 1 + 1 + 1 + 1 = 4 fruits.

Constraints:

2 <= n == fruits.length == fruits[i].length <= 1000
0 <= fruits[i][j] <= 1000

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// =================== Memoization ========================
// Can only move diagonally
int child1Collect(vector<vector<int>> &fruits, vector<vector<int>> &dp){
    int n = fruits.size();
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += fruits[i][i];
        fruits[i][i] = 0;
        dp[i][i] = 0;
    }
    return ans;
}

int child2Collect(int i, int j, vector<vector<int>> &fruits, vector<vector<int>> &dp){
    int n = fruits.size();

    if(i < 0 || i >= n || j < 0 || j >= n) return 0;

    if(i == n - 1 && j == n - 1) return 0;

    // can't go beyond diagonal or left to diagonal (only have n-1 moves)
    if(i == j || i > j) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    int leftcorner = fruits[i][j] + child2Collect(i + 1, j - 1, fruits, dp);
    int middle = fruits[i][j] + child2Collect(i + 1, j, fruits, dp);
    int rightcorner = fruits[i][j] + child2Collect(i + 1, j + 1, fruits, dp);

    return dp[i][j] = max({middle, rightcorner, leftcorner});
}

int child3Collect(int i, int j, vector<vector<int>> &fruits, vector<vector<int>> &dp){
    int n = fruits.size();

    if(i < 0 || i >= n || j < 0 || j >= n) return 0;
    if(i == n - 1 && j == n - 1) return 0;

    // can't go beyond diagonal or right to diagonal (only have n-1 moves)
    if(i == j || j > i) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    int topcorner = fruits[i][j] + child3Collect(i - 1, j + 1, fruits, dp);
    int right = fruits[i][j] + child3Collect(i, j + 1, fruits, dp);
    int rightcorner = fruits[i][j] + child3Collect(i + 1, j + 1, fruits, dp);

    return dp[i][j] = max({right, rightcorner, topcorner});
}

int maxCollectedFruits(vector<vector<int>> &fruits){
    int n = fruits.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    // First child
    int firstChildScore = child1Collect(fruits, dp);

    // Second child
    int secondChildScore = child2Collect(0, n - 1, fruits, dp);

    // Third child
    int thirdChildScore = child3Collect(n - 1, 0, fruits, dp);

    return (firstChildScore + secondChildScore + thirdChildScore);
}

// =================== Tabulation ========================
int maxCollectedFruits(vector<vector<int>> &fruits){
    int n = fruits.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    // dp[i][j] = max fruits collected till [i][j] from source

    // child1Collect - Diagonal elements
    int result = 0;
    for(int i = 0; i < n; i++){
        result += fruits[i][i];
    }

    // Before child2 and child3, nullify the cells which can'dp be visited by child2 and child3
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i < j && i + j < n - 1){
                dp[i][j] = 0;
            }
            else if (i > j && i + j < n - 1){
                dp[i][j] = 0;
            }
            else{
                dp[i][j] = fruits[i][j];
            }
        }
    }

    // child2 collect fruits
    // cells upper to diagonal : i < j
    for(int i = 1; i < n; i++){
        for(int j = i + 1; j < n; j++){
            dp[i][j] += max({dp[i - 1][j - 1], dp[i - 1][j], (j + 1 < n) ? dp[i - 1][j + 1] : 0});
        }
    }

    // child3 collect fruits
    // cells upper to diagonal : i > j
    for(int j = 1; j < n; j++){
        for(int i = j + 1; i < n; i++){
            dp[i][j] += max({dp[i - 1][j - 1], dp[i][j - 1], (i + 1 < n) ? dp[i + 1][j - 1] : 0});
        }
    }

    return result + dp[n-2][n-1] + dp[n-1][n-2];
}

int main(){
    vector<vector<int>> fruits = {
        {1, 2, 3, 4},
        {5, 6, 8, 7},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    int result = maxCollectedFruits(fruits);
    cout << "Maximum fruits collected: " << result << endl;

    return 0;
}