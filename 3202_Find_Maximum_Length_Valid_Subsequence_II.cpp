/*
Find the Maximum Length of Valid Subsequence II - [Leetcode - 3202(Medium)]
-----------------------------------------------------------------------------
You are given an integer array nums and a positive integer k.
A subsequence sub of nums with length x is called valid if it satisfies:

(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
Return the length of the longest valid subsequence of nums.


Example 1:

Input: nums = [1,2,3,4,5], k = 2

Output: 5

Explanation:

The longest valid subsequence is [1, 2, 3, 4, 5].

Example 2:

Input: nums = [1,4,2,3,1,4], k = 3

Output: 4

Explanation:

The longest valid subsequence is [1, 4, 1, 4].



Constraints:

2 <= nums.length <= 103
1 <= nums[i] <= 107
1 <= k <= 103
*/

#include <iostream>
#include <vector>
using namespace std;

int maximumLength(vector<int> &nums, int k){
    // Using same LIS bottom up code

    int n = nums.size();

    // vector<int> dp1(n, 1); //mod1
    // vector<int> dp0(n, 1); //mod0

    //  dp0 {} //mod0
    //  dp1 {} //mod1

    // {
    //   {}, 0th row for mod0
    //  {}  1st row for mod1
    // }

    // row = 0 is for mod0
    // row = 1 is for mod1
    // row = 2 is for mod2
    //....
    // row = k-1 is for mod k-1
    vector<vector<int>> dp(k, vector<int>(n, 1));
    int maxSub = 1;

    // mod = 1
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            int mod = (nums[j] + nums[i]) % k;
            
            // mod = 0 = 0th row , %2 = 0 waale case ka result
            // mod = 1 = 1st row, %2 = 1 waale case ka result
            
            dp[mod][i] = max(dp[mod][i], 1 + dp[mod][j]);
            maxSub = max(maxSub, dp[mod][i]);
        }
    }

    return maxSub;
}

int main(){
    
    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 2;
    
    cout << "Maximum Length of Valid Subsequence: " << maximumLength(nums, k) << endl;

    vector<int> nums2 = {1, 4, 2, 3, 1, 4};
    int k2 = 3;

    cout << "Maximum Length of Valid Subsequence: " << maximumLength(nums2, k2) << endl;

    return 0;
}