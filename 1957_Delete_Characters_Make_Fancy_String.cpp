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

// Function to make a fancy string (no three consecutive same characters)
string makeFancyString(string s) {
    string result = "";
    for (auto ch : s) {
        // Use result.size() directly to check last two characters
        if (result.size() >= 2 && result[result.size() - 1] == ch && result[result.size() - 2] == ch) {
            continue;
        }
        result += ch;
    }
    return result;
}

int main() {
    string s = "leeetcode";
    cout << "Original: " << s << endl;
    cout << "Fancy: " << makeFancyString(s) << endl; // Output: leetcode
    return 0;
}