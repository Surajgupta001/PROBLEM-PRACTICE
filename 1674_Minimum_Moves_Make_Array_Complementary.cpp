/*
Minimum Moves to Make Array Complementary - [LeetCode - 1674(Medium)]
----------------------------------------------------------------------------

You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.

The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.

Return the minimum number of moves required to make nums complementary.

Example 1:

Input: nums = [1,2,4,3], limit = 4
Output: 1
Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
nums[0] + nums[3] = 1 + 3 = 4.
nums[1] + nums[2] = 2 + 2 = 4.
nums[2] + nums[1] = 2 + 2 = 4.
nums[3] + nums[0] = 3 + 1 = 4.
Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.

Example 2:

Input: nums = [1,2,2,1], limit = 2
Output: 2
Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
Example 3:

Input: nums = [1,2,1,2], limit = 2
Output: 0
Explanation: nums is already complementary.
 

Constraints:

n == nums.length
2 <= n <= 10^5
1 <= nums[i] <= limit <= 10^5
n is even.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Approach: Brute Force
int minMoves(vector<int>& nums, int limit) {

}

// Approach: Difference Array Technique
int minMoves(vector<int>& nums, int limit) {
    int n = nums.size();

    vector<int> diff(2 * limit + 2, 0); // difference array to track changes

    for(int i=0; i<n/2; i++){
        int a = nums[i];
        int b = nums[n - 1 - i];

        int minVal = min(a, b) + 1; // minimum value that can be achieved by changing one of the elements
        int maxVal = max(a, b) + limit; // maximum value that can be

        diff[2] += 2; // initially, all pairs require 2 moves
        diff[2*limit + 1] -= 2; // after 2*limit, no moves are needed

        // For moves = 1
        diff[minVal] += (-1); // if we change one element to achieve minVal, we reduce moves by 1
        diff[maxVal + 1] -= (-1); // after maxVal, we need 2 moves again

        // For moves = 0
        diff[a + b] += (-1); // if we don't change any element, we save 1 move
        diff[a + b + 1] -= (-1); // after a + b, we need 2 moves again
    }

    int result = INT_MAX;

    for(int sum = 2; sum <= 2 * limit; sum++){
        diff[sum] += diff[sum - 1]; // accumulate the difference array to get the actual moves needed for each sum
        result = min(result, diff[sum]); // find the minimum moves needed
    }
    return result;
}

int main() {
    vector<int> nums1 = {1, 2, 4, 3};
    int limit1 = 4;
    cout << minMoves(nums1, limit1) << endl; // Output: 1

    vector<int> nums2 = {1, 2, 2, 1};
    int limit2 = 2;
    cout << minMoves(nums2, limit2) << endl; // Output: 2

    vector<int> nums3 = {1, 2, 1, 2};
    int limit3 = 2;
    cout << minMoves(nums3, limit3) << endl; // Output: 0

    return 0;
}