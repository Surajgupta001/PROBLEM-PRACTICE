/*
Smallest Missing Integer Greater Than Sequential Prefix Sum - [Leetcode - 2996(Easy)]
-----------------------------------------------------------------------------------------
You are given a 0-indexed array of integers nums.

A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j - 1] + 1. In particular, the prefix consisting only of nums[0] is sequential.

Return the smallest integer x missing from nums such that x is greater than or equal to the sum of the longest sequential prefix.

Example 1:

Input: nums = [1,2,3,2,5]
Output: 6
Explanation: The longest sequential prefix of nums is [1,2,3] with a sum of 6. 6 is not in the array, therefore 6 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix.

Example 2:

Input: nums = [3,4,5,1,12,14,13]
Output: 15
Explanation: The longest sequential prefix of nums is [3,4,5] with a sum of 12. 12, 13, and 14 belong to the array while 15 does not. Therefore 15 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix. 

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 50
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int missingInteger(vector<int>& nums) {
    int n = nums.size();
    
    unordered_set<int> numSet(nums.begin(), nums.end());

    int sequentialSum = nums[0];

    for(int j=1; j<n; j++){
        if(nums[j] == nums[j-1] + 1){
            sequentialSum += nums[j];
        } else {
            break;
        }
    }

    while(numSet.count(sequentialSum)) {
        sequentialSum++;
    }

    return sequentialSum;
}

int main() {
    vector<int> nums1 = {1, 2, 3, 2, 5};
    cout << "Output: " << missingInteger(nums1) << endl; // Output: 6

    vector<int> nums2 = {3, 4, 5, 1, 12, 14, 13};
    cout << "Output: " << missingInteger(nums2) << endl; // Output: 15

    return 0;
}