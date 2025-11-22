/*
Unique Length-3 Palindromic Subsequences - [Leetcode - 1930(Medium)]
----------------------------------------------------------------------
Given a string s, return the number of unique palindromes of length three that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".


Example 1:

Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")
Example 2:

Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".
Example 3:

Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")


Constraints:

3 <= s.length <= 105
s consists of only lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// Approach-1
// T.C : O(n)
// S.C : O(1) - Only 26 sized always
int countPalindromicSubsequence(string s) {
    int n = s.length();
    
    unordered_set<char> unique_letters;
    for (char &ch : s){
        unique_letters.insert(ch);
    }
    
    int result = 0;
    
    for (char letter : unique_letters){
        int first_idx = -1;
        int last_idx = -1;
        
        for (int i = 0; i < n; i++){
            if (s[i] == letter){
                if (first_idx == -1){
                    first_idx = i;
                }
                last_idx = i;
            }
        }
        
        unordered_set<char> st;
        for (int middle = first_idx + 1; middle <= last_idx - 1; middle++){
            st.insert(s[middle]);
        }
        
        result += st.size();
    }
    
    return result;
}

// Approach-2 (Storing first and last indices before hand
// T.C : O(n)
// S.C : O(1) - Only 26 sized always
int countPalindromicSubsequence(string s) {
    int n = s.length();
    
    vector<pair<int, int>> indices(26, {-1, -1}); // Store first and last indices for each letter

    for(int i = 0; i < n; i++){
        char ch = s[i];
        int idx = ch - 'a'; // a = 0, b = 1, ..., z = 25

        if(indices[idx].first == -1){
            indices[idx].first = i; // First occurrence
        }
        indices[idx].second = i; // Update last occurrence
    }

    int result = 0;
    for (int i = 0; i < 26; i++) {
        if (indices[i].first != -1 && indices[i].second != -1 && indices[i].second > indices[i].first) {
            unordered_set<char> unique_middle_chars;
            for (int j = indices[i].first + 1; j < indices[i].second; j++) {
                unique_middle_chars.insert(s[j]);
            }
            result += unique_middle_chars.size();
        }
    }

    return result;
}


int main() {
    string s1 = "aabca";
    cout << "Input: s = \"" << s1 << "\"" << endl;
    cout << "Output: " << countPalindromicSubsequence(s1) << endl; // Expected output: 3

    string s2 = "adc";
    cout << "Input: s = \"" << s2 << "\"" << endl;
    cout << "Output: " << countPalindromicSubsequence(s2) << endl; // Expected output: 0

    string s3 = "bbcbaba";
    cout << "Input: s = \"" << s3 << "\"" << endl;
    cout << "Output: " << countPalindromicSubsequence(s3) << endl; // Expected output: 4

    return 0;
}