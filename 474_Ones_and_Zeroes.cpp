/*
Ones and Zeroes - [Leetcode - 474(Medium)]
--------------------------------------------
You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.

Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.

Example 2:

Input: strs = ["10","0","1"], m = 1, n = 1

Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.
 
Constraints:

1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] consists only of digits '0' and '1'.
1 <= m, n <= 100
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int helper(vector<pair<int, int>>& count, int m, int n, int i, vector<vector<vector<int>>>& dp){
    if(i >= count.size() || (m == 0 && n == 0)) {
        return 0;
    }

    if(dp[i][m][n] != -1) {
        return dp[i][m][n];
    }

    int take = 0;
    if(count[i].first <= m && count[i].second <= n) {
        take = 1 + helper(count, m - count[i].first, n - count[i].second, i + 1, dp);
    }

    int skip = helper(count, m, n, i + 1, dp);

    return dp[i][m][n] = max(take, skip);
}
    

int findMaxForm(vector<string>& strs, int m, int n) {
    int N = strs.size();
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

    vector<pair<int, int>> count(N);
    for(int i=0; i<N; i++){
        int countZeros = 0;
        int countOnes = 0;

        for(auto ch : strs[i]){
            if(ch == '0') countZeros++;
            else countOnes++;
        }

        count[i] = {countZeros, countOnes};
    }

    return helper(count, m, n, 0, dp);
}

int main() {
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    cout << findMaxForm(strs, m, n) << endl; // Output: 4
    return 0;
}