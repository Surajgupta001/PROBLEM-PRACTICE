/*
Majority Element II - [Leetcode - 229(Medium)]
==============================================
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 
Constraints:

1 <= nums.length <= 5 * 104
-109 <= nums[i] <= 109
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Using Majority Element Concept -> Boyer-Moore Majority Algorithms
vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    
    int majority1 = NULL;
    int count1 = 0;

    int majority2 = NULL;
    int count2 = 0;
    
    int freq = floor(n/3);
    
    for(int i = 0; i<n; i++) {
        if(nums[i] == majority1) count1++;
        else if(nums[i] == majority2) count2++;
        else if(count1 == 0) {
            majority1 = nums[i];
            count1 = 1;
        }
        else if(count2 == 0) {
            majority2 = nums[i];
            count2 = 1;
        }
        else {
            count1--;
            count2--;
        }
    }
    
    vector<int> ans; //because atmost two elements can occur more than ⌊ n/3 ⌋ in an array of length n
    count1 = 0;
    count2 = 0;
    
    for(int num:nums) {
        if(num == majority1) count1++;
        else if(num == majority2) count2++;
    }

    if(count1 > floor(n/3)) ans.push_back(majority1);
    if(count2 > floor(n/3)) ans.push_back(majority2);
    
    return ans;
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> nums = {3,2,3};
    vector<int> result = majorityElement(nums);
    
    return 0;
}