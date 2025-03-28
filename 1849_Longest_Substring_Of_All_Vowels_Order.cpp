/*
Longest Substring Of All Vowels in Order - [Leetcode - 1839(Medium)]
====================================================================
A string is considered beautiful if it satisfies the following conditions:

Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.

Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.

A substring is a contiguous sequence of characters in a string.

Example 1:

Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
Output: 13
Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
Example 2:

Input: word = "aeeeiiiioooauuuaeiou"
Output: 5
Explanation: The longest beautiful substring in word is "aeiou" of length 5.
Example 3:

Input: word = "a"
Output: 0
Explanation: There is no beautiful substring, so return 0.
 

Constraints:

1 <= word.length <= 5 * 105
word consists of characters 'a', 'e', 'i', 'o', and 'u'.
*/ 

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int longestBeautifulSubstring(string word) {
    if (word.empty()) {
        return 0;
    }

    int max_len = 0;
    vector<int> freq(5, 0);
    int left = 0;
    vector<char> vowel_map = {'a', 'e', 'i', 'o', 'u'};

    for (int right = 0; right < word.size(); right++) {
        int idx = 0;
        while (idx < 5 && word[right] != vowel_map[idx]) idx++;

        if (idx < 5) {
            if (right > 0 && word[right] < word[right - 1]) {
                left = right;
                fill(freq.begin(), freq.end(), 0);
            }
            freq[idx]++;
            if (freq[0] > 0 && freq[1] > 0 && freq[2] > 0 && freq[3] > 0 && freq[4] > 0) {
                max_len = max(max_len, right - left + 1);
            }
        } else {
            left = right + 1;
            fill(freq.begin(), freq.end(), 0);
            // memset(freq, 0, sizeof(freq)); -> used in array not in vector
        }
    }
    return max_len;
}

int main() {
    string word = "aeeeiiiioooauuuaeiou";
    int result = longestBeautifulSubstring(word);
    cout << "The length of the longest beautiful substring is: " << result << endl;
    return 0;
}