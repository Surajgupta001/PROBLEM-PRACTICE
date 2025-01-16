/*
Top K Frequent - [Leetcode - 347(Medium)]
===========================================
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
*/ 

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> topKFrequent(vector<int>& v, int k){

    // map pair is <ele,freq>
    unordered_map<int, int> freq;
    for(auto ele:v) freq[ele]++; 

    // heap pair is <freq,ele>
    priority_queue<pair<int, int>> pq;
    for(auto itr=freq.begin();itr!=freq.end();itr++){
        pq.push({itr->second, itr->first});
    }
    vector<int>res;
    for(int i=0;i<k;i++){
        res.push_back(pq.top().second);
        pq.pop();
    }
    return res;
}

int main(){

    int n;
    cout<<"Enter the size of vector: ";
    cin>>n;

    vector<int>v(n);
    cout<<"Enter the elements of vector: ";
    for(int i=0;i<n;i++) cin>>v[i];

    int k;
    cout<<"Enter the value of K: ";
    cin>>k;
    
    vector<int> res = topKFrequent(v, k);
    cout<<"Top K frequent elements are: ";
    for(int i=0;i<res.size();i++) cout<<res[i]<<" ";

}