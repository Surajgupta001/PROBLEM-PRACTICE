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
using namespace std;

// Function to create a frequency vector for a given string
vector<int>getFrequencyVector(string str){
    vector<int>freq(26, 0); // Assuming all characters are lowercase
    for(char c : str){
        freq[c - 'a']++;
    }
    return freq;
}

// Function to convert a frequency vector to a string for hashing
string frequencyVectorToString(vector<int>&freq) {
    string str;
    for(int count : freq) {
        str = str + to_string(count) + ",";
    }
    return str;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> anagrams;
    
    for (string str : strs) {
        vector<int>freq = getFrequencyVector(str);
        string freqStr = frequencyVectorToString(freq);
        
        if (anagrams.find(freqStr) != anagrams.end()) {
            anagrams[freqStr].push_back(str);
        }
        else {
            anagrams[freqStr] = {str};
        }
    }
    
    vector<vector<string>> result;
    for(auto pair : anagrams) {
        result.push_back(pair.second);
    }
    
    return result;
}

int main(){
    
    vector<string> strs;
    string str;
    
    cout << "Enter the number of strings: ";
    int n;
    cin >> n;
    
    cout << "Enter the strings: ";
    for (int i = 0; i < n; i++) {
        cin >> str;
        strs.push_back(str);
    }
    
    vector<vector<string>> result = groupAnagrams(strs);
    
    cout << "Grouped Anagrams: " << endl;
    for (auto group : result) {
        for (string& str : group) {
            cout << str << " ";
        }
        cout << endl;
    }

    return 0;
} 