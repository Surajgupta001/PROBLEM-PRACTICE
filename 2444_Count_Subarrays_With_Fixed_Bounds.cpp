/*
2444. Count Subarrays With Fixed Bounds - [Leetcode - 2444(Hard)]
=================================================================
You are given an integer array nums and two integers minK and maxK.

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:

The minimum value in the subarray is equal to minK.
The maximum value in the subarray is equal to maxK.
Return the number of fixed-bound subarrays.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
Output: 2
Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

Example 2:

Input: nums = [1,1,1,1], minK = 1, maxK = 1
Output: 10
Explanation: Every subarray of nums is a fixed-bound subarray. There are 10 possible subarrays.
 

Constraints:

2 <= nums.length <= 105
1 <= nums[i], minK, maxK <= 106

*/


#include <iostream>
#include <vector>
using namespace std;

// Brute Force - O(n^2) - TLE
long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    int n = nums.size();
    long long count = 0;

    for (int start = 0; start < n; ++start) {
        int currentMin = nums[start];
        int currentMax = nums[start];

        for (int end = start; end < n; ++end) {
            currentMin = min(currentMin, nums[end]);
            currentMax = max(currentMax, nums[end]);

            if (currentMin == minK && currentMax == maxK) {
                count++;
            }
        }
    }
    return count;
}


// Optimised Approch - O(n)
long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    long long ans = 0;
    
    int minPosition = -1;
    int maxPosition = -1;
    int leftBound   = -1;
    
    for(int i = 0; i < nums.size(); i++) {
        
        if(nums[i] < minK || nums[i] > maxK){
            leftBound = i;
        }
        
        if(nums[i] == minK){
            minPosition = i;
        }

        if(nums[i] == maxK){
            maxPosition = i;
        }
        
        int count = min(maxPosition, minPosition) - leftBound;
        
        ans += (count <= 0) ? 0 : count;
        
    }

    return ans;
}

int main(){
    
    vector<int> nums = {1, 3, 5, 2, 7, 5};

    int minK = 1, maxK = 5;

    long long result = countSubarrays(nums, minK, maxK);
    cout << result << endl; // Output: 2

    return 0;
}