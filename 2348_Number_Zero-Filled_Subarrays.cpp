/*
Number of Zero-Filled Subarrays - [Leetcode - 2348(Medium)]
------------------------------------------------------------
Given an integer array nums, return the number of subarrays filled with 0.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,3,0,0,2,0,0,4]
Output: 6
Explanation: 
There are 4 occurrences of [0] as a subarray.
There are 2 occurrences of [0,0] as a subarray.
There is no occurrence of a subarray with a size more than 2 filled with 0. Therefore, we return 6.

Example 2:

Input: nums = [0,0,0,2,0,0]
Output: 9
Explanation:
There are 5 occurrences of [0] as a subarray.
There are 3 occurrences of [0,0] as a subarray.
There is 1 occurrence of [0,0,0] as a subarray.
There is no occurrence of a subarray with a size more than 3 filled with 0. Therefore, we return 9.

Example 3:

Input: nums = [2,10,2019]
Output: 0
Explanation: There is no subarray filled with 0. Therefore, we return 0.
 

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Approach : 1 - Using very simple math to find subarrays count.
long long zeroFilledSubarray(vector<int>& nums) {
    long long result = 0;
    int n = nums.size();
    int i = 0;

    while(i < n){
        long long length = 0;
        if(nums[i] == 0){
            while(i < n && nums[i] == 0){
                length++;
                i++;
            }
            result += (length * (length + 1)) / 2; // For a contiguous subarray of k zeros, the number of subarrays is (k * (k + 1)) / 2
        } else {
            i++;
        }
    }
    return result;
}

// Approach : 2 - Using prefix sum to find subarrays count.
long long zeroFilledSubarray(vector<int>& nums){
    // 0 -> 1
    // 00 -> 2 + 1 = 3
    // 000 -> 3 + 3 = 6
    // 0002 -> 6
    // 00020 -> 6 + 1 = 7
    
    long long result = 0;
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            count++;
            result += count;
        } else {
            count = 0;
        }
    }
    return result;
}

// Approach : 3 - Recursion
long long helper(vector<int>& nums, int index, vector<long long>& dp){
    if(index >= nums.size()) return 0;
    if(dp[index] != -1) return dp[index];

    if(nums[index] == 0){
        long long count = 1;
        while (index + 1 < nums.size() && nums[index + 1] == 0){
            count++;
            index++;
        }
        dp[index] = (count * (count + 1)) / 2 + helper(nums, index + 1, dp);
    }
    else{
        dp[index] = helper(nums, index + 1, dp);
    }
    return dp[index];
}

long long zeroFilledSubarray(vector<int>& nums){
    vector<long long> dp(nums.size(), -1);
    return helper(nums, 0, dp);
}

int main() {
    vector<int> nums = {1, 3, 0, 0, 2, 0, 0, 4};
    cout << zeroFilledSubarray(nums) << endl;

    nums = {0, 0, 0, 2, 0, 0};
    cout << zeroFilledSubarray(nums) << endl;

    nums = {2, 10, 2019};
    cout << zeroFilledSubarray(nums) << endl;

    return 0;
}