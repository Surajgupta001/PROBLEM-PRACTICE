/*
Set Mismatch - [Leetcode - 645(Easy)]
=====================================
You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

Example 1:

Input: nums = [1,2,2,4]
Output: [2,3]

Example 2:

Input: nums = [1,1]
Output: [1,2]
*/ 

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Approach 1: Using Negative Marking
vector<int> findErrorNums(vector<int>& nums){
    /*
    Time : O(n);
    Space : O(1);
    */ 
    vector<int>ans;
    for(int i=0;i<nums.size();i++){
        int idx = abs(nums[i]) - 1;
        if(nums[idx] < 0) ans.push_back(abs(nums[i]));
        else nums[idx] *= -1;
    }
    for(int i=0;i<nums.size();i++){
        if(nums[i] > 0){
            ans.push_back(i+1);
            break;
        }
    }
    return ans;
}

int main(){

    vector<int> nums = {1,2,2,4};
    
    vector<int> result = findErrorNums(nums);
    for(int i=0;i<result.size();i++) cout<<result[i]<<" ";

    return 0;
}

/*
// Approach 2: Using Hashing
vector<int> findErrorNumsSet(vector<int>& nums){
    unordered_set<int>visit;
    int dublicate = 0;
    for(int i=0;i<nums.size();i++){
        if(visit.find(nums[i]) != visit.end()) dublicate = nums[i];
        visit.insert(nums[i]);
    }  
    for(int i=0;i<=nums.size();i++){
        if(visit.find(i) == visit.end()) return {dublicate,i};
    }
    return {};
}
*/ 