/*
imum Difference Between Adjacent Elements in a Circular Array - [Leetcode - 3423(Easy)]
----------------------------------------------------------------------------------------
Given a circular array nums, find the maximum absolute difference between adjacent elements.

Note: In a circular array, the first and last elements are adjacent.

 

Example 1:

Input: nums = [1,2,4]

Output: 3

Explanation:

Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.

Example 2:

Input: nums = [-5,-10,-5]

Output: 5

Explanation:

The adjacent elements nums[0] and nums[1] have the maximum absolute difference of |-5 - (-10)| = 5.

 

Constraints:

2 <= nums.length <= 100
-100 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
using namespace std;

int maxAdjacentDistance(vector<int>& nums) {
    int n = nums.size();
    int maxDiff = 0;

    for (int i = 0; i < n; i++) {
        int nextIndex = (i + 1) % n; // Circular array
        int diff = abs(nums[i] - nums[nextIndex]);
        maxDiff = max(maxDiff, diff);
    }

    return maxDiff;
}

int main () {
    vector<int> nums = {1, 2, 4};
    cout << "Maximum absolute difference: " << maxAdjacentDistance(nums) << endl;

    nums = {-5, -10, -5};
    cout << "Maximum absolute difference: " << maxAdjacentDistance(nums) << endl;

    return 0;
}