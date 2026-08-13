/*
1848. Minimum Distance to the Target Element - [Leetcode - 1848(Easy)]
----------------------------------------------------------------------------
Given an integer array nums (0-indexed) and two integers target and start, find an index i such that nums[i] == target and abs(i - start) is minimized. Note that abs(x) is the absolute value of x.

Return abs(i - start).

It is guaranteed that target exists in nums.

Example 1:

Input: nums = [1,2,3,4,5], target = 5, start = 3
Output: 1
Explanation: nums[4] = 5 is the only value equal to target, so the answer is abs(4 - 3) = 1.

Example 2:

Input: nums = [1], target = 1, start = 0
Output: 0
Explanation: nums[0] = 1 is the only value equal to target, so the answer is abs(0 - 0) = 0.

Example 3:

Input: nums = [1,1,1,1,1,1,1,1,1,1], target = 1, start = 0
Output: 0
Explanation: Every value of nums is 1, but nums[0] minimizes abs(i - start), which is abs(0 - 0) = 0. 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 104
0 <= start < nums.length
target is in nums.
*/

#include <iostream>
#include <vector>
using namespace std;

int getMinDistance(vector<int>& nums, int target, int start) {
    int n = nums.size();
    int minDistance = n; // Initialize with a large value
    
    for (int i = 0; i < n; ++i) {
        if (nums[i] == target) {
            minDistance = min(minDistance, abs(i - start));
        }
    }
    return minDistance;
}

int main() {
    vector<int> nums1 = {1, 2, 3, 4, 5};
    int target1 = 5;
    int start1 = 3;
    cout << "Output: " << getMinDistance(nums1, target1, start1) << endl; // Output: 1

    vector<int> nums2 = {1};
    int target2 = 1;
    int start2 = 0;
    cout << "Output: " << getMinDistance(nums2, target2, start2) << endl; // Output: 0

    vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int target3 = 1;
    int start3 = 0;
    cout << "Output: " << getMinDistance(nums3, target3, start3) << endl; // Output: 0

    return 0;
}