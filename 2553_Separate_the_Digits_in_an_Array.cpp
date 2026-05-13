/*
Separate the Digits in an Array - [Leetcode - 2553(Easy)]
---------------------------------------------------------------
Given an array of positive integers nums, return an array answer that consists of the digits of each integer in nums after separating them in the same order they appear in nums.

To separate the digits of an integer is to get all the digits it has in the same order.

For example, for the integer 10921, the separation of its digits is [1,0,9,2,1].

Example 1:
Input: nums = [13,25,83,77]
Output: [1,3,2,5,8,3,7,7]
Explanation: 
- The separation of 13 is [1,3].
- The separation of 25 is [2,5].
- The separation of 83 is [8,3].
- The separation of 77 is [7,7].
answer = [1,3,2,5,8,3,7,7]. Note that answer contains the separations in the same order.

Example 2:
Input: nums = [7,1,3,9]
Output: [7,1,3,9]
Explanation: The separation of each integer in nums is itself.
answer = [7,1,3,9].

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// using string conversion
vector<int> separateDigits(vector<int>& nums) {
    vector<int> res;
    for(auto num : nums){
        string s = to_string(num);
        for(auto ch : s){
            res.push_back(ch - '0');
        }
    }
    return res;
}

// without using string conversion
vector<int> separateDigits(vector<int>& nums) {
    vector<int> res;
    for(int num : nums){
        vector<int> temp;
        while(num > 0){
            temp.push_back(num % 10);
            num /= 10;
        }
        reverse(temp.begin(), temp.end());
        res.insert(res.end(), temp.begin(), temp.end());
    }
    return res;
}

int main() {
    vector<int> nums1 = {13,25,83,77};
    vector<int> res1 = separateDigits(nums1);
    for(int num : res1){
        cout << num << " ";
    }
    cout << endl;

    vector<int> nums2 = {7,1,3,9};
    vector<int> res2 = separateDigits(nums2);
    for(int num : res2){
        cout << num << " ";
    }
    cout << endl;

    return 0;
}