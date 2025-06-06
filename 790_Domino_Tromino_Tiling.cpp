/*
Domino and Tromino Tiling - [Leetcode - 790(Medium)]
----------------------------------------------------

You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate these shapes.


Given an integer n, return the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 109 + 7.

In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.

Example 1:

Input: n = 3
Output: 5
Explanation: The five different ways are show above.

Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 1000
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Memoization + Recursion --> DP

int mod = 1e9 + 7;

int helper(int n, vector<int>& dp){
    if(n == 1 or n == 2) return n;
    if(n == 3) return 5;

    if(dp[n] != -1) return dp[n];

    return dp[n] = (2*helper(n-1, dp) % mod + helper(n-3, dp) % mod) % mod;
}

int numTilings(int n){
    vector<int> dp(1001, -1);
    return helper(n, dp);
}

// Bottom Up DP
int mod = 1e9 + 7;
int numTilings(int n){
    if (n == 1 || n == 2) return n;

    vector<int> dp(n + 1, 0);

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 5;

    for (int i = 4; i <= n; i++){
        dp[i] = (2 * dp[i - 1] % mod + dp[i - 3] % mod) % mod;
    }
    return dp[n];
}

int main(){
    
    int n = 3;
    cout << numTilings(n) << endl; // Output: 5
    
    return 0;
}