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
#include <algorithm>
using namespace std;

bool isSubsequence(string &str1, string &str2){

    auto itr2 = str2.begin();

    for(auto itr1 = str1.begin(); itr1 != str1.end(); itr1++){
        itr2 = find(itr2, str2.end(), *itr1);
        if(itr2 == str2.end()){
            return false;
        }
        itr2++;
    }
    return true;
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
        cout<<"TRUE";
    }
    else{
        cout<<"FALSE";
    }

    return 0;
}