/*
Maximum Sum of Two Non-Overlapping Subarrays - [Leetcode - 1031(Medium)]
-------------------------------------------------------------------------------
Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.

The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.

A subarray is a contiguous part of an array.

Example 1:

Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.

Example 2:

Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.

Example 3:

Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [0,3,8] with length 3. 

Constraints:

1 <= firstLen, secondLen <= 1000
2 <= firstLen + secondLen <= 1000
firstLen + secondLen <= nums.length <= 1000
0 <= nums[i] <= 1000
*/

#include <iostream>
#include <vector>
using namespace std;

int maxSum(vector<int>& prefixSum, int L, int M) {
    int n = prefixSum.size();
    int maxLengthSubSum = 0;
    int result = 0; // maxSum

    for(int mEnd = L + M - 1; mEnd < n; mEnd++){
        int lEnd = mEnd - M;
        int lStartPrevIndex = lEnd - L;

        int mBlockSum = prefixSum[mEnd] - prefixSum[lEnd];
        int lBlockSum = prefixSum[lEnd] - (lStartPrevIndex < 0 ? 0 : prefixSum[lStartPrevIndex]);

        maxLengthSubSum = max(maxLengthSubSum, lBlockSum);
        result = max(result, maxLengthSubSum + mBlockSum);
    }

    return result;
}

int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
    int L = firstLen;
    int M = secondLen;

    int n = nums.size();
    vector<int> prefixSum(n + 1);
    prefixSum[0] = nums[0];

    for(int i = 1; i < n; ++i){ 
        prefixSum[i] = prefixSum[i - 1] + nums[i];
    }

    return max(maxSum(prefixSum, L, M), maxSum(prefixSum, M, L));
}

int main() {
    vector<int> nums = {0,6,5,2,2,5,1,9,4};
    int firstLen = 1;
    int secondLen = 2;

    int result = maxSumTwoNoOverlap(nums, firstLen, secondLen);
    cout << "Maximum sum of two non-overlapping subarrays: " << result << endl;

    return 0;
}