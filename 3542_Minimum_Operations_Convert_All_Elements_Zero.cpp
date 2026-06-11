/*
Minimum Operations to Convert All Elements to Zero - [Leetcode - 3542(Medium)]
--------------------------------------------------------------------------------
You are given an array nums of size n, consisting of non-negative integers. Your task is to apply some (possibly zero) operations on the array so that all elements become 0.

In one operation, you can select a subarray [i, j] (where 0 <= i <= j < n) and set all occurrences of the minimum non-negative integer in that subarray to 0.

Return the minimum number of operations required to make all elements in the array 0.

Example 1:

Input: nums = [0,2]

Output: 1

Explanation:

Select the subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0].
Thus, the minimum number of operations required is 1.

Example 2:

Input: nums = [3,1,2,1]

Output: 3

Explanation:

Select subarray [1,3] (which is [1,2,1]), where the minimum non-negative integer is 1. Setting all occurrences of 1 to 0 results in [3,0,2,0].
Select subarray [2,2] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [3,0,0,0].
Select subarray [0,0] (which is [3]), where the minimum non-negative integer is 3. Setting all occurrences of 3 to 0 results in [0,0,0,0].
Thus, the minimum number of operations required is 3.

Example 3:

Input: nums = [1,2,1,2,1,2]

Output: 4

Explanation:

Select subarray [0,5] (which is [1,2,1,2,1,2]), where the minimum non-negative integer is 1. Setting all occurrences of 1 to 0 results in [0,2,0,2,0,2].
Select subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,2,0,2].
Select subarray [3,3] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,0,0,2].
Select subarray [5,5] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,0,0,0].
Thus, the minimum number of operations required is 4.
 
Constraints:

1 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <stack>
using namespace std;

// Brute Force Approach
int minOperations(vector<int>& nums) {
    unordered_set<int> sets(nums.begin(), nums.end());

    int n = nums.size();

    int operations = 0;

    for(auto target : sets){
        if(target == 0) continue;

        bool flow = false;
        for(size_t i=0; i<n; i++){
            if(nums[i] == target){
                if(!flow){
                    flow = true;
                    operations++;
                }
            } else if (nums[i] < target){
                flow = false;
            }
        }
    }
    return operations;
}

// Monotonic Stack Approach
int minOperations(vector<int>& nums) {
    stack<int> st;
    int operations = 0;

    for(size_t i=0; i<nums.size(); i++){
        while(!st.empty() and st.top() > nums[i]){
            st.pop();
        }
        
        if(nums[i] == 0) continue;

        if(st.empty() or st.top() < nums[i]){
            st.push(nums[i]);
            operations++;
        }
    }
    return operations;
}

int main() {
    vector<int> nums1 = {0,2};
    cout << minOperations(nums1) << endl; // Output: 1

    vector<int> nums2 = {3,1,2,1};
    cout << minOperations(nums2) << endl; // Output: 3

    vector<int> nums3 = {1,2,1,2,1,2};
    cout << minOperations(nums3) << endl; // Output: 4

    return 0;
}