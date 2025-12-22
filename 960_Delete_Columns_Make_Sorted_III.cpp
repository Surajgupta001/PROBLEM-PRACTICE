/*
Delete Columns to Make Sorted III - [Leetcode - 960(Hard)]
------------------------------------------------------------
You are given an array of n strings strs, all of the same length.

We may choose any deletion indices, and we delete all the characters in those indices for each string.

For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef", "vyz"].

Suppose we chose a set of deletion indices answer such that after deletions, the final array has every string (row) in lexicographic order. (i.e., (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]), and (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]), and so on). Return the minimum possible value of answer.length.

Example 1:

Input: strs = ["babca","bbazb"]
Output: 3
Explanation: After deleting columns 0, 1, and 4, the final array is strs = ["bc", "az"].
Both these rows are individually in lexicographic order (ie. strs[0][0] <= strs[0][1] and strs[1][0] <= strs[1][1]).
Note that strs[0] > strs[1] - the array strs is not necessarily in lexicographic order.

Example 2:

Input: strs = ["edcba"]
Output: 4
Explanation: If we delete less than 4 columns, the only row will not be lexicographically sorted.

Example 3:

Input: strs = ["ghi","def","abc"]
Output: 0
Explanation: All rows are already lexicographically sorted.
 
Constraints:

n == strs.length
1 <= n <= 100
1 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Simply Longest Increasing Subsequence (LIS) problem Variant
// Bottom-Up DP Approach
int minDeletionSize(vector<string>& strs) {
    int rows = strs.size();
    int cols = strs[0].size();

    vector<int> dp(cols, 1); // dp[i] will be the length of the longest valid sequence ending at column i

    // dp[i] = LIS ending at index i

    int LIS = 1; // Length of Longest Increasing Subsequence

    for(int i = 1; i < cols; ++i){
        for(int j = 0; j < i; ++j){
            bool safe = true;
            for(int k = 0; k < rows; ++k){
                if(strs[k][j] > strs[k][i]){
                    // that means not following lexicographical order
                    safe = false;
                    break;
                }
            }
            if(safe){
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        LIS = max(LIS, dp[i]);  
    }
    return cols - LIS; // Minimum deletions = Total columns - Length of Longest Increasing Subsequence
}

int main() {
    vector<string> strs1 = {"babca","bbazb"};
    cout << "Minimum deletions for strs1: " << minDeletionSize(strs1) << endl; // Output: 3

    vector<string> strs2 = {"edcba"};
    cout << "Minimum deletions for strs2: " << minDeletionSize(strs2) << endl; // Output: 4

    vector<string> strs3 = {"ghi","def","abc"};
    cout << "Minimum deletions for strs3: " << minDeletionSize(strs3) << endl; // Output: 0

    return 0;
}