/*
Minimum Distance Between Three Equal Elements II - [Leetcode - 3741(Medium)]
------------------------------------------------------------------------------
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

1 <= n == nums.length <= 10^5
1 <= nums[i] <= n
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

int minimumDistance(vector<int>& nums) {
    int n = nums.size();
    
    unordered_map<int, vector<int>> maps; // Number -> List of indices where the number appears

    int result = INT_MAX; // Distance of the closest good tuple

    for (int k = 0; k < n; k++){
        maps[nums[k]].push_back(k);

        if(maps[nums[k]].size() >= 3){
            // i, j, k
            // 2*(k-i)
            vector<int> &indices = maps[nums[k]];
            int size = indices.size();
            
            int i = indices[size-3]; // {,,,,,i, j, k}

            result = min(result, 2*(k-i));
        }
    }
    return result == INT_MAX ? -1 : result;
}

int main() {
    vector<int> nums1 = {1,2,1,1,3};
    cout << minimumDistance(nums1) << endl; // Output: 6

    vector<int> nums2 = {1,1,2,3,2,1,2};
    cout << minimumDistance(nums2) << endl; // Output: 8

    vector<int> nums3 = {1};
    cout << minimumDistance(nums3) << endl; // Output: -1

    return 0;
}