/*
Smallest Subsequence of Distinct Characters - [Leetcode - 1081(Medium)]
--------------------------------------------------------------------------
Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

Example 1:

Input: s = "bcabc"
Output: "abc"

Example 2:

Input: s = "cbacdcbc"
Output: "acdb" 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.

Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string smallestSubsequence(string s) {
    int n = s.length();
    string result;
    
    vector<bool> taken(26, false); //O(1) space
    vector<int> lastIndex(26); //O(1) space
    
    for(int i = 0; i < n; i++) {
        char ch = s[i];
        
        lastIndex[ch-'a'] = i; // Store the last index of each character
    }
    
    
    for(int i = 0; i < n; i++) {
        
        int idx = s[i] - 'a';
        
        if(taken[idx] == true) continue; // If character is already taken, skip it
        
        while(result.length() > 0 && s[i] < result.back() && lastIndex[result.back() - 'a'] > i) {
            taken[result.back() - 'a'] = false; // Mark the last character as not taken
            result.pop_back(); // Remove the last character to maintain lexicographical order
        }
        
        result.push_back(s[i]); // Add the current character to the result
        taken[idx] = true; // Mark the current character as taken
        
    }
    return result;
}

int main() {
    string s1 = "bcabc";
    string s2 = "cbacdcbc";

    cout << "Smallest subsequence for s1: " << smallestSubsequence(s1) << endl; // Output: "abc"
    cout << "Smallest subsequence for s2: " << smallestSubsequence(s2) << endl; // Output: "acdb"

    return 0;
}