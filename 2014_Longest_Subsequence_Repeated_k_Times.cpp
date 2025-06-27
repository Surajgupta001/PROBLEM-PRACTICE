/*
Longest Subsequence Repeated k Times - [Leetcode - 2014(Hard)]
---------------------------------------------------------------
You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.

A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.

A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.

For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.



Example 1:

example 1
Input: s = "letsleetcode", k = 2
Output: "let"
Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
"let" is the lexicographically largest one.
Example 2:

Input: s = "bb", k = 2
Output: "b"
Explanation: The longest subsequence repeated 2 times is "b".
Example 3:

Input: s = "ab", k = 2
Output: ""
Explanation: There is no subsequence repeated 2 times. Empty string is returned.


Constraints:

n == s.length
2 <= n, k <= 2000
2 <= n < k * 8
s consists of lowercase English letters
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
// Approach-1 (Khandani Backtracking remplate - storing all possible strings)
// T.C : O(n * ((n/k)!))
// S.C : O(n/k)

bool isSubsequence(string &s, string &sub, int k) {
    int i = 0;
    int j = 0;
    int L = sub.length();
    int n = s.length();

    while (i < n && j < k * L) {
        if (s[i] == sub[j % L])
            j++;

        i++;
    }

    return j == k * L;
}

void backtracking(string &s, string &curr, vector<bool> &canUse, vector<int> &requiredFreq, int k, int maxLen, string &result) {
    if (curr.length() > maxLen) return;

    if ((curr.length() > result.length() || (curr.length() == result.length() && curr > result)) && isSubsequence(s, curr, k)) {
        result = curr;
    }

    for (int i = 0; i <= 25; i++) {
        if (canUse[i] == false || requiredFreq[i] == 0) continue;

        // DO
        char ch = i + 'a';
        curr.push_back(ch);
        requiredFreq[i]--;

        // EXPLORE
        backtracking(s, curr, canUse, requiredFreq, k, maxLen, result);

        // UNDO
        curr.pop_back();
        requiredFreq[i]++;
    }
}

string longestSubsequenceRepeatedK(string s, int k) {
    int n = s.length();

    int freq[26] = {};
    for (char &ch : s) {
        freq[ch - 'a']++;
    }

    vector<bool> canUse(26, false);
    vector<int> requiredFreq(26, 0);
    for (int i = 0; i < 26; ++i) {
        if (freq[i] >= k) {
            canUse[i] = true;
            requiredFreq[i] = freq[i] / k; // atmost this can be used in a subsequence
        }
    }

    int maxLen = n / k;

    string curr;
    string result = "";
    backtracking(s, curr, canUse, requiredFreq, k, maxLen, result);

    return result;
}
*/ 

// Approach-2 IMPROVED BACKTRACKING : (Khandani Backtracking remplate - storing all possible strings)
// T.C : O(n * ((n/k)!))
// S.C : O(n/k)

bool isSubsequence(string &s, string &sub, int k) {
    int i = 0;
    int j = 0;
    int L = sub.length();
    int n = s.length();

    while (i < n && j < k * L) {
        if (s[i] == sub[j % L]) {
            j++;
        }
        i++;
    }

    return j == k * L;
}

bool backtracking(string &s, string &curr, vector<bool> &canUse, vector<int> &requiredFreq, int k, int maxLen, string &result) {
    if (curr.length() == maxLen) {
        if (isSubsequence(s, curr, k)) {
            result = curr;
            return true;
        }
        return false;
    }

    for (int i = 25; i >= 0; i--) {
        if (canUse[i] == false || requiredFreq[i] == 0) continue;

        // DO
        char ch = i + 'a';
        curr.push_back(ch);
        requiredFreq[i]--;

        // EXPLORE
        if (backtracking(s, curr, canUse, requiredFreq, k, maxLen, result) == true) {
            return true;
        }

        // UNDO
        curr.pop_back();
        requiredFreq[i]++;
    }

    return false;
}

string longestSubsequenceRepeatedK(string s, int k) {
    int n = s.length();

    int freq[26] = {};
    for (char &ch : s) {
        freq[ch - 'a']++;
    }

    vector<bool> canUse(26, false);
    vector<int> requiredFreq(26, 0);
    for (int i = 0; i < 26; ++i) {
        if (freq[i] >= k) {
            canUse[i] = true;
            requiredFreq[i] = freq[i] / k; // atmost this can be used in a subsequence
        }
    }

    int maxLen = n / k;

    for (int len = maxLen; len >= 0; len--) {
        vector<int> tempRequiredFreq = requiredFreq;
        string curr = "";
        string result = "";
        if (backtracking(s, curr, canUse, tempRequiredFreq, k, len, result) == true) {
            return result;
        }
    }

    return "";
}

int main () {
    string s = "letsleetcode";
    int k = 2;

    string ans = longestSubsequenceRepeatedK(s, k);
    cout << "Longest subsequence repeated " << k << " times: " << ans << endl;

    return 0;
}