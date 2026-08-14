/*
Maximum Length Substring With Two Occurrences - [LeetCode - 3090(Easy)]
------------------------------------------------------------------------------
Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.

Example 1:

Input: s = "bcbbbcba"

Output: 4

Explanation:

The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
Example 2:

Input: s = "aaaa"

Output: 2

Explanation:

The following substring has a length of 2 and contains at most two occurrences of each character: "aaaa".
 

Constraints:

2 <= s.length <= 100
s consists only of lowercase English letters.
*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int maximumLengthSubstring(string s) {
    int n = s.length();
    int maxLength = 0;
    int left = 0;
    unordered_map<char, int> charCount;

    for (int right = 0; right < n; ++right) {
        charCount[s[right]]++;

        while (charCount[s[right]] > 2) {
            charCount[s[left]]--;
            left++;
        }

        maxLength = max(maxLength, right - left + 1);
    }

    return maxLength;
}

int main() {
    string s = "bcbbbcba"; // Example input

    int result = maximumLengthSubstring(s);
    cout << "Maximum length of substring with at most two occurrences of each character: " << result << endl;

    return 0;
}