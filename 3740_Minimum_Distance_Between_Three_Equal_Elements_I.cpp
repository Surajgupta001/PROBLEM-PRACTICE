/*
Minimum Distance Between Three Equal Elements I - [Leetcode - 3740(Easy)]
----------------------------------------------------------------------------

You are given an integer array nums.

A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.

 

Example 1:

Input: nums = [1,2,1,1,3]

Output: 6

Explanation:

The minimum distance is achieved by the good tuple (0, 2, 3).

(0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. Its distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

Example 2:

Input: nums = [1,1,2,3,2,1,2]

Output: 8

Explanation:

The minimum distance is achieved by the good tuple (2, 4, 6).

(2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. Its distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

Example 3:

Input: nums = [1]

Output: -1

Explanation:

There are no good tuples. Therefore, the answer is -1.

 

Constraints:

1 <= n == nums.length <= 100
1 <= nums[i] <= n
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// Brute Force Approach: O(n^3)
int minimumDistance(vector<int>& nums) {
    int n = nums.size();
    int result = INT_MAX;

    for (int i = 0; i < n - 2; i++){
        for (int j = i + 1; j < n - 1; j++){
            for (int k = j + 1; k < n; k++){
                if (nums[i] == nums[j] && nums[j] == nums[k]){
                    int distance = abs(i - j) + abs(j - k) + abs(k - i);
                    result = min(result, distance);
                }
            }
        }
    }
    return result == INT_MAX ? -1 : result;
}

// Brute Force Approach: O(n^3) - Slightly Optimized
int minimumDistance(vector<int>& nums) {
    int n = nums.size();
    int result = INT_MAX;

    for (int i = 0; i < n - 2; i++){
        for (int j = i + 1; j < n - 1; j++){
            for (int k = j + 1; k < n; k++){
                if (nums[i] == nums[j] && nums[j] == nums[k]){
                    int distance = 2 * (k - i);
                    result = min(result, distance);
                }
            }
        }
    }
    return result == INT_MAX ? -1 : result;
}

int main () {
    vector<int> nums1 = {1,2,1,1,3};
    cout << minimumDistance(nums1) << endl; // Output: 6

    vector<int> nums2 = {1,1,2,3,2,1,2};
    cout << minimumDistance(nums2) << endl; // Output: 8

    vector<int> nums3 = {1};
    cout << minimumDistance(nums3) << endl; // Output: -1

    return 0;
}