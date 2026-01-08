/*
Given two arrays nums1 and nums2.

Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.

A subsequence of a array is a new array which is formed from the original array by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).

Example 1:

Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
Output: 18
Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
Their dot product is (2*3 + (-2)*(-6)) = 18.

Example 2:

Input: nums1 = [3,-2], nums2 = [2,-6,7]
Output: 21
Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
Their dot product is (3*7) = 21.

Example 3:

Input: nums1 = [-1,-1], nums2 = [1,1]
Output: -1
Explanation: Take subsequence [-1] from nums1 and subsequence [1] from nums2.
Their dot product is -1.

Constraints:

1 <= nums1.length, nums2.length <= 500
-1000 <= nums1[i], nums2[i] <= 1000
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach-1 (Using concept of LCS - same code)
// T.C : O(m*n)
// S.C : O(m*n)
int solve(vector<int> &nums1, vector<int> &nums2, int i, int j, vector<vector<int>> &dp) {
    int m = nums1.size();
    int n = nums2.size();
    
    if(i == m || j == n) return -1e9; // send a large negative number. Don't send 0 because we can have -ve product as well. For example : {-1, -1}, {1, 1}, output should be -1.
    
    if(dp[i][j] != -1e9) return dp[i][j];
    
    int val = nums1[i] * nums2[j];
    int take_i_j = solve(nums1, nums2, i + 1, j + 1, dp) + val;
    
    int take_i = solve(nums1, nums2, i, j + 1, dp);
    int take_j = solve(nums1, nums2, i + 1, j, dp);
    
    return dp[i][j] = max({val, take_i_j, take_i, take_j});
}

int maxDotProduct(vector<int> &nums1, vector<int> &nums2){
    int m = nums1.size();
    int n = nums2.size();
    vector<vector<int>> dp(501, vector<int>(501, -1e9));
    for (int i = 0; i < 501; i++){
        for (int j = 0; j < 501; j++){
            dp[i][j] = -1e9;
        }
    }
    return solve(nums1, nums2, 0, 0, dp);
}

// Approach-2 (Bottom Up same as LCS)
int maxDotProduct(vector<int> &nums1, vector<int> &nums2){
    int m = nums1.size();
    int n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1e9));
    
    for (int i = m - 1; i >= 0; i--){
        for (int j = n - 1; j >= 0; j--){
            int val = nums1[i] * nums2[j];
            int take_i_j = dp[i + 1][j + 1] + val;
            
            int take_i = dp[i][j + 1];
            int take_j = dp[i + 1][j];
            
            dp[i][j] = max({val, take_i_j, take_i, take_j});
        }
    }
    return dp[0][0];
}

int main () {
    vector<int> nums1 = {2, 1, -2, 5};
    vector<int> nums2 = {3, 0, -6};
    cout << maxDotProduct(nums1, nums2) << endl; // Output: 18
    return 0;
}