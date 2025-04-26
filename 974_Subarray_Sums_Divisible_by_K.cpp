/*
Subarray Sums Divisible by K - [Leetcode - 974(Medium)]
=======================================================
Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
Example 2:

Input: nums = [5], k = 9
Output: 0
 

Constraints:

1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
2 <= k <= 104
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Brute Force -> O(n^3)
int subarraysDivByK(vector<int>& nums, int k) {
    int count = 0;
    for(int i=0; i<nums.size(); i++){ // O(n)
        int sum = 0;
        for(int j=i; j<nums.size(); j++){// O(n)
            sum += nums[j]; // // O(n)
            if(sum % k == 0) count++;
        }
    }
    return count;
}

// Better Approch -> O(n^2)
int subarraysDivByK(vector<int>& nums, int k){
    int count = 0;
    // Cumlative Sum
    for(int i=1; i<nums.size(); i++){
        nums[i] += nums[i-1];
    }

    for(int i=0; i<nums.size(); i++){ // O(n)
        for(int j=i; j<nums.size(); j++){ // O(n)
            int sum = (i == 0) ? nums[j] : nums[j] - nums[i-1]; // O(1)
            if(sum % k == 0) count ++;
        }
    }
    return count;
}


// Optimised Approch -> O(n)
int subarraysDivByK(vector<int>& nums, int k){
    int count = 0;
    unordered_map<int, int> map;
    int sum = 0;

    map[0] = 1;

    for(int i=0; i<nums.size(); i++){
        sum += nums[i]; // Prefix Sum

        int remainder = sum % k;

        if(remainder < 0){ // Edge Corner --> Important
            remainder += k;
        }

        if(map.find(remainder) != map.end()){
            count += map[remainder];
        }
        map[remainder]++;
    }
    return count;
}

int main(){
    vector<int> nums = {4,5,0,-2,-3,1};
    int k = 5;
    cout << subarraysDivByK(nums, k) << endl; // Output: 7

    vector<int> nums2 = {5};
    cout << subarraysDivByK(nums2, 9) << endl; // Output: 0

    return 0;
} 