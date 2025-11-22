/*
Find Minimum Operations to Make All Elements Divisible by Three - [Leetcode - 3190(Easy)]
-------------------------------------------------------------------------------------------
You are given an integer array nums. In one operation, you can add or subtract 1 from any element of nums.

Return the minimum number of operations to make all elements of nums divisible by 3.

Example 1:

Input: nums = [1,2,3,4]

Output: 3

Explanation:

All array elements can be made divisible by 3 using 3 operations:

Subtract 1 from 1.
Add 1 to 2.
Subtract 1 from 4.

Example 2:

Input: nums = [3,6,9]

Output: 0

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 50
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minimumOperations(vector<int>& nums) {
    int operations = 0;
    
    for(auto &num : nums){
        // Goal: Make every number divisible by 3
        // For any number, num % 3 gives its remainder when divided by 3:
        // 
        // 0 -> Already divisible by 3, no operation needed
        // 1 -> Subtract 1 to make it divisible by 3 (1 operation)
        // 2 -> Add 1 to make it divisible by 3 (1 operation)
        if(num % 3 != 0){
            operations++;
        }
    }
    return operations;
}

// Approach: STL
int minimumOperations(vector<int>& nums) {
    // count how many numbers are not divisible by 3
    return count_if(nums.begin(), nums.end(), [](int num) {
        return num % 3 != 0;
    });
}

int main () {
    vector<int> nums1 = {1, 2, 3, 4};
    cout << "Minimum operations for nums1: " << minimumOperations(nums1) << endl; // Output: 3

    vector<int> nums2 = {3, 6, 9};
    cout << "Minimum operations for nums2: " << minimumOperations(nums2) << endl; // Output: 0

    return 0;
}