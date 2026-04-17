/*
Minimum Absolute Distance Between Mirror Pairs - [Leetcode - 3761(Medium)]
-------------------------------------------------------------------------------
You are given an integer array nums.

A mirror pair is a pair of indices (i, j) such that:

0 <= i < j < nums.length, and
reverse(nums[i]) == nums[j], where reverse(x) denotes the integer formed by reversing the digits of x. Leading zeros are omitted after reversing, for example reverse(120) = 21.
Return the minimum absolute distance between the indices of any mirror pair. The absolute distance between indices i and j is abs(i - j).

If no mirror pair exists, return -1.

Example 1:

Input: nums = [12,21,45,33,54]

Output: 1

Explanation:

The mirror pairs are:

(0, 1) since reverse(nums[0]) = reverse(12) = 21 = nums[1], giving an absolute distance abs(0 - 1) = 1.
(2, 4) since reverse(nums[2]) = reverse(45) = 54 = nums[4], giving an absolute distance abs(2 - 4) = 2.
The minimum absolute distance among all pairs is 1.

Example 2:

Input: nums = [120,21]

Output: 1

Explanation:

There is only one mirror pair (0, 1) since reverse(nums[0]) = reverse(120) = 21 = nums[1].

The minimum absolute distance is 1.

Example 3:

Input: nums = [21,120]

Output: -1

Explanation:

There are no mirror pairs in the array.

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9​​​​​​​
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

int getReverse(int num){
    int result = 0;
    while(num > 0){
        result = result * 10 + num % 10;
        num /= 10;
    }
    return result;
}

int minMirrorPairDistance(vector<int>& nums) {
    int n = nums.size();

    unordered_map<int, int> maps; // reverse value -> index

    int result = INT_MAX;

    for(int i=0; i<n; i++){
        if(maps.count(nums[i])){
            result = min(result, i - maps[nums[i]]);
        }
        maps[getReverse(nums[i])] = i;
    }
    return result == INT_MAX ? -1 : result;
}

int main() {
    vector<int> nums1 = {12, 21, 45, 33, 54};
    cout << minMirrorPairDistance(nums1) << endl; // Output: 1

    vector<int> nums2 = {120, 21};
    cout << minMirrorPairDistance(nums2) << endl; // Output: 1

    vector<int> nums3 = {21, 120};
    cout << minMirrorPairDistance(nums3) << endl; // Output: -1

    return 0;
}