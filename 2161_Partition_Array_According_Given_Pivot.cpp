/*
Partition Array According to Given Pivot - [Leetcode - 2161]
============================================================
You are given a 0-indexed integer array nums and an integer pivot. Rearrange nums such that the following conditions are satisfied:

Every element less than pivot appears before every element greater than pivot.
Every element equal to pivot appears in between the elements less than and greater than pivot.
The relative order of the elements less than pivot and the elements greater than pivot is maintained.
More formally, consider every pi, pj where pi is the new position of the ith element and pj is the new position of the jth element. If i < j and both elements are smaller (or larger) than pivot, then pi < pj.
Return nums after the rearrangement.


Example 1:

Input: nums = [9,12,5,10,14,3,10], pivot = 10
Output: [9,5,3,10,10,12,14]
Explanation: 
The elements 9, 5, and 3 are less than the pivot so they are on the left side of the array.
The elements 12 and 14 are greater than the pivot so they are on the right side of the array.
The relative ordering of the elements less than and greater than pivot is also maintained. [9, 5, 3] and [12, 14] are the respective orderings.
Example 2:

Input: nums = [-3,4,3,2], pivot = 2
Output: [-3,2,4,3]
Explanation: 
The element -3 is less than the pivot so it is on the left side of the array.
The elements 4 and 3 are greater than the pivot so they are on the right side of the array.
The relative ordering of the elements less than and greater than pivot is also maintained. [-3] and [4, 3] are the respective orderings.
 

Constraints:

1 <= nums.length <= 105
-106 <= nums[i] <= 106
pivot equals to an element of nums.
*/ 

#include <iostream>
#include <vector>
using namespace std;

vector<int> partitionArraow(vector<int>& nums, int pivot){
    
    // Create three vector to store element less than, equal to, and greater than the pivot
    vector<int> lessThanPivot;
    vector<int> equalToPivot;
    vector<int> greaterThanPivot;
    
    // Traverse the array and store the elements in the respective vectors
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] < pivot){
            lessThanPivot.push_back(nums[i]);
        }
        else if(nums[i] > pivot){
            greaterThanPivot.push_back(nums[i]);
        }
        else{
            equalToPivot.push_back(nums[i]);
        }
    }
    
    // Concatenate the three vectors to get the final result
    vector<int> ans;
    ans.insert(ans.end(), lessThanPivot.begin(), lessThanPivot.end());
    ans.insert(ans.end(), equalToPivot.begin(), equalToPivot.end());
    ans.insert(ans.end(), greaterThanPivot.begin(), greaterThanPivot.end());
    
    return ans;
}

int main(){

    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int> v(n);
    cout<<"Enter the elements of vector: ";
    for(int i=0; i<v.size(); i++) cin>>v[i];

    int pivot;
    cout<<"Enter the pivot element: ";
    cin>>pivot;
    
    vector<int>ans;
    ans = partitionArraow(v, pivot);
    cout<<"The final array is: ";
    for(int i = 0; i < ans.size(); i++) cout<<ans[i]<<" ";
    
    return 0;
}