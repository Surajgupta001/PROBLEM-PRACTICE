/*
Largest Perimeter Triangle - [Leetcode - 976(Easy)]
-----------------------------------------------------
Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.

Example 1:

Input: nums = [2,1,2]
Output: 5
Explanation: You can form a triangle with three side lengths: 1, 2, and 2.

Example 2:

Input: nums = [1,2,1,10]
Output: 0
Explanation: 
You cannot use the side lengths 1, 1, and 2 to form a triangle.
You cannot use the side lengths 1, 1, and 10 to form a triangle.
You cannot use the side lengths 1, 2, and 10 to form a triangle.
As we cannot use any three side lengths to form a triangle of non-zero area, we return 0.
 

Constraints:

3 <= nums.length <= 104
1 <= nums[i] <= 106

*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int largestPerimeter(vector<int>& nums) {
    sort(nums.begin(), nums.end(), greater<int>()); // Sort in descending order
    for (int i = 0; i < nums.size() - 2; ++i) {
        if (nums[i] < nums[i + 1] + nums[i + 2]) {
            return nums[i] + nums[i + 1] + nums[i + 2]; // Return the perimeter
        }
    }
    return 0; // If no valid triangle is found
}

int main() {
    vector<int> nums1 = {2, 1, 2};
    vector<int> nums2 = {1, 2, 1, 10};

    cout << "Largest Perimeter of Triangle in nums1: " << largestPerimeter(nums1) << endl; // Output: 5
    cout << "Largest Perimeter of Triangle in nums2: " << largestPerimeter(nums2) << endl; // Output: 0

    return 0;
}