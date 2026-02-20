/*
Special Binary String - [Leetcode - 761(Hard)]
-------------------------------------------------
Special binary strings are binary strings with the following two properties:

The number of 0's is equal to the number of 1's.
Every prefix of the binary string has at least as many 1's as 0's.
You are given a special binary string s.

A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.

Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.

Example 1:

Input: s = "11011000"
Output: "11100100"
Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.

Example 2:

Input: s = "10"
Output: "10"

Constraints:

1 <= s.length <= 50
s[i] is either '0' or '1'.
s is a special binary string.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string makeLargestSpecial(string s) {
    vector<string> subs;
    int count = 0, start = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            count++;
        } else {
            count--;
        }
        if (count == 0) {
            subs.push_back("1" + makeLargestSpecial(s.substr(start + 1, i - start - 1)) + "0");
            start = i + 1;
        }
    }
    
    sort(subs.begin(), subs.end(), greater<string>()); // Sort in descending order to get the lexicographically largest result
    string result;
    
    for (const string& sub : subs) {
        result += sub;
    }
    
    return result;
}

int main() {
    string s1 = "11011000";
    string s2 = "10";
    
    cout << "Input: s = \"" << s1 << "\"" << endl;
    cout << "Output: \"" << makeLargestSpecial(s1) << "\"" << endl;
    
    cout << "Input: s = \"" << s2 << "\"" << endl;
    cout << "Output: \"" << makeLargestSpecial(s2) << "\"" << endl;
    
    return 0;
}