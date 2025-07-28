/*
Kth Largest Element in an Array - [Leetcode - 215(Medium)]
-----------------------------------------------------------
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
*/ 

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Approaches: 1 => sorting : O(n log n)
int findKthLargest(vector<int>& nums, int k){
    sort(nums.begin(), nums.end(), greater<int>());
    return nums[k - 1];
}

// Approaches: 2 => using a min-heap : O(n log k)
int findKthLargest(vector<int>& nums, int k){
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for(auto &num : nums){
        minHeap.push(num);
        if(minHeap.size() > k){
            minHeap.pop();
        }
    }
    return minHeap.top();
}

// Approaches: 3 => using quickselect : O(n) on average

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    cout << "The " << k << "th largest element is: " << findKthLargest(nums, k) << endl;
    return 0;
}