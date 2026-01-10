/*
Minimum ASCII Delete Sum for Two Strings - [Leetcode - 712(Medium)]
---------------------------------------------------------------------
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
 
Constraints:

1 <= s1.length, s2.length <= 1000
s1 and s2 consist of lowercase English letters.

*/

#include <iostream>
#include <vector>
using namespace std;

int helper(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
    int m = s1.length();
    int n = s2.length();
    
    if(i >= m && j >= n) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    if(i >= m){
        return dp[i][j] = s2[j] + helper(i, j + 1, s1, s2, dp);
    } else if(j >= n){
        return dp[i][j] = s1[i] + helper(i + 1, j, s1, s2, dp);
    }

    if(s1[i] == s2[j]){
        return dp[i][j] = helper(i + 1, j + 1, s1, s2, dp);    
    }

    // Two Possibilities
    int delete_s1_iTh = s1[i] + helper(i + 1, j, s1, s2, dp);
    int delete_s2_jTh = s2[j] + helper(i, j + 1, s1, s2, dp);

    return dp[i][j] = min(delete_s1_iTh, delete_s2_jTh);
}

int minimumDeleteSum(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

    return helper(0, 0, s1, s2, dp);
}

// Bottom up DP Approach

int main() {
    string s1 = "sea";
    string s2 = "eat";

    cout << "Minimum ASCII Delete Sum for Two Strings: " << minimumDeleteSum(s1, s2) << endl;

    return 0;
}