/*
Find Greatest Common Divisor of Array - [Leetcode - 1979(Easy)]
--------------------------------------------------------------------
Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.

The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

Example 1:

Input: nums = [2,5,6,9,10]
Output: 2
Explanation:
The smallest number in nums is 2.
The largest number in nums is 10.
The greatest common divisor of 2 and 10 is 2.

Example 2:

Input: nums = [7,5,6,8,3]
Output: 1
Explanation:
The smallest number in nums is 3.
The largest number in nums is 8.
The greatest common divisor of 3 and 8 is 1.

Example 3:

Input: nums = [3,3]
Output: 3
Explanation:
The smallest number in nums is 3.
The largest number in nums is 3.
The greatest common divisor of 3 and 3 is 3.

Constraints:

2 <= nums.length <= 1000
1 <= nums[i] <= 1000
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findGCD(vector<int>& nums) {
    int minNum = *min_element(nums.begin(), nums.end());
    int maxNum = *max_element(nums.begin(), nums.end());

    return __gcd(minNum, maxNum);
}

int main() {
    vector<int> nums1 = {2, 5, 6, 9, 10};
    cout << "GCD of nums1: " << findGCD(nums1) << endl; // Output: 2

    vector<int> nums2 = {7, 5, 6, 8, 3};
    cout << "GCD of nums2: " << findGCD(nums2) << endl; // Output: 1

    vector<int> nums3 = {3, 3};
    cout << "GCD of nums3: " << findGCD(nums3) << endl; // Output: 3

    return 0;
}