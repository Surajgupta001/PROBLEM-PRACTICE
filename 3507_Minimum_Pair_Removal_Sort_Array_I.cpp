/*
Minimum Pair Removal to Sort Array I - [Leetcode - 3507(Easy)]
----------------------------------------------------------------
Given an array nums, you can perform the following operation any number of times:

-> Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
-> Replace the pair with their sum.

Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).

Example 1:

Input: nums = [5,2,3,1]

Output: 2

Explanation:

The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
The array nums became non-decreasing in two operations.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

The array nums is already sorted.

Constraints:

1 <= nums.length <= 50
-1000 <= nums[i] <= 1000
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int minPairSum(vector<int>& nums) {
    int minSum = INT_MAX;
    int index = -1;

    for(int i=0; i<nums.size()-1; i++){
        int sum = nums[i] + nums[i+1];

        if(sum < minSum){
            minSum = sum;
            index = i;
        }
    }
    return index;
}

int minimumPairRemoval(vector<int>& nums) {
    int minOperations = 0;

    while(!is_sorted(nums.begin(), nums.end())){
        int index = minPairSum(nums);

        nums[index] = nums[index] + nums[index + 1];

        nums.erase(nums.begin() + index + 1);

        minOperations++;
    }

    return minOperations;
}

int main() {
    vector<int> nums = {5, 2, 3, 1};

    cout << "Minimum operations to make array non-decreasing: " << minimumPairRemoval(nums) << endl;

    return 0;
}