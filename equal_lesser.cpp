/*
Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the such that nums[i]==nums[j] and abs(i-j)<=k.

Input: nums = [1,2,3,1], k = 3;
Output: true;

Input: nums = [1,2,3,1,2,3], k = 2;
output: false;
*/ 
#include <iostream>
#include <vector>
using namespace std;

bool function(vector<int>&v, int k){
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i] == v[j] && abs(i-j) <= k){
                return true;
            }
        }
    }
    return false;
}
int main(){

    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;

    cout<<"Enter all the elements of vectors: ";
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    int k;
    cout<<"Enter a integer value: ";
    cin>>k;

    function(v,k);

    if(function(v,k)){
        cout << "TRUE" << endl;
    }
    else {
        cout << "FALSE" << endl;
    }

    return 0;
}