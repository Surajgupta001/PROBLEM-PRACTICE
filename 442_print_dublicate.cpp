/*
FIND ALL DUBLICATE IN AN ARRAY (LEETCODE-442)
==============================================
Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears once or twice, return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only constant extra space O(1).

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]

Example 2:

Input: nums = [1,1,2]
Output: [1]

Example 3:

Input: nums = [1]
Output: []
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> findDuplicates(vector<int>& v) {
    unordered_map<int, int> count;
    vector<int> ans;

    for(int itr : v) {
        count[itr]++;
    }
    
    for(auto it : count) {
        if(it.second == 2){
            ans.push_back(it.first);
        }
    }

    return ans;
}

int main(){

    int n;
    cout<<"Enter the size of vectors: ";
    cin>>n;

    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    cout<<"Original Vectors: ";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;

    vector<int>ans=findDuplicates(v);

    cout<<"Vectors after removing: ";
    for (int itr : ans) {
        cout << itr << " ";
    }
    cout << endl;

    return 0;
}