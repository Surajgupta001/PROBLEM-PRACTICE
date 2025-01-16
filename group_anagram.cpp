/*
GROUP ANAGRAM - (LEETCODE - 49)
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:

Input: strs = [""]
Output: [[""]]

Example 3:

Input: strs = ["a"]
Output: [["a"]]
*/ 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& str) {
    unordered_map<string, vector<string>> anagrams;
    
    for(string itr : str){
        string sortedStr = itr;
        sort(sortedStr.begin(), sortedStr.end());
        
        if(anagrams.find(sortedStr) != anagrams.end()){
            anagrams[sortedStr].push_back(itr);
        }
        else{
            anagrams[sortedStr] = {itr};
        }
    }
    
    vector<vector<string>> result;
    for (auto pair : anagrams) {
        result.push_back(pair.second);
    }
    
    return result;
}

int main(){
    
    vector<string>strs;
    string str;
    
    cout << "Enter the number of strings: ";
    int n;
    cin >> n;
    
    cout << "Enter the strings: ";
    for (int i = 0; i < n; i++) {
        cin>>str;
        strs.push_back(str);
    }
    
    vector<vector<string>> result = groupAnagrams(strs);
    
    cout<<"Grouped Anagrams: "<<endl;
    for (auto group : result) {
        for (string& str : group) {
            cout<<str<<" ";
        }
        cout<<endl;
    }

    return 0;
}