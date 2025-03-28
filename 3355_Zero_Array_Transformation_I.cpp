/*
Zero Array Transformation I - [Leetcode - 3355(Medium)]
======================================================
You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].

For each queries[i]:

-> Select a subset(A subset of an array is a selection of elements (possibly none) of the array.) of indices within the range [li, ri] in nums.
-> Decrement the values at the selected indices by 1.

A Zero Array is an array where all elements are equal to 0.

Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially, otherwise return false.


Example 1:

Input: nums = [1,0,1], queries = [[0,2]]

Output: true

Explanation:

For i = 0:
Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
The array will become [0, 0, 0], which is a Zero Array.

Example 2:

Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]

Output: false

Explanation:

For i = 0:
Select the subset of indices as [1, 2, 3] and decrement the values at these indices by 1.
The array will become [4, 2, 1, 0].
For i = 1:
Select the subset of indices as [0, 1, 2] and decrement the values at these indices by 1.
The array will become [3, 1, 0, 0], which is not a Zero Array.


Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 105
1 <= queries.length <= 105
queries[i].length == 2
0 <= li <= ri < nums.length
*/

#include <iostream>
#include <vector>
using namespace std;

bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    vector<int>Prefix(n+1, 0);

    // Update the prefix sum array based on queries
    for (int i = 0; i < queries.size(); i++){
        int leftIdx = queries[i][0];
        int rightIdx = queries[i][1];
        Prefix[leftIdx]++;
        Prefix[rightIdx+1]--;
    }
    // Calculate the prefix sum array
    for (int i = 1; i <= n; i++){
        Prefix[i] += Prefix[i-1];
    }
    // Check if nums can be transformed into a Zero Array
    for (int i = 0; i < n; i++) {
        if (nums[i] > Prefix[i]) {
            return false;
        }
    }
    return true;
}

int main(){
    vector<int> nums = {1, 0, 1};
    vector<vector<int>> queries = {{0, 2}};
    cout << boolalpha << isZeroArray(nums, queries) << endl;
    return 0;
}