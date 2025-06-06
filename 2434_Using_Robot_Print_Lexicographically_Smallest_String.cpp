/*
Using a Robot to Print the Lexicographically Smallest String - [Leetcode - 234(Medium)]
----------------------------------------------------------------------------------------
You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:

Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
Return the lexicographically smallest string that can be written on the paper.

 

Example 1:

Input: s = "zza"
Output: "azz"
Explanation: Let p denote the written string.
Initially p="", s="zza", t="".
Perform first operation three times p="", s="", t="zza".
Perform second operation three times p="azz", s="", t="".

Example 2:

Input: s = "bac"
Output: "abc"
Explanation: Let p denote the written string.
Perform first operation twice p="", s="c", t="ba". 
Perform second operation twice p="ab", s="c", t="". 
Perform first operation p="ab", s="", t="c". 
Perform second operation p="abc", s="", t="".

Example 3:

Input: s = "bdda"
Output: "addb"
Explanation: Let p denote the written string.
Initially p="", s="bdda", t="".
Perform first operation four times p="", s="", t="bdda".
Perform second operation four times p="addb", s="", t="".
 

Constraints:

1 <= s.length <= 105
s consists of only English lowercase letters.
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string robotWithString(string s) {
    int n = s.length();

    vector<char> minCharToRight(n); // You can store index of those characters if needed of storing characters
    minCharToRight[n - 1] = s[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        minCharToRight[i] = min(s[i], minCharToRight[i + 1]);
    }

    string t = "";
    string paper = "";

    int i = 0;
    while(i < n){
        t.push_back(s[i]);

        char minChar = (i+1 < n) ? minCharToRight[i + 1] : s[i]; // Get the minimum character from the right side of the current index

        while(!t.empty() && t.back() <= minChar) {
            paper.push_back(t.back());
            t.pop_back();
        }
        i++;
    }
    
    // If there are still characters left in t, we can write them to paper
    while(!t.empty()) {
        paper.push_back(t.back());
        t.pop_back();
    }

    return paper;
}

int main () {
    
    string s = "bdda";
    
    cout << "Lexicographically smallest string: " << robotWithString(s) << endl; // Output: "addb"
    
    return 0;
}