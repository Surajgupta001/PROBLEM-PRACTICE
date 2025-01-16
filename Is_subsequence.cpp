/*
IS SUBSEQUENCE - (LEETCODE - 392)
=====================================
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false
*/ 
#include <iostream>
#include <string>
using namespace std;

bool isSubsequence(string &str1, string &str2){

    /*
    * Time: O(N);
    * Space: O(1);
    */ 

    int left_ptr = 0; // traverse pointer for str1
    int right_ptr = 0; // traverse pointer for str2

    while (left_ptr < str1.size() && right_ptr < str2.size()){
        if (str1[left_ptr] == str2[right_ptr]){
            left_ptr++;
        }
        right_ptr++;
    }
    return left_ptr == str1.size();
}
int main(){

    string str1;
    cout<<"Enter a 1st string: ";
    getline(cin,str1);

    string str2;
    cout<<"Enter a 2nd string: ";
    getline(cin,str2);

    bool ans = isSubsequence(str1, str2);

    if(ans){
        cout<<"TURE";
    }
    else{
        cout<<"FALSE";
    }

    return 0;
}