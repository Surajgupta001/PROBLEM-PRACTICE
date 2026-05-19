/*
Minimum Common Value - [Leetcode - 2540(Easy)]
-------------------------------------------------

Given two integer arrays nums1 and nums2, sorted in non-decreasing order, return the minimum integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.

Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one occurrence of that integer.

Example 1:
Input: nums1 = [1,2,3], nums2 = [2,4]
Output: 2
Explanation: The smallest element common to both arrays is 2, so we return 2.

Example 2:
Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
Output: 2
Explanation: There are two common elements in the array 2 and 3 out of which 2 is the smallest, so 2 is returned.

Constraints:

1 <= nums1.length, nums2.length <= 10^5
1 <= nums1[i], nums2[j] <= 10^9
Both nums1 and nums2 are sorted in non-decreasing order.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// APproach 1: Using Hashing - set
int getCommon(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> sets(nums2.begin(), nums2.end());
    for (auto num : nums1) {
        if (sets.count(num)) {
            return num;
        }
    }
    return -1;
}

// Approach 2: Using Binary Search
int getCommon(vector<int>& nums1, vector<int>& nums2) {
    for (auto num : nums1) {
        if (binary_search(nums2.begin(), nums2.end(), num)) {
            return num;
        }
    }
    return -1;
}

// Approach 3: Using Two Pointers
int getCommon(vector<int>& nums1, vector<int>& nums2) {
    int i = 0, j = 0;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] == nums2[j]) {
            return nums1[i];
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return -1;
}

int main() {
    vector<int> nums1 = {1, 2, 3, 6};
    vector<int> nums2 = {2, 3, 4, 5};
    cout << getCommon(nums1, nums2) << endl; // Output: 2
    return 0;
}