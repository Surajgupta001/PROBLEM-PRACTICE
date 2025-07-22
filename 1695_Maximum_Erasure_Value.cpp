/*
Maximum Erasure Value - [Leetcode - 1695(Medium)]
---------------------------------------------------
You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.

Return the maximum score you can get by erasing exactly one subarray.

An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

Example 1:

Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].

Example 2:

Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Standard Sliding Window Technique
int maximumUniqueSubarray(vector<int>& nums) {
    int n = nums.size();

    unordered_set<int> sets;
    int i = 0;
    int j = 0;
    int currSum = 0;
    int result = 0;

    while(j < n){ // Traverse through the array with two pointers
        if(!sets.count(nums[j])){ // If the current element is not in the set, we can add it
            sets.insert(nums[j]); // Add the current element to the set
            currSum += nums[j]; // Add the current element to the current sum
            result = max(result, currSum);
            j++; // Move the right pointer forward
        }
        else { // If we encounter a duplicate, we need to shrink the window from the left
            while(i < n && sets.count(nums[j])){ // Shrink the window until the duplicate is removed
                sets.erase(nums[i]); // Remove the leftmost element from the set
                currSum -= nums[i]; // Remove the leftmost element from the current sum
                i++; // Move the left pointer forward
            }
        }
    }

    return result;
}

// Slightly Optimized Sliding Window Technique
// We have to store index of elements. We have seen in the past
// that using a map to store the last seen index of each element and jump the (idx + 1) 
int maximumUniqueSubarray(vector<int>& nums){
    int n = nums.size();
    
    vector<int> cumSum(n, 0);
    cumSum[0] = nums[0];
    for(int i = 1; i < n; i++){
        cumSum[i] = cumSum[i - 1] + nums[i];
    }

    vector<int> lastSeen(10001, -1); // Since nums[i] <= 10^4
    int result = 0;
    int i = 0;
    int j = 0;

    while(j < n){
        i = max(i, lastSeen[nums[j]] + 1); // jumping i so that i to j is valid
        
        int jthSum = cumSum[j];
        int ithSum = (i > 0) ? cumSum[i - 1] : 0; // If i is 0, we take 0 as the sum before the first element

        result = max(result, jthSum - ithSum); // Calculate the maximum sum of the subarray from i to j

        lastSeen[nums[j]] = j; // Update the last seen index of nums[j]
        j++; // Move the right pointer forward
    }
    
    return result;
}

int main () {
    vector<int> nums1 = {4, 2, 4, 5, 6};
    cout << "Maximum Erasure Value for nums1: " << maximumUniqueSubarray(nums1) << endl; // Output: 17

    vector<int> nums2 = {5, 2, 1, 2, 5, 2, 1, 2, 5};
    cout << "Maximum Erasure Value for nums2: " << maximumUniqueSubarray(nums2) << endl; // Output: 8

    return 0;
}