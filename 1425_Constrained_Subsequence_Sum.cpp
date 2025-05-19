/*
1425. Constrained Subsequence Sum - [Leetcode - 1425(Hard)]
------------------------------------------------------------
Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
Example 1:

Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].
Example 2:

Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.
Example 3:

Input: nums = [10,-2,-10,-5,20], k = 2
Output: 23
Explanation: The subsequence is [10, -2, -5, 20].
 

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104

Similar Problem => 239. Sliding Window Maximum
Also U can solve Priority Queue approach using max heap
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

int constrainedSubsetSum(vector<int>& nums, int k) {
    vector<int> dp(nums.size());
    deque<int> dq; // to store indices of dp in decreasing order

    int result = nums[0];

    for(int i=0; i < nums.size(); i++){
        // dp[i] is nums[i] + max(0, dp[dq.front()])
        dp[i] = nums[i];

        if(not dq.empty()){
            dp[i] = max(dp[i], nums[i] + dp[dq.front()]);
        }

        // Maintain deque : remove indices that are out of the window
        if(not dq.empty() && dq.front() <= i - k){
            dq.pop_front();
        }

        // Maintain deque : remove indices whose dp values are less than current dp[i]
        while(not dq.empty() && dp[dq.back()] < dp[i]){
            dq.pop_back();
        }

        // Add current index to the deque
        dq.push_back(i);
        
        // Update result
        result = max(result, dp[i]);
    }

    return result;
}

int main() {
    vector<int> nums = {10, 2, -10, 5, 20};
    int k = 2;
    cout << constrainedSubsetSum(nums, k) << endl; // Output: 37
    return 0;
}