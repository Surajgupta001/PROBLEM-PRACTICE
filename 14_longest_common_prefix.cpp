/*
LONGEST COMMON PREFIX - (LEETCODE 14)
=====================================
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
*/ 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string longestCommonPrefix(vector<string> &str){

    sort(str.begin(), str.end());

    string  str1 = str[0]; // first string
    string  strr2 = str[str.size()-1]; // last string

    string ans = ""; // if no larget Common Prefix then retuen empty string.

    for(int i=0;i<str1.size();i++){
        if(str1[i] == strr2[i]){
            ans += str1[i];
        }
        else{
            break;
        }
    }
    return ans;
}
int main(){

    int n;
    cout<<"Enter the numbers of string: ";
    cin>>n;

    vector<string>strs;
    cout<<"Enter all the strings: ";
    for(int i=0;i<n;i++){
        string str;
        cin>>str;
        strs.push_back(str);
    }

    cout<<"Longest common prefix: "<<longestCommonPrefix(strs)<<endl;

    return 0;
}