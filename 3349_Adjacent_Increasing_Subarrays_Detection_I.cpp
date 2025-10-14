/*
Adjacent Increasing Subarrays Detection I - [Leetcode - 3349(Easy)]
--------------------------------------------------------------------
Given an array nums of n integers and an integer k, determine whether there exist two adjacent subarrays of length k such that both subarrays are strictly increasing. Specifically, check if there are two subarrays starting at indices a and b (a < b), where:

Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
The subarrays must be adjacent, meaning b = a + k.
Return true if it is possible to find two such subarrays, and false otherwise.

Example 1:

Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3

Output: true

Explanation:

The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
These two subarrays are adjacent, so the result is true.

Example 2:

Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5

Output: false

Constraints:

2 <= nums.length <= 100
1 < 2 * k <= nums.length
-1000 <= nums[i] <= 1000

*/ 

#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force
bool isIncreasing(vector<int>& nums, int start, int end) {
    for(int i = start; i < end - 1; i++) {
        if(nums[i] >= nums[i+1]) return false;
    }
    return true;
}

bool hasIncreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    for(int start = 0; start + 2 * k <= n; start++) {
        int first = isIncreasing(nums, start, start+k);
        int second = isIncreasing(nums, start+k, start+2*k);
        if(first && second) return true;
    }
    return false;
}

// Approach 2: Optimized
bool hasIncreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    
    int currRunLength = 1;
    int prevRunLength = 0;
    
    for(int i = 1; i < n; i++){
        if(nums[i] > nums[i-1]){
            currRunLength++;
        }
        else { // Increasing sequence broken
            prevRunLength = currRunLength;
            currRunLength = 1;
        }

        if(currRunLength >= 2*k){
            // We can accommodate two increasing subarrays of length k
            return true;
        }

        if(min(currRunLength, prevRunLength) >= k){
            return true;
        }
    }
    return false;
}

int main() {
    vector<int> nums = {2,5,7,8,9,2,3,4,3,1};
    int k = 3;
    cout << (hasIncreasingSubarrays(nums, k) ? "true" : "false") << endl; // Output: true
    return 0;
}