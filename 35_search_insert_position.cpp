/*
Search Insert Position - [Leetcode - 35(Easy)]
================================================
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [1,3,5,6], target = 5
Output: 2
Example 2:

Input: nums = [1,3,5,6], target = 2
Output: 1
Example 3:

Input: nums = [1,3,5,6], target = 7
Output: 4
*/ 

#include <iostream>
#include <vector>
using namespace std;

int searchInsert(vector<int>& nums, int target){
    int low = 0;
    int high = nums.size()-1;

    while(low <= high){
        int mid = low + (high-low)/2;
        if(nums[mid] == target) return mid;
        else if(nums[mid] > target) high = mid-1;
        else low = mid+1;
    }
    // return low; -> this is also give a correct ans;
    // Use lower_bound to find the index where the target value should be inserted
    return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
}

int main(){

    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int> v(n);
    cout<<"Enter the elements of vector: ";
    for(int i=0; i<n; i++) cin>>v[i];

    int target;
    cout<<"Enter the target value: ";
    cin>>target;

    cout<<"Index of target value: "<<searchInsert(v, target)<<endl;

    return 0;
}