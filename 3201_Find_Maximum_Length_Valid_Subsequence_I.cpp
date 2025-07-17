/*
Find the Maximum Length of Valid Subsequence I - [Leetcode - 3201(Medium)]
---------------------------------------------------------------------------
You are given an integer array nums.
A subsequence sub of nums with length x is called valid if it satisfies:

(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
Return the length of the longest valid subsequence of nums.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.



Example 1:

Input: nums = [1,2,3,4]

Output: 4

Explanation:

The longest valid subsequence is [1, 2, 3, 4].

Example 2:

Input: nums = [1,2,1,1,2,1,2]

Output: 6

Explanation:

The longest valid subsequence is [1, 2, 1, 2, 1, 2].

Example 3:

Input: nums = [1,3]

Output: 2

Explanation:

The longest valid subsequence is [1, 3].



Constraints:

2 <= nums.length <= 2 * 105
1 <= nums[i] <= 107
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach: 1 -> Without Recursion : (Count Even and Odd Numbers)
int maximumLength(vector<int> &nums){
    
    int countEven = 0;
    int countOdd = 0;
    
    for(int num : nums){
        if (num % 2 == 0) countEven++;
        else countOdd++;
    }

    // Try building alternating parity subsequence
    int altLen = 1; // At least one number
    int prevParity = nums[0] % 2;

    for(int i = 1; i < nums.size(); ++i){
        int currParity = nums[i] % 2;
        if(currParity != prevParity){
            altLen++;
            prevParity = currParity;
        }
    }

    return max({countEven, countOdd, altLen});
}

// Approach: 2 -> Using LIS Pattern (Recursion) - Memoization will give MLE due to high constraints
// T.C : Without Memoization O(2^n), With memoization - O(n^2) but MLE
// S.C : O(n^2)
int LIS(vector<int> &nums, int i, int prev, int mod){
    if (i >= nums.size()){
        return 0;
    }

    int take = 0;
    int skip = 0;

    // take
    if (prev == -1 || (nums[prev] + nums[i]) % 2 == mod){
        take = 1 + LIS(nums, i + 1, i, mod);
    }

    // skip
    skip = LIS(nums, i + 1, prev, mod);

    return max(take, skip);
}

// Approach: 3 -> Using LIS Pattern (Bottom Up) - TLE
// T.C : O(n^2) but TLE
// S.C : O(n)
int maximumLength(vector<int> &nums){
    // Using same LIS bottom up code

    int n = nums.size();

    // vector<int> dp1(n, 1); //mod1
    // vector<int> dp0(n, 1); //mod0
    //  dp0 {} //mod0
    //  dp1 {} //mod1
    //{
    //   {}, 0th row for mod0
    //  {}  1st row for mod1
    //}

    // row = 0 is for mod0
    // row = 1 is for mod1
    vector<vector<int>> dp(2, vector<int>(n, 1));
    int maxSub = 1;

    // mod = 1
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            int mod = (nums[j] + nums[i]) % 2;
            
            // mod = 0 = 0th row , %2 = 0 waale case ka result
            // mod = 1 = 1st row, %2 = 1 waale case ka result
            
            dp[mod][i] = max(dp[mod][i], 1 + dp[mod][j]);
            maxSub = max(maxSub, dp[mod][i]);
        }
    }

    return maxSub;
}

int maximumLength(vector<int>& nums) {
    
    int maxSubLength = 0;
    
    maxSubLength = max(maxSubLength, LIS(nums, 0, -1, 0)); //%2 == 0 k lie
    maxSubLength = max(maxSubLength, LIS(nums, 0, -1, 1)); //%2 == 1 k lie
    
    return maxSubLength;

}

int main(){
    
    vector<int> nums = {1, 2, 3, 4};
    cout << "Maximum Length of Valid Subsequence: " << maximumLength(nums) << endl;

    return 0;
}