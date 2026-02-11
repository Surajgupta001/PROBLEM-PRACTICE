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

1 <= s.length <= 1000
s consists of lowercase English letters.
*/

#include <iostream>
#include <vector>
using namespace std;
    
bool checkBalanced(vector<int>& freq) {
    int common = 0;
    
    for(int i = 0; i < 26; i++) {
        if(freq[i] == 0) continue;
        if(common == 0) common = freq[i];
        else if(freq[i] != common) {
            return false;
        }
    }
    return true;
}

int longestBalanced(string s) {
    int n = s.length();
    int maxL = 0;
    
    for(int i = 0; i < n; i++) {
        
        vector<int> freq(26, 0);
        
        for(int j = i; j < n; j++) {
            freq[s[j] - 'a']++;
            //i..j
            if(checkBalanced(freq)) {
                maxL = max(maxL, j-i+1);
            }
        }
    }
    return maxL;
}

int main() {
    string s = "abbac";
    cout << longestBalanced(s) << endl;
    
    s = "zzabccy";
    cout << longestBalanced(s) << endl;
    
    s = "aba";
    cout << longestBalanced(s) << endl;
    
    return 0;
}