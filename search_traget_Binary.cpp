/*
BINARY SEARCH - (LEETCODE-704)
Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Example 2:

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
*/ 
#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>&v, int target){

    int low = 0;
    int high = v.size()-1;

    while(low <= high){
        int mid = low + (high-low)/2;
        if(v[mid] == target) return mid;
        else if(v[mid]<target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int main(){

    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    int target;
    cout<<"Enter the target: ";
    cin>>target;

    int result = search(v,target);
    cout<<"Indexes: "<<result<<endl;

    return 0;
}