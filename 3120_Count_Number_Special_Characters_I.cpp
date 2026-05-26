/*
Count the Number of Special Characters I - [Leetcode - 3120(Easy)]
----------------------------------------------------------------------

You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.

Return the number of special letters in word.


Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters in word are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

No character in word appears in uppercase.

Example 3:

Input: word = "abBCab"

Output: 1

Explanation:

The only special character in word is 'b'.

Constraints:

1 <= word.length <= 50
word consists of only lowercase and uppercase English letters.
*/

#include <iostream>
using namespace std;

int numberOfSpecialChars(string word) {
    int count = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        if (word.find(c) != string::npos && word.find(toupper(c)) != string::npos) {
            count++;
        }
    }
    return count;       
}

int main() {
    string word1 = "aaAbcBC";
    cout << numberOfSpecialChars(word1) << endl; // Output: 3

    string word2 = "abc";
    cout << numberOfSpecialChars(word2) << endl; // Output: 0

    string word3 = "abBCab";
    cout << numberOfSpecialChars(word3) << endl; // Output: 1

    return 0;
}