/*
Maximum Difference Between Increasing Elements - [Leetcode - 2016(Easy)]
-------------------------------------------------------------------------
Given a 0-indexed integer array nums of size n, find the maximum difference between nums[i] and nums[j] (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].

Return the maximum difference. If no such i and j exists, return -1.

 

Example 1:

Input: nums = [7,1,5,4]
Output: 4
Explanation:
The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 - 1 = 4.
Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1 = 6, but i > j, so it is not valid.

Example 2:

Input: nums = [9,4,3,2]
Output: -1
Explanation:
There is no i and j such that i < j and nums[i] < nums[j].

Example 3:

Input: nums = [1,5,2,10]
Output: 9
Explanation:
The maximum difference occurs with i = 0 and j = 3, nums[j] - nums[i] = 10 - 1 = 9.
 

Constraints:

n == nums.length
2 <= n <= 1000
1 <= nums[i] <= 109
*/ 

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Brute Force
int maximumDifference(vector<int>& nums) {
    int maxDiff = -1;
    for(int i=0; i<nums.size(); i++){
        for(int j=i+1; j<nums.size(); j++){
            if(nums[j] > nums[i]){
                maxDiff = max(maxDiff, nums[j] - nums[i]);
            }
        }
    }
    return maxDiff;
}

// Optimal Approach
int maximumDifferenceOptimal(vector<int>& nums) {
    int minElement = nums[0]; // nums[i];
    int maxDiff = -1;
    
    for(int j=1; j<nums.size(); j++){
        if(nums[j] > minElement){
            maxDiff = max(maxDiff, nums[j] - minElement);
        }
        else{
            minElement = nums[j];
        }
    }
    return maxDiff;
}

int main () {
    vector<int> nums1 = {7, 1, 5, 4};
    vector<int> nums2 = {9, 4, 3, 2};
    vector<int> nums3 = {1, 5, 2, 10};

    cout << "Maximum Difference in nums1: " << maximumDifference(nums1) << endl; // Output: 4
    cout << "Maximum Difference in nums2: " << maximumDifference(nums2) << endl; // Output: -1
    cout << "Maximum Difference in nums3: " << maximumDifference(nums3) << endl; // Output: 9

    return 0;
}