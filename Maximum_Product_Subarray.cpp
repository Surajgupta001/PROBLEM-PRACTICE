/*
Maximum Product Subarray - [leetcode - 152(Medium)]
=====================================================
Given an integer array nums, find a subarray that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxProduct(vector<int>& nums) {
    int maxProduct = nums[0];
    int minProduct = nums[0];
    int result = nums[0];

    for (int i=1;i<nums.size();i++) {
        if(nums[i] < 0) {
            swap(maxProduct, minProduct);
        }
        maxProduct = max(nums[i], maxProduct * nums[i]);
        minProduct = min(nums[i], minProduct * nums[i]);

        result = max(result, maxProduct);
    }

    return result;
}

int main() {
    vector<int> nums1 = {2, 3, -2, 4};
    cout << "Maximum product subarray: " << maxProduct(nums1) << endl;

    return 0;
}