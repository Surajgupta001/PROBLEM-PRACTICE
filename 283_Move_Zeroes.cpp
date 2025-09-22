/*
Move Zeroes - [Leetcode - 283(Easy)]
-------------------------------------
Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you minimize the total number of operations done?
*/ 

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Brute Force Approach - Using Extra Array - O(N) time and O(N) space
void moveZeroes(vector<int>& nums) {
    int n = nums.size();
    vector<int> temp(n, 0); // Temporary array initialized with zeros
    int index = 0; // Pointer for the position to place non-zero elements

    // First pass: Copy all non-zero elements to the temporary array
    for(int i = 0; i < n; i++) {
        if(nums[i] != 0) {
            temp[index] = nums[i];
            index++;
        }
    }

    // Copy the temporary array back to the original array
    for(int i = 0; i < n; i++) {
        nums[i] = temp[i];
    }        
}

// Optimal Approach - Two Pointer Approach - O(N) time and O(1) space
void moveZeroes(vector<int>& nums) {
    int n = nums.size();
    int nonZeroIndex = 0; // Pointer to place the next non-zero element

    // First pass: Move all non-zero elements to the front
    for(int i = 0; i < n; i++) {
        if(nums[i] != 0) {
            nums[nonZeroIndex] = nums[i];
            nonZeroIndex++;
        }
    }

    // Second pass: Fill the remaining positions with zeros
    for(int i = nonZeroIndex; i < n; i++) {
        nums[i] = 0;
    }        
}

// Using STL functions - O(N) time and O(1) space
void moveZeroes(vector<int>& nums) {
    auto itr = remove(nums.begin(), nums.end(), 0);
    fill(itr, nums.end(), 0);
}

int main() {
    vector<int> nums = {0, 1, 0, 3, 12};
    moveZeroes(nums);
    
    cout << "After moving zeroes: ";
    for(int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}