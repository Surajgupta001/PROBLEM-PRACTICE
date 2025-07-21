/*
Delete Characters to Make Fancy String - [Leetcode - 1957 (Easy)]
-------------------------------------------------------------------
A fancy string is a string where no three consecutive characters are equal.

Given a string s, delete the minimum possible number of characters from s to make it fancy.

Return the final string after the deletion. It can be shown that the answer will always be unique.

 

Example 1:

Input: s = "leeetcode"
Output: "leetcode"
Explanation:
Remove an 'e' from the first group of 'e's to create "leetcode".
No three consecutive characters are equal, so return "leetcode".
Example 2:

Input: s = "aaabaaaa"
Output: "aabaa"
Explanation:
Remove an 'a' from the first group of 'a's to create "aabaaaa".
Remove two 'a's from the second group of 'a's to create "aabaa".
No three consecutive characters are equal, so return "aabaa".
Example 3:

Input: s = "aab"
Output: "aab"
Explanation: No three consecutive characters are equal, so return "aab".
 

Constraints:

1 <= s.length <= 105
s consists only of lowercase English letters.
*/ 

#include <iostream>
#include <string>
using namespace std;

string makeFancyString(string s) {
    
    string result = "";
    if (s.empty()) {
        return result;
    }

    result += s[0]; // Add the first character
    for (int i = 1; i < s.length(); i++) {
        // If the current character is the same as the previous two, skip it
        if (result.length() >= 2 && s[i] == result[result.length() - 1] && s[i] == result[result.length() - 2]) {
            continue;
        }
        result += s[i]; // Add the current character to the result
    }
    return result;
}

int main() {
    string s1 = "leeetcode";
    cout << "Input: " << s1 << ", Output: " << makeFancyString(s1) << endl; // Expected: leetcode

    string s2 = "aaabaaaa";
    cout << "Input: " << s2 << ", Output: " << makeFancyString(s2) << endl; // Expected: aabaa

    string s3 = "aab";
    cout << "Input: " << s3 << ", Output: " << makeFancyString(s3) << endl; // Expected: aab

    string s4 = "aaaaa";
    cout << "Input: " << s4 << ", Output: " << makeFancyString(s4) << endl; // Expected: aa

    string s5 = "abccddeefffgghh";
    cout << "Input: " << s5 << ", Output: " << makeFancyString(s5) << endl; // Expected: abccddeeffgghh

    return 0;
}