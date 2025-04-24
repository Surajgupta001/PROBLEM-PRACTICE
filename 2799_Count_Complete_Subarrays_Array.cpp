/*
Count Complete Subarrays in an Array - [Leetcode - 2799(Medium)]
================================================================
You are given an array nums consisting of positive integers.

We call a subarray of an array complete if the following condition is satisfied:

The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
Return the number of complete subarrays.

A subarray is a contiguous non-empty part of an array.

Example 1:

Input: nums = [1,3,1,2,2]
Output: 4
Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
Example 2:

Input: nums = [5,5,5,5]
Output: 10
Explanation: The array consists only of the integer 5, so any subarray is complete. The number of subarrays that we can choose is 10.


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 2000
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
============== Brute Force ================
int countCompleteSubarrays(vector<int>& nums) {
    int count = 0;
    for(int i=0; i<nums.size(); i++){
        unordered_set<int> distinct;
        for(int j=i; j<nums.size(); j++){
            distinct.insert(nums[j]);
            if(distinct.size() == unordered_set<int>(begin(nums), end(nums)).size()){
                count++;
            }
        }
    }
    return count;
}
*/ 

// ============ Sliding Window ==================
int countCompleteSubarrays(vector<int>& nums){
    int count = 0;
    unordered_set<int> distinct;
    for(int i=0; i<nums.size(); i++){
        distinct.insert(nums[i]);
    }
    
    int k = distinct.size();
    unordered_map<int, int> window;
    int left = 0;
    for(int right = 0; right < nums.size(); right++){
        window[nums[right]]++;
        while(window.size() == k){
            count += nums.size() - right;
            window[nums[left]]--;
            if(window[nums[left]] == 0){
                window.erase(nums[left]);
            }
            left++;
        }
    }
    return count;
}

int main(){

    vector<int> v = {5, 5, 5, 5};
    cout<<countCompleteSubarrays(v)<<endl;

    return 0;
}