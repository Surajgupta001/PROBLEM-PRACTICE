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
    int n = result.size();
    
    for (auto ch : s) {
        // If last two characters in result are same as current, skip
        if (n >= 2 && result[n - 1] == ch && result[n - 2] == ch) {
            continue;
        }
        else {
            result += ch; // Add current character to result
        }
    }
    return result;
}

int main() {
    string s = "aaabaaaa";
    cout << "Original: " << s << endl;
    cout << "Fancy: " << makeFancyString(s) << endl; // Output: aabaa
    return 0;
}