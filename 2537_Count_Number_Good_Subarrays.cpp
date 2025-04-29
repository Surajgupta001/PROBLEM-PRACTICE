/*
Count the Number of Good Subarrays - [Leetcode - 2537(Medium)]
==============================================================
Given an integer array nums and an integer k, return the number of good subarrays of nums.

A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,1,1,1,1], k = 10
Output: 1
Explanation: The only good subarray is the array nums itself.
Example 2:

Input: nums = [3,1,4,3,2,2,4], k = 2
Output: 4
Explanation: There are 4 different good subarrays:
- [3,1,4,3,2,2] that has 2 pairs.
- [3,1,4,3,2,2,4] that has 3 pairs.
- [1,4,3,2,2,4] that has 2 pairs.
- [4,3,2,2,4] that has 2 pairs.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i], k <= 109
*/ 

#include <bits/stdc++.h>
using namespace std;

long long countGood(vector<int>& nums, int k) {
    int n = nums.size();
    int i = 0;
    int j = 0;

    long long result = 0;

    unordered_map<int, int> mp;

    long long pairs = 0;

    while (j < n) {
        pairs += mp[nums[j]]; // isse pehle kitni baar nums[j] dekha hai humne
        mp[nums[j]]++;

        while (pairs >= k) {
            result += (n - j);
            mp[nums[i]]--;
            pairs -= mp[nums[i]];
            i++;
        }

        j++;
    }

    return result;
}

int main(){
    
    vector<int> nums = {3,1,4,3,2,2,4};
    int k = 2;
    cout << countGood(nums, k) << endl; // Output: 4
    
    return 0;
}