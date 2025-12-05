/*
Count Partitions with Even Sum Difference - [Leetcode - 3432(Easy)]
---------------------------------------------------------------------
You are given an integer array nums of length n.

A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty subarrays such that:

Left subarray contains indices [0, i].
Right subarray contains indices [i + 1, n - 1].
Return the number of partitions where the difference between the sum of the left and right subarrays is even.

Example 1:

Input: nums = [10,10,3,7,6]

Output: 4

Explanation:

The 4 partitions are:

[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

No partition results in an even sum difference.

Example 3:

Input: nums = [2,4,6,8]

Output: 3

Explanation:

All partitions result in an even sum difference.

Constraints:

2 <= n == nums.length <= 100
1 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//Approach-1 (Using cumulative sum)
//T.C : O(n) ( 2 Pass  )
//S.C : O(1)
int countPartitions(vector<int>& nums) {
    int n = nums.size();
    
    int sum = accumulate(begin(nums), end(nums), 0);
    
    int leftSum = 0;
    
    int result = 0;
    
    for(int i = 0; i < n-1; i++) {
        leftSum += nums[i];
        
        int rightSum = sum - leftSum;
        
        if((leftSum - rightSum) % 2 == 0) result++;
    }

    return result;
}



//Approach-2 (Using one pass - Maths)
//T.C : O(n) ( 1 Pass  )
//S.C : O(1)
int countPartitions(vector<int>& nums) {
    int n = nums.size();
    
    int sum = accumulate(begin(nums), end(nums), 0);
    
    if(sum % 2 == 0) return n-1; //all partitions will be possible as it only depends on sum
    
    return 0;
}


int main() {
    vector<int> nums1 = {10, 10, 3, 7, 6};
    cout << countPartitions(nums1) << endl; // Output: 4

    vector<int> nums2 = {1, 2, 2};
    cout << countPartitions(nums2) << endl; // Output: 0

    vector<int> nums3 = {2, 4, 6, 8};
    cout << countPartitions(nums3) << endl; // Output: 3

    return 0;
}