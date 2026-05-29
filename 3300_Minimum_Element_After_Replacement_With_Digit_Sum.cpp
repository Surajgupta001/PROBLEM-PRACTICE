/*
Minimum Element After Replacement With Digit Sum - [Leetcode - 3300(Easy)]
--------------------------------------------------------------------------------
You are given an integer array nums.

You replace each element in nums with the sum of its digits.

Return the minimum element in nums after all replacements.

Example 1:

Input: nums = [10,12,13,14]

Output: 1

Explanation:

nums becomes [1, 3, 4, 5] after all replacements, with minimum element 1.

Example 2:

Input: nums = [1,2,3,4]

Output: 1

Explanation:

nums becomes [1, 2, 3, 4] after all replacements, with minimum element 1.

Example 3:

Input: nums = [999,19,199]

Output: 10

Explanation:

nums becomes [27, 10, 19] after all replacements, with minimum element 10.

 

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minElement(vector<int>& nums) {
    int result = INT_MAX;
    for (int num : nums) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        result = min(result, sum);
    }
    return result;        
}

int main() {
    vector<int> nums1 = {10, 12, 13, 14};
    cout << minElement(nums1) << endl; // Output: 1

    vector<int> nums2 = {1, 2, 3, 4};
    cout << minElement(nums2) << endl; // Output: 1

    vector<int> nums3 = {999, 19, 199};
    cout << minElement(nums3) << endl; // Output: 10

    return 0;
}