/*
Check If All 1's Are at Least Length K Places Away - [Leetcode - 1437(Easy)]
------------------------------------------------------------------------------
Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.

Example 1:

Input: nums = [1,0,0,0,1,0,0,1], k = 2
Output: true
Explanation: Each of the 1s are at least 2 places away from each other.

Example 2:

Input: nums = [1,0,0,1,0,1], k = 2
Output: false
Explanation: The second 1 and third 1 are only one apart from each other.
 

Constraints:

1 <= nums.length <= 10^5
0 <= k <= nums.length
nums[i] is 0 or 1
*/ 

#include <iostream>
#include <vector>
using namespace std;

bool kLengthApart(vector<int>& nums, int k) {
    int lastOne = -(k+1);
    for(int i=0; i<nums.size(); i++){
        if(nums[i] == 1){
            if(i - lastOne - 1 < k){
                return false;
            }
            lastOne = i;
        }
    }
    return true;
}

int main() {
    vector<int> nums1 = {1,0,0,0,1,0,0,1};
    int k1 = 2;
    cout << (kLengthApart(nums1, k1) ? "true" : "false") << endl; // Expected output: true

    vector<int> nums2 = {1,0,0,1,0,1};
    int k2 = 2;
    cout << (kLengthApart(nums2, k2) ? "true" : "false") << endl; // Expected output: false

    return 0;
}