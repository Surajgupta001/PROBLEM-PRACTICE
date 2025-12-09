/*
Count Special Triplets - [Leetcode - 3583(Medium)]
---------------------------------------------------
You are given an integer array nums.

A special triplet is defined as a triplet of indices (i, j, k) such that:

0 <= i < j < k < n, where n = nums.length
nums[i] == nums[j] * 2
nums[k] == nums[j] * 2
Return the total number of special triplets in the array.

Since the answer may be large, return it modulo 109 + 7.

Example 1:

Input: nums = [6,3,6]

Output: 1

Explanation:

The only special triplet is (i, j, k) = (0, 1, 2), where:

nums[0] = 6, nums[1] = 3, nums[2] = 6
nums[0] = nums[1] * 2 = 3 * 2 = 6
nums[2] = nums[1] * 2 = 3 * 2 = 6
Example 2:

Input: nums = [0,1,0,0]

Output: 1

Explanation:

The only special triplet is (i, j, k) = (0, 2, 3), where:

nums[0] = 0, nums[2] = 0, nums[3] = 0
nums[0] = nums[2] * 2 = 0 * 2 = 0
nums[3] = nums[2] * 2 = 0 * 2 = 0
Example 3:

Input: nums = [8,4,2,8,4]

Output: 2

Explanation:

There are exactly two special triplets:

(i, j, k) = (0, 1, 3)
nums[0] = 8, nums[1] = 4, nums[3] = 8
nums[0] = nums[1] * 2 = 4 * 2 = 8
nums[3] = nums[1] * 2 = 4 * 2 = 8
(i, j, k) = (1, 2, 4)
nums[1] = 4, nums[2] = 2, nums[4] = 4
nums[1] = nums[2] * 2 = 2 * 2 = 4
nums[4] = nums[2] * 2 = 2 * 2 = 4
 

Constraints:

3 <= n == nums.length <= 105
0 <= nums[i] <= 105
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int mod = 1e9 + 7;
int specialTriplets(vector<int>& nums) {
    unordered_map<int, int> leftMap;
    unordered_map<int, int> rightMap;

    int result = 0;

    for(auto &num : nums){
        rightMap[num]++;
    }

    for(auto &num : nums){
        rightMap[num]--;

        int left = leftMap[num * 2];
        int right = rightMap[num * 2];

        result = (result + (long long)left * right) % mod;

        leftMap[num]++;
    }

    return result;
}

// One pass
int specialTriplets(vector<int>& nums){
    unordered_map<int, int> valid_i;
    unordered_map<int, int> valid_j;

    int result = 0;

    for(auto &num : nums){
        if(num % 2 == 0){ // if is's valid k, we got our triplets
            result = (result + valid_j[num / 2]) % mod;
        }

        // If it's valid j or not
        valid_j[num] = (valid_j[num] + valid_i[num * 2]) % mod;

        // If it's valid i
        valid_i[num]++;
    }
    return result;
}

int main () {
    vector<int> nums = {8, 4, 2, 8, 4};
    cout << specialTriplets(nums) << endl; // Output: 2
    return 0;
}