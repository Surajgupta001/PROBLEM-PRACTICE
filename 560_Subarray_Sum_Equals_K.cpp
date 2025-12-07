/*
Subarray Sum Equals K - [Leetcode - 560(Medium)]
--------------------------------------------------
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2

Example 2:

Input: nums = [1,2,3], k = 3
Output: 2
 
Constraints:

1 <= nums.length <= 2 * 10^4
-1000 <= nums[i] <= 1000
-107 <= k <= 10^7
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Brute Force
// O(n^2)
int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    int count = 0;

    for (int start = 0; start < n; start++) {
        int sum = 0;  // reset for each new start
        for (int end = start; end < n; end++) {
            sum += nums[end];  // accumulate directly
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}

// Optimized Approach using HashMap
// O(n)
int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> mp; //prefix sum and its frequency

    int result = 0;
    int cumSum = 0; // Prefix sum
    
    mp.insert({0, 1});

    for(int i=0; i<n; i++){
        cumSum += nums[i];

        if(mp.count(cumSum - k)){
            result += mp[cumSum - k];
        }
        mp[cumSum]++;
    }
    return result;
}

int main() {
    vector<int> nums = {1, 1, 1};
    int k = 2;
    cout << "Total subarrays with sum " << k << ": " << subarraySum(nums, k) << endl;
    return 0;
}