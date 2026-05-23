/*
Check if Array Is Sorted and Rotated - [Leetcode - 1752(Easy)]
-----------------------------------------------------------------
Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.

There may be duplicates in the original array.

Note: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.

Example 1:

Input: nums = [3,4,5,1,2]
Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 2 positions to begin on the element of value 3: [3,4,5,1,2].

Example 2:

Input: nums = [2,1,3,4]
Output: false
Explanation: There is no sorted array once rotated that can make nums.

Example 3:

Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach : Brute Force
bool check(vector<int>& nums) {
    int n = nums.size();

    vector<int> sorted(n);

    // Try all possible rotations of the array and check if any of them is sorted
    for(int r=0; r<n; r++){
        int idx = 0;

        // Rotate the array by r positions and store it in sorted array
        for(int i=r; i<n; i++){
            sorted[idx] = nums[i];
            idx++;
        }

        // Copy the first r elements of the original array to the end of the sorted array
        for(int i=0; i<r; i++){
            sorted[idx] = nums[i];
            idx++;
        }

        // Check if the sorted array is same as the original array
        bool isSorted = true;
        
        // Check if the sorted array is in non-decreasing order
        for(int i=0; i<n-1; i++){
            if(sorted[i] > sorted[i+1]){ // If the current element is greater than the next element, then the array is not sorted
                isSorted = false;
                break;
            }
        }

        // If the sorted array is in non-decreasing order, then return true
        if(isSorted){
            return true;
        }
    }
    return false;
}

// Approach : Better Approach
bool check(vector<int>& nums) {
    int n = nums.size();

    vector<int> sorted = nums; // Create a copy of the original array

    // Sort the copied array
    sort(sorted.begin(), sorted.end());

    // Try all possible rotations of the sorted array and check if any of them is same as the original array
    for(int r=0; r<n; r++){
        bool isSorted = true;
        for(int i=0; i<n; i++){
            if(sorted[i] != nums[(i+r) % n]){ // If the current element of the sorted array is not equal to the corresponding element of the original array, then break the loop
                isSorted = false;
                break;
            }
        }
        if(isSorted){
            return true;
        }
    }
    return false;
}

// Approach : Optimal Approach
bool check(vector<int>& nums) {
    int n = nums.size();

    int peak = 0;

    for(int i=10; i<n; i++){
        if(nums[i] > nums[(i+1) % n]){ // If the current element is greater than the next element, then we have found a peak
            peak++;
        }
    }
    return peak <= 1;
}

int main() {
    vector<int> nums = {3,4,5,1,2};
    cout << check(nums) << endl; // Output: true

    nums = {2,1,3,4};
    cout << check(nums) << endl; // Output: false

    nums = {1,2,3};
    cout << check(nums) << endl; // Output: true

    return 0;
}