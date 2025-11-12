/*
Minimum Number of Operations to Make All Array Elements Equal to 1 - [Leetcode - 2654(Medium)]
------------------------------------------------------------------------------------------------
You are given a 0-indexed array nums consisiting of positive integers. You can do the following operation on the array any number of times:

Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.
Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.

The gcd of two integers is the greatest common divisor of the two integers.

Example 1:

Input: nums = [2,6,3,4]
Output: 4
Explanation: We can do the following operations:
- Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
- Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
- Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
- Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].

Example 2:

Input: nums = [2,10,6,14]
Output: -1
Explanation: It can be shown that it is impossible to make all the elements equal to 1.
 
Constraints:

2 <= nums.length <= 50
1 <= nums[i] <= 10^6
 
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minOperations(vector<int>& nums) {
    int n = nums.size();
    
    int countOf1s = 0;
    for(int i=0; i<n; i++){
        if(nums[i] == 1) countOf1s++;
    }
    
    if(countOf1s > 0){
        return (n - countOf1s); // Each non-1 element needs one operation to become 1
    }

    int minStepsTo1 = INT_MAX;
    for(int i=0; i<n; i++){
        int GCD = nums[i];
        for(int j=i+1; j<n; j++){
            GCD = gcd(GCD, nums[j]);

            // Check if we can make a 1 from this subarray
            if(GCD == 1){
                minStepsTo1 = min(minStepsTo1, j - i); // j-i operations to make one 1
                break; // No need to check further as we found a subarray with GCD 1
            }
        }
    }

    if(minStepsTo1 == INT_MAX) return -1;
    return (n - 1) + minStepsTo1;
}

int main() {
    vector<int> nums1 = {2, 6, 3, 4};
    cout << "Minimum operations for nums1: " << minOperations(nums1) << endl; // Output: 4

    vector<int> nums2 = {2, 10, 6, 14};
    cout << "Minimum operations for nums2: " << minOperations(nums2) << endl; // Output: -1

    return 0;
}