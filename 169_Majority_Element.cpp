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
#include <vector>
using namespace std;

// Using Majority Element Concept -> Boyer-Moore Majority Algorithms
int majorityElement(vector<int>& nums) {
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

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> nums = {3,2,3};
    cout << majorityElement(nums) << endl;
    
    return 0;
}