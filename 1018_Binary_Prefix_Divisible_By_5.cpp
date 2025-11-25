/*
Binary Prefix Divisible By 5 - [Leetcode - 1018(Easy)]
--------------------------------------------------------
You are given a binary array nums (0-indexed).

We define xi as the number whose binary representation is the subarray nums[0..i] (from most-significant-bit to least-significant-bit).

For example, if nums = [1,0,1], then x0 = 1, x1 = 2, and x2 = 5.
Return an array of booleans answer where answer[i] is true if xi is divisible by 5.

Example 1:

Input: nums = [0,1,1]
Output: [true,false,false]
Explanation: The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.
Only the first number is divisible by 5, so answer[0] is true.

Example 2:

Input: nums = [1,1,1]
Output: [false,false,false]

Constraints:

1 <= nums.length <= 10^5
nums[i] is either 0 or 1.

similar approach as used in 1015_Smallest_Integer_Divisible_by_K.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

vector<bool> prefixesDivBy5(vector<int>& nums) {
    int n = nums.size();
    vector<bool> result(n);

    int remainder = 0;

    for(int i=0; i<n; i++){
        remainder = (remainder * 2 + nums[i]) % 5;
        result[i] = (remainder == 0);
    }
    return result;
}

int main() {
    vector<int> nums = {0, 1, 1};
    vector<bool> result = prefixesDivBy5(nums);

    for(bool val : result) {
        cout << (val ? "true" : "false") << " ";
    }
    cout << endl;

    return 0;
}