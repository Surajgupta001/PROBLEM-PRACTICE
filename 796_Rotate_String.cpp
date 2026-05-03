/*
Rotate String - [Leetcode - 796(Easy)]
----------------------------------------
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.
 

Example 1:

Input: s = "abcde", goal = "cdeab"
Output: true

Example 2:

Input: s = "abcde", goal = "abced"
Output: false
 

Constraints:

1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.
*/

#include <iostream>
#include <string>
using namespace std;

bool rotateString(string s, string goal) {
    if (s.length() != goal.length()) {
        return false;
    }
    
    string temp = s + s; // Concatenate s with itself
    
    return temp.find(goal) != string::npos; // Check if goal is a substring of temp       
}

int main() {
    string s1 = "abcde";
    string goal1 = "cdeab";
    cout << boolalpha << rotateString(s1, goal1) << endl; // Output: true

    string s2 = "abcde";
    string goal2 = "abced";
    cout << boolalpha << rotateString(s2, goal2) << endl; // Output: false

    return 0;
}