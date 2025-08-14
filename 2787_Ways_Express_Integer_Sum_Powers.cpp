/*
Ways to Express an Integer as Sum of Powers - [Leetcode - 2787(Medium)]
------------------------------------------------------------------------
Given two positive integers n and x.

Return the number of ways n can be expressed as the sum of the xth power of unique positive integers, in other words, the number of sets of unique integers [n1, n2, ..., nk] where n = n1x + n2x + ... + nkx.

Since the result can be very large, return it modulo 109 + 7.

For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53.

Example 1:

Input: n = 10, x = 2
Output: 1
Explanation: We can express n as the following: n = 32 + 12 = 10.
It can be shown that it is the only way to express 10 as the sum of the 2nd power of unique integers.

Example 2:

Input: n = 4, x = 1
Output: 2
Explanation: We can express n in the following ways:
- n = 41 = 4.
- n = 31 + 11 = 4.
 
Constraints:

1 <= n <= 300
1 <= x <= 5
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

// Approach: Memoization
int mod = 1e9 + 7;
int helper(int n, int num, int x, vector<vector<int>>& dp){
    if(n == 0) return 1; // Found a valid combination
    if(n < 0) return 0;
    if(pow(num, x) > n) return 0;

    if(dp[n][num] != -1) return dp[n][num];

    int take = helper(n - pow(num, x), num + 1, x, dp);
    int skip = helper(n, num + 1, x, dp);

    return dp[n][num] = (take + skip)% mod;
}

int numberOfWays(int n, int x) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return helper(n, 1, x, dp);
}

// Approach - 2: Tabulation
int numberOfWays(int n, int x) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1; // Base case

    for(int num = 1; num <= n; num++) {
        for(int sum = 0; sum <= n; sum++) {
            dp[sum][num] = dp[sum][num - 1]; // Skip current number
            if(sum - pow(num, x) >= 0) {
                dp[sum][num] = (dp[sum][num] + dp[sum - pow(num, x)][num - 1]) % mod;
            }
        }
    }

    return dp[n][n];
}

int main() {
    int n = 10, x = 2;
    cout << "Number of ways to express " << n << " as sum of unique integers to the power " << x << " is: " << numberOfWays(n, x) << endl;

    n = 4, x = 1;
    cout << "Number of ways to express " << n << " as sum of unique integers to the power " << x << " is: " << numberOfWays(n, x) << endl;

    return 0;
}