/*
Longest Substring Without Repeating Characters - [Leetcode - 3(Medium)]
=======================================================================
Given a string s, find the length of the longest substring without repeating characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/ 

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int lengthOfLongestSubstring(string str){
    int i = 0; // left or start
    int j = 0; // right or end
    int maxLength = 0; // store the length of the longest substring without repeating character
    unordered_map<char, int> map;
    while(j < str.length()){
        if(map.find(str[j]) != map.end()){
            i = max(i, map[str[j]] + 1);
        }
        else{
            map[str[j]] = j;
            maxLength = max(maxLength, j - i + 1);
        }
        j++;
    }
    return maxLength;
}
int main(){

    string str;
    cout<<"Enter a string: ";
    getline(cin,str);

    cout<<"Length of the longest substring without repeating characters is: "<<lengthOfLongestSubstring(str)<<endl;
    
    return 0;
}