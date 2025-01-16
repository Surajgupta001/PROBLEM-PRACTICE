/*
MAXIMUM PRODUCT OF THREE NUMBERS - (LEETCODE-628)
======================================================
Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

Example 1:

Input: nums = [1,2,3]
Output: 6

Example 2:

Input: nums = [1,2,3,4]
Output: 24

Example 3:

Input: nums = [-1,-2,-3]
Output: -6

*/ 

/*
LOGIC / ALORITHMS

Step-1 : Sort the aray.
Step 2: Calculate the product of the three largest numbers.
Step 3: Calculate the product of the two smallest numbers and the largest number.
Step 4: Return the maximum of the two products.
*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxProduct(vector<int>&v){

    // Step-1 : Sort the aray
    sort(v.begin(),v.end());

    // Step-2 : Calculate the product of the three largest numbers
    int product_1 = v[v.size()-1] * v[v.size()-2] * v[v.size()-3];

    // step-3 : Calculate the product of the two smallest numbers and the largest number
    int product_2 = v[0] * v[1] * v[v.size()-1];

    // Return the maximum of the two products
    return max(product_1,product_2);
}

int minProduct(vector<int>&v){

    // Step-1 : Sort the aray
    sort(v.begin(),v.end());

    // Step-2 : Calculate the product of the three largest numbers
    int product_1 = v[v.size()-1] * v[v.size()-2] * v[v.size()-3];

    // step-3 : Calculate the product of the two smallest numbers and the largest number
    int product_2 = v[0] * v[1] * v[v.size()-1];

    // Return the maximum of the two products
    return min(product_1,product_2);
}

int main(){

    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;

    cout<<"Enter all the elements of vectors: ";
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    cout<<"Maximum Product of 3 Elements are: ";
    int result_1 = maxProduct(v);
    cout<<result_1<<endl;

    cout<<"Minimum Product of 3 Elements are: ";
    int result_2 = minProduct(v);
    cout<<result_2;

    return 0;
}