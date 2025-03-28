/*
Search 2D Matrix - [Leetcode - 74(Medium)]
=============================================
You are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous row.
Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

Example 1:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
*/ 

#include <iostream>
#include <vector>
using namespace std;

int searchMatrix(vector<vector<int>>& matrix, int target){
    int m = matrix.size();
    int n = matrix[0].size();
    int low = 0;
    int high = m * n - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        int midValue = matrix[mid / n][mid % n];
        if(midValue == target) return true;
        else if(midValue < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

int main(){

    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    
    int target = 3;
    
    cout<<searchMatrix(matrix, target)<<endl;
    
    return 0;
}