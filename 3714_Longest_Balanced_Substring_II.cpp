/*
Longest Balanced Substring I - [Leetcode - 3713(Medium)]
----------------------------------------------------------
You are given a string s consisting of lowercase English letters.

A substring of s is called balanced if all distinct characters in the substring appear the same number of times.

Return the length of the longest balanced substring of s.

Example 1:

Input: s = "abbac"

Output: 4

Explanation:

The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.

Example 2:

Input: s = "zzabccy"

Output: 4

Explanation:

The longest balanced substring is "zabc" because the distinct characters 'z', 'a', 'b', and 'c' each appear exactly 1 time.​​​​​​​

Example 3:

Input: s = "aba"

Output: 2

Explanation:

​​​​​​​One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each appear exactly 1 time. Another longest balanced substring is "ba".

Constraints:

1 <= s.length <= 105
s contains only the characters 'a', 'b', and 'c'.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int helper(string &s, char c1, char c2) {
    int n = s.length();
    int maxLength = 0;
    
    unordered_map<int, int> diffMap; // diffMap[diff] = first index where this diff was seen
    int count1 = 0;
    int count2 = 0;

    for(int i=0; i<n; i++){
        if(s[i] != c1 && s[i] != c2) {
            diffMap.clear();
            count1 = 0;
            count2 = 0;
            continue;
        }

        if(s[i] == c1) count1++;
        else count2++;

        if(count1 == count2) {
            maxLength = max(maxLength, count1 + count2);
        }

        int diff = count1 - count2;
        if(diffMap.count(diff)) {
            maxLength = max(maxLength, (i - diffMap[diff]));
        } else {
            diffMap[diff] = i;
        }
    }
    return maxLength;
}

// Optimal Approach
int longestBalanced(string s) {
    int n = s.length();
    int maxLength = 0;
    
    // CASE : 1 - 
    int count = 1; // s[0] = 1
    for(int i=1; i<n; i++){
        if(s[i] == s[i-1]){
            count++;
        } else {
            maxLength = max(maxLength, count);
            count = 1; // reset count for the new character
        }
    }
    maxLength = max(maxLength, count); // for the last character sequence

    // CASE : 2 -
    maxLength = max(maxLength, helper(s, 'a', 'b'));
    maxLength = max(maxLength, helper(s, 'a', 'c'));
    maxLength = max(maxLength, helper(s, 'b', 'c'));

    // CASE : 3 -
    int countA = 0;
    int countB = 0;
    int countC = 0;
    
    unordered_map<string, int> diffMap; // diffMap[diff] = first index where this diff was seen

    for(int i=0; i<s.length(); i++){
        if(s[i] == 'a') countA++;
        else if(s[i] == 'b') countB++;
        else countC++;

        if(countA == countB && countB == countC) {
            maxLength = max(maxLength, countA + countB + countC);
        }

        int diffAB = countA - countB;
        int diffAC = countA - countC;

        string string_key = to_string(diffAB) + "," + to_string(diffAC);
        if(diffMap.count(string_key)) {
            maxLength = max(maxLength, (i - diffMap[string_key]));
        } else {
            diffMap[string_key] = i;
        }
    }
    return maxLength;
}

int main() {
    string s = "abbac";
    cout << longestBalanced(s) << endl; // Output: 4

    s = "zzabccy";
    cout << longestBalanced(s) << endl; // Output: 4

    s = "aba";
    cout << longestBalanced(s) << endl; // Output: 2

    return 0;
}