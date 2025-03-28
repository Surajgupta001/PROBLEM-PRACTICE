/*
Two Sum [Leetcode - (01)]
=====================================
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& v, int target){
    unordered_map<int, int> numToIndex;
    for(int i=0;i<v.size();i++){
        int difference = target - v[i];
        if(numToIndex.find(difference) != numToIndex.end()){
            return {numToIndex[difference], i};
        }
        numToIndex[v[i]] = i;
    }
    return {}; // If no solution is found, return an empty vector
}

int main(){
    
    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int> v(n);
    cout<<"Enter the elements of vector: ";
    for(int i=0;i<n;i++) cin>>v[i];

    int target;
    cout<<"Enter the target: ";
    cin>>target;

    vector<int> result = twoSum(v, target);
    if(result.size() > 0){
        cout<<"Indices of two numbers that add up to "<<target<<" are: "<<result[0]<<" and "<<result[1]<<endl;
    }
    else{
        cout<<"No two numbers in the vector add up to "<<target<<endl;
    }
    return 0;
}