/*
Longest Balanced Subarray I - [Leetcode - 3719(Medium)]
---------------------------------------------------------
You are given an integer array nums.

A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

Return the length of the longest balanced subarray.

Example 1:

Input: nums = [2,5,4,3]

Output: 4

Explanation:

The longest balanced subarray is [2, 5, 4, 3].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.

Example 2:

Input: nums = [3,2,2,5,4]

Output: 5

Explanation:

The longest balanced subarray is [3, 2, 2, 5, 4].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.

Example 3:

Input: nums = [1,2,3,2]

Output: 3

Explanation:

The longest balanced subarray is [2, 3, 2].
It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.
 

Constraints:

1 <= nums.length <= 1500
1 <= nums[i] <= 10^5
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int longestBalanced(vector<int>& nums) {
    int maxLength = 0;

    for(int i=0; i<nums.size(); i++){
        unordered_set<int> evenSet;
        unordered_set<int> oddSet;

        for(int j=i; j<nums.size(); j++){
            if(nums[j] % 2 == 0){
                evenSet.insert(nums[j]);
            } else {
                oddSet.insert(nums[j]);
            }

            if(evenSet.size() == oddSet.size()){
                maxLength = max(maxLength, j - i + 1);
            }
        }
        
    }
    return maxLength;
}

int main() {
    vector<int> nums1 = {2, 5, 4, 3};
    cout << longestBalanced(nums1) << endl; // Output: 4

    vector<int> nums2 = {3, 2, 2, 5, 4};
    cout << longestBalanced(nums2) << endl; // Output: 5

    vector<int> nums3 = {1, 2, 3, 2};
    cout << longestBalanced(nums3) << endl; // Output: 3

    return 0;
}