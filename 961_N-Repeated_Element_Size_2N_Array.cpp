/*
N-Repeated Element in Size 2N Array - [Leetcode - 961(Easy)]
---------------------------------------------------------------
You are given an integer array nums with the following properties:

nums.length == 2 * n.
nums contains n + 1 unique elements.
Exactly one element of nums is repeated n times.
Return the element that is repeated n times.

Example 1:

Input: nums = [1,2,3,3]
Output: 3

Example 2:

Input: nums = [2,1,2,5,3,2]
Output: 2

Example 3:

Input: nums = [5,1,5,2,5,3,5,4]
Output: 5
 
Constraints:

2 <= n <= 5000
nums.length == 2 * n
0 <= nums[i] <= 10^4
nums contains n + 1 unique elements and one of them is repeated exactly n times.
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int repeatedNTimes(vector<int>& nums) {
    unordered_set<int> sets;
    for(auto &num : nums){
        if(sets.count(num)){
            return num; // Found the repeated element
        } else {
            sets.insert(num);
        }
    }
    return -1; // This line should never be reached given the problem constraints
}

int main () {
    vector<int> nums1 = {1, 2, 3, 3};
    cout << "Repeated element in nums1: " << repeatedNTimes(nums1) << endl; // Output: 3

    vector<int> nums2 = {2, 1, 2, 5, 3, 2};
    cout << "Repeated element in nums2: " << repeatedNTimes(nums2) << endl; // Output: 2

    vector<int> nums3 = {5, 1, 5, 2, 5, 3, 5, 4};
    cout << "Repeated element in nums3: " << repeatedNTimes(nums3) << endl; // Output: 5

    return 0;
}