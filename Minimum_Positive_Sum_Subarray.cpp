/*
Minimum Positive Sum Subarray - [Leetcode - 3364(Easy)]
=======================================================
You are given an integer array nums and two integers l and r. Your task is to find the minimum sum of a subarray whose size is between l and r (inclusive) and whose sum is greater than 0.

Return the minimum sum of such a subarray. If no such subarray exists, return -1.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [3, -2, 1, 4], l = 2, r = 3

Output: 1

Explanation:

The subarrays of length between l = 2 and r = 3 where the sum is greater than 0 are:

[3, -2] with a sum of 1
[1, 4] with a sum of 5
[3, -2, 1] with a sum of 2
[-2, 1, 4] with a sum of 3
Out of these, the subarray [3, -2] has a sum of 1, which is the smallest positive sum. Hence, the answer is 1.

Example 2:

Input: nums = [-2, 2, -3, 1], l = 2, r = 3

Output: -1

Explanation:

There is no subarray of length between l and r that has a sum greater than 0. So, the answer is -1.

Example 3:

Input: nums = [1, 2, 3, 4], l = 2, r = 4

Output: 3

Explanation:

The subarray [1, 2] has a length of 2 and the minimum sum greater than 0. So, the answer is 3.
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int minSum(vector<int>& v, int l, int r) {
    int minimum = INT_MAX;
    bool flag = false;
    int n = v.size();
    int sum = 0;

    // Calculate the prefix sum
    for (int i = 0; i < n; i++) sum += v[i];

    // Initialize the minimum sum for the first window
    int windowSum = 0;
    for (int i = 0; i < l; i++) windowSum += v[i];

    // Slide the window and update the minimum sum
    for (int i = l; i <= r; i++) {
        if (windowSum > 0) {
            minimum = min(minimum, windowSum);
            flag = true;
        }

        // Update the window sum for the next iteration
        if (i < n) windowSum += v[i];

        // Remove the first element of the previous window
        if (i - l >= 0) windowSum -= v[i - l];
    }
    return flag ? minimum : -1;
} 

int main(){
    vector<int> v = {1, 2, 3, 4};
    int l = 2, r = 4;
    cout << minSum(v, l, r) << endl;
    return 0;
}