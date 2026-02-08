/*
Minimum Removals to Balance Array - [Leetcode - 3634(Medium)]
---------------------------------------------------------------
You are given an integer array nums and an integer k.

An array is considered balanced if the value of its maximum element is at most k times the minimum element.

You may remove any number of elements from nums​​​​​​​ without making it empty.

Return the minimum number of elements to remove so that the remaining array is balanced.

Note: An array of size 1 is considered balanced as its maximum and minimum are equal, and the condition always holds true.


Example 1:

Input: nums = [2,1,5], k = 2

Output: 1

Explanation:

Remove nums[2] = 5 to get nums = [2, 1].
Now max = 2, min = 1 and max <= min * k as 2 <= 1 * 2. Thus, the answer is 1.

Example 2:

Input: nums = [1,6,2,9], k = 3

Output: 2

Explanation:

Remove nums[0] = 1 and nums[3] = 9 to get nums = [6, 2].
Now max = 6, min = 2 and max <= min * k as 6 <= 2 * 3. Thus, the answer is 2.

Example 3:

Input: nums = [4,6], k = 2

Output: 0

Explanation:

Since nums is already balanced as 6 <= 4 * 2, no elements need to be removed.
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= 10^5
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minRemoval(vector<int>& nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    // Here we will use two pointers to find the longest balanced subarray
    int L = 1; // Start from the second element
    int maxElement = nums[0]; // Initialize maxElement to the first element
    int minElement = nums[0]; // Initialize minElement to the first element

    int i = 0; // Start from the first element
    int j = 0; // Start from the first element and it will move forward to find the longest balanced subarray

    while(j < n){
        // Update the maxElement and minElement for the current subarray
        maxElement = max(maxElement, nums[j]);
        minElement = min(minElement, nums[j]);

        while(i < j && maxElement > (long long)minElement * k){
            i++; // Move the left pointer to the right to try to balance the array
            minElement = nums[i]; // Update the minElement to the new left pointer
        }

        L = max(L, j - i + 1); // Update the length of the longest balanced subarray
        j++; // Move the right pointer to the right to expand the subarray
    }
    
    return n - L; // Minimum removals to balance the array
}

int main() {
    vector<int> nums1 = {2, 1, 5};
    int k1 = 2;
    cout << "Minimum removals for example 1: " << minRemoval(nums1, k1) << endl;

    vector<int> nums2 = {1, 6, 2, 9};
    int k2 = 3;
    cout << "Minimum removals for example 2: " << minRemoval(nums2, k2) << endl;

    vector<int> nums3 = {4, 6};
    int k3 = 2;
    cout << "Minimum removals for example 3: " << minRemoval(nums3, k3) << endl;

    return 0;
}