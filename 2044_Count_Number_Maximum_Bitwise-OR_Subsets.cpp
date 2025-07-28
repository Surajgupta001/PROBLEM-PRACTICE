/*
Count Number of Maximum Bitwise-OR Subsets - [Leetcode - 2044(Medium)]
-----------------------------------------------------------------------
Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.

The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).

 

Example 1:

Input: nums = [3,1]
Output: 2
Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
- [3]
- [3,1]
Example 2:

Input: nums = [2,2,2]
Output: 7
Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 23 - 1 = 7 total subsets.
Example 3:

Input: nums = [3,2,1,5]
Output: 6
Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
- [3,5]
- [3,1,5]
- [3,2,5]
- [3,2,1,5]
- [2,5]
- [2,1,5]
 

Constraints:

1 <= nums.length <= 16
1 <= nums[i] <= 105
*/ 

#include <iostream>
#include <vector>
using namespace std;

int countSubsets(int index, int currOr, vector<int>& nums, int maxOr, vector<vector<int>>& dp) {
    // Base case: If we have considered all elements
    if (index == nums.size()) {
        return currOr == maxOr ? 1 : 0; // Return 1 if current OR matches max OR, else return 0
    }

    // Check if the result is already computed
    if (dp[index][currOr] != -1) {
        return dp[index][currOr];
    }

    // Take nums[index] in the subset
    int takeCount = countSubsets(index + 1, currOr | nums[index], nums, maxOr, dp);

    // Do not take nums[index] in the subset
    int notTakeCount = countSubsets(index + 1, currOr, nums, maxOr, dp);

    // Store the result in the dp table
    dp[index][currOr] = takeCount + notTakeCount;
    return dp[index][currOr];
}

int countMaxOrSubsets(vector<int>& nums) {
    int maxOr = 0;
    
    for(auto &num : nums){
        maxOr |= num; // Calculate the maximum bitwise OR
    }
    
    // Initialize a dp table with -1
    vector<vector<int>> dp(nums.size() + 1, vector<int>(maxOr + 1, -1));

    int currOr = 0;

    return countSubsets(0, currOr, nums, maxOr, dp);
}

int main() {
    
    vector<int> nums = {3, 2, 1, 5};
    
    int result = countMaxOrSubsets(nums);
    
    cout << "Number of subsets with maximum bitwise OR: " << result << endl;
    
    return 0;
}