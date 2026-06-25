/*
Number of ZigZag Arrays I - [Leetcode - 3699(Hard)]
------------------------------------------------------
You are given three integers n, l, and r.

A ZigZag array of length n is defined as follows:

Each element lies in the range [l, r].
No two adjacent elements are equal.
No three consecutive elements form a strictly increasing or strictly decreasing sequence.
Return the total number of valid ZigZag arrays.

Since the answer may be large, return it modulo 109 + 7.

A sequence is said to be strictly increasing if each element is strictly greater than its previous one (if exists).

A sequence is said to be strictly decreasing if each element is strictly smaller than its previous one (if exists).

Example 1:

Input: n = 3, l = 4, r = 5

Output: 2

Explanation:

There are only 2 valid ZigZag arrays of length n = 3 using values in the range [4, 5]:

[4, 5, 4]
[5, 4, 5]​​​​​​​
Example 2:

Input: n = 3, l = 1, r = 3

Output: 10

Explanation:

There are 10 valid ZigZag arrays of length n = 3 using values in the range [1, 3]:

[1, 2, 1], [1, 3, 1], [1, 3, 2]
[2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
[3, 1, 2], [3, 1, 3], [3, 2, 3]
All arrays meet the ZigZag conditions.

Constraints:

3 <= n <= 2000
1 <= l < r <= 2000
*/

#include <iostream>
#include <vector>
using namespace std;

#define ll long long
int mod = 1e9 + 7;

// Approach: DP + Recursion + Memoization
int helper(int i, int prevVal, bool isIncreasing, int N, int M, vector<vector<vector<int>>>& dp) {

    if(i == N) return 1; // We reached till end of zigzap array and completed 1 zigzag array

    if(dp[i][prevVal][isIncreasing] != -1) return dp[i][prevVal][isIncreasing];

    ll result = 0;

    if(isIncreasing){ // Increasing sequence
        for(int nextVal=prevVal+1; nextVal<=M; nextVal++){
            result = result + helper(i+1, nextVal, false, N, M, dp) % mod;
        }
    } else { // Decreasing sequence
        for(int nextVal=1; nextVal<prevVal; nextVal++){
            result = result + helper(i+1, nextVal, true, N, M, dp) % mod;
        }
    }

    return dp[i][prevVal][isIncreasing] = result % mod;
}


int zigZagArrays(int n, int l, int r) {
    int N = n;
    int M = r - l + 1; // no. of element in given range [l, r]

    vector<vector<vector<int>>> dp(N, vector<vector<int>>(M+1, vector<int>(2, -1))); // O(N*M*2) => (2000 * 2000 * 2000 => 8 * 10^9) -> TLE
    
    ll result = 0;

    for(int startVal=1; startVal<=M; startVal++){
        // i = 0; -> put startVal at index 0

        // Increasing sequence
        result = (result + helper(1, startVal, true, N, M, dp)) % mod;
        
        // Decreasing sequence
        result = (result + helper(1, startVal, false, N, M, dp)) % mod;
    }

    return result;
}

// Approach: DP + Tabulation
int zigZagArrays(int n, int l, int r) {
    int N = n;
    int M = r - l + 1;

    vector<vector<vector<int>>> dp(N + 1,vector<vector<int>>(M + 1, vector<int>(2, 0))); // O(N*M*2) => (2000 * 2000 * 2000 => 8 * 10^9) -> TLE

    ll result = 0;

    // Base Case
    for(int prevVal = 1; prevVal <= M; prevVal++){
        dp[N][prevVal][0] = 1;
        dp[N][prevVal][1] = 1;
    }

    for(int i = N - 1; i >= 1; i--){
        for(int prevVal = 1; prevVal <= M; prevVal++){
            // Increasing
            for(int nextVal = prevVal + 1; nextVal <= M; nextVal++){
                dp[i][prevVal][1] = (dp[i][prevVal][1] + dp[i + 1][nextVal][0]) % mod;
            }

            // Decreasing
            for(int nextVal = 1; nextVal < prevVal; nextVal++) {
                dp[i][prevVal][0] = (dp[i][prevVal][0] + dp[i + 1][nextVal][1]) % mod;
            }
        }
    }

    for(int startVal = 1; startVal <= M; startVal++){
        result = (result + dp[1][startVal][1]) % mod;
        result = (result + dp[1][startVal][0]) % mod;
    }

    return result;
}

// Approach: Prefix Sum + DP + Tabulation => Optimal Solution
int zigZagArrays(int n, int l, int r) {
    int N = n;
    int M = r - l + 1;

    vector<vector<int>> next(M + 1, vector<int>(2, 1));
    vector<vector<int>> curr(M + 1, vector<int>(2, 0));

    ll result = 0;

    for(int i = N - 1; i >= 1; i--) {

        vector<int> prefixSumIncreasing(M + 1, 0);
        vector<int> prefixSumDecreasing(M + 1, 0);

        for(int prevVal = 1; prevVal <= M; prevVal++) {
            prefixSumIncreasing[prevVal] = (prefixSumIncreasing[prevVal - 1] + next[prevVal][0]) % mod;

            prefixSumDecreasing[prevVal] = (prefixSumDecreasing[prevVal - 1] + next[prevVal][1]) % mod;
        }

        for(int prevVal = 1; prevVal <= M; prevVal++) {

            // Increasing
            curr[prevVal][1] = (prefixSumIncreasing[M] - prefixSumIncreasing[prevVal] + mod) % mod;

            // Decreasing
            curr[prevVal][0] = prefixSumDecreasing[prevVal - 1];
        }

        swap(curr, next);
    }

    for(int startVal = 1; startVal <= M; startVal++) {
        result = (result + next[startVal][1]) % mod;
        result = (result + next[startVal][0]) % mod;
    }

    return result;
}

int main() {
    int n = 3, l = 1, r = 3;
    cout << zigZagArrays(n, l, r) << endl; // Output: 10
    return 0;
}