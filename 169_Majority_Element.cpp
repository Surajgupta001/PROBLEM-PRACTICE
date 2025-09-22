/*
Majority Element - [Leetcode - 169(Easy)]
=========================================
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

Example 1:

Input: nums = [3,2,3]
Output: 3

Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109

*/ 

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

// Using Majority Element Concept -> Boyer-Moore Majority Algorithms
int majorityElement(vector<int>& nums) {  // Optimal Approach - O(N) time and O(1) space
    int n = nums.size();
    int count = 0;
    int majority = NULL;
    
    for(int i = 0; i<n; i++){
        if(count == 0) {
            count = 1;
            majority = nums[i];
        }
        else if(nums[i] == majority){
            count++;
        }
        else{
            count--;
        }
    }
    //Since it is gauranteed that majority element exists, so we don't check for freq of "majority" and return
    return majority;
}

// 2nd Approach - Using sorting
int majorityElement(vector<int>& nums) { // Simple Approach - O(NlogN) time and O(1) space
    sort(nums.begin(), nums.end());
    return nums[nums.size()/2];
}

// 3rd Approach - using nth_element (partial sorting to median position)
int majorityElement(vector<int>& nums) { // Simple Approach - O(N) average time and O(1) space
    nth_element(nums.begin(), nums.begin() + nums.size()/2, nums.end());
    return nums[nums.size()/2];
}

// 4th Approach - Using HashMap
int majorityElement(vector<int>& nums) { // Simple Approach - O(N) time and O(N) space
    unordered_map<int, int> freqMap;
    int n = nums.size();
    
    for(int i = 0; i<n; i++){
        freqMap[nums[i]]++;
        if(freqMap[nums[i]] > n/2){
            return nums[i];
        }
    }
    return -1; // This line will never be reached as majority element is guaranteed to exist
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> nums = {3,2,3};
    cout << majorityElement(nums) << endl;
    
    return 0;
}