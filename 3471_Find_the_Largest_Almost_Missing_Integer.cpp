/*
Find the Largest Almost Missing Integer - [Leetcode - 3471(Easy)]
--------------------------------------------------------------------
You are given an integer array nums and an integer k.

An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.

Return the largest almost missing integer from nums. If no such integer exists, return -1.

A subarray is a contiguous sequence of elements within an array. 

Example 1:

Input: nums = [3,9,2,1,7], k = 3

Output: 7

Explanation:

1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
3 appears in 1 subarray of size 3: [3, 9, 2].
7 appears in 1 subarray of size 3: [2, 1, 7].
9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
We return 7 since it is the largest integer that appears in exactly one subarray of size k.

Example 2:

Input: nums = [3,9,7,2,1,7], k = 4

Output: 3

Explanation:

1 appears in 2 subarrays of size 4: [9, 7, 2, 1], [7, 2, 1, 7].
2 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
3 appears in 1 subarray of size 4: [3, 9, 7, 2].
7 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
9 appears in 2 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1].
We return 3 since it is the largest and only integer that appears in exactly one subarray of size k.

Example 3:

Input: nums = [0,0], k = 1

Output: -1

Explanation:

There is no integer that appears in only one subarray of size 1.

 

Constraints:

1 <= nums.length <= 50
0 <= nums[i] <= 50
1 <= k <= nums.length
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int largestInteger(vector<int>& nums, int k) {
    unordered_map<int, int> count;
    int n = nums.size();

    // Count occurrences of each integer in all subarrays of size k
    for (int i = 0; i <= n - k; i++) {
        unordered_map<int, int> subarrayCount;
        for (int j = i; j < i + k; j++) {
            subarrayCount[nums[j]]++;
        }
        for (const auto& pair : subarrayCount) {
            count[pair.first]++;
        }
    }

    // Find the largest integer that appears in exactly one subarray
    int result = -1;
    for (const auto& pair : count) {
        if (pair.second == 1) {
            result = max(result, pair.first);
        }
    }

    return result;
}

int main() {
    vector<int> nums1 = {3, 9, 2, 1, 7};
    int k1 = 3;
    cout << largestInteger(nums1, k1) << endl; // Output: 7

    vector<int> nums2 = {3, 9, 7, 2, 1, 7};
    int k2 = 4;
    cout << largestInteger(nums2, k2) << endl; // Output: 3

    vector<int> nums3 = {0, 0};
    int k3 = 1;
    cout << largestInteger(nums3, k3) << endl; // Output: -1

    return 0;
}